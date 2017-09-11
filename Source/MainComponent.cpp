/*
   Composer: A Halo specific music player
   Copyright (C) 2017 Devin Bobadilla

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "widgets/commands_panel.h"
#include "widgets/about_panel.h"
#include "widgets/playlist_panel.h"
#include "widgets/playback_panel.h"
#include "widgets/settings_panel.h"
#include "widgets/controls.h"
#include "widgets/text_tree_item.cpp"
#include "player/playlist.h"
#include "config.h"
#include "util/util.h"
#include "../JuceLibraryCode/JuceHeader.h"

void trackClickedCallback(void *object, int index);
void trackDoubleClickedCallback(void *object, int index);
void commandClickedCallback(void *object, int index);
void commandDoubleClickedCallback(void *object, int index);
juce::String get_command_text_string(Command *cmd);

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

using std::min;
using std::max;

class MainContentComponent    : public juce::Component,
                                public juce::Slider::Listener,
                                public juce::TextButton::Listener,
                                public juce::AudioSource
{
public:
    //==============================================================================
    MainContentComponent()
    {
        // setup the window and the controls panel
        setSize (350, 500);
        addAndMakeVisible(controls_panel);

        // setup the button and slider listener overrides
        controls_panel.set_slider_listener_override(this);
        controls_panel.set_button_listener_override(this);

        this->active_track   = 0;
        this->active_command = 0;

        this->playlist_reader_count = 0;
        this->lock_playlist_reading = false;
        this->delete_curr_samples = false;
        this->curr_samples = NULL;
        this->working_dir = get_working_dir();

        this->resampler = new juce::ResamplingAudioSource(this, false);

        // load the config and load the last playlist played
        this->config   = new ComposerConfig(strcpycat(this->working_dir, (char *)DEF_CONFIG_NAME));
        this->playlist = new Playlist(config->get_last_playlist());

        if (playlist->command_lists == NULL || !playlist->is_valid()) {
            // couldnt load the playlist, so make a new one
            delete this->playlist;
            this->playlist = new Playlist();
            this->playlist->set_tags_dir(config->get_tags_dir());
            this->playlist->set_filepath(strcpycat(config->get_playlists_dir(), "untitled.play"));
        }

        this->loadPlaylistToWidgets();

        this->setVolume(this->config->data->last_volume);
    }

    ~MainContentComponent()
    {
        shutdownAudio();

        this->stopPlayback();

        if (this->playlist != NULL && this->config != NULL) {
            this->config->set_last_playlist(this->playlist->get_filepath());
            this->config->data->last_volume = this->getVolume();

            this->config->serialize();

            delete this->playlist;
            this->playlist = NULL;

            delete this->config;
            this->config = NULL;
        }

        PlaylistPanel *playlist_panel = (PlaylistPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(0));
        playlist_panel->playlistTree->deleteRootItem();

        CommandsPanel *commands_panel = (CommandsPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(1));
        commands_panel->commandsTree->deleteRootItem();
        delete this->resampler;
        delete this->curr_samples;
    }

    float getVolume() {
        return (float)max(0.0, min(1.0, this->controls_panel.playbackPanel->volume->getValue() / 100));
    }

    void setVolume(float new_val) {
        this->controls_panel.playbackPanel->volume->setValue(max(0.0, min(100.0, new_val * 100.0)),
                                                             dontSendNotification);
        this->audioSourcePlayer.setGain((float)(this->controls_panel.playbackPanel->volume->getValue() / 100.0));
    }

    void buttonClicked(juce::Button* button) override
    {
        if (button == NULL || button == nullptr) return;
        juce::String name = button->getName();

        if      (!name.compareIgnoreCase(juce::String("playlists dir button"))) {
            // changing the default tags directory
            juce::FileChooser *chooser = new juce::FileChooser(
                juce::String("Select the directory to save playlists to"),
                juce::File(this->config->get_playlists_dir())
            );

            if (chooser->browseForDirectory()) {
                juce::File result = chooser->getResult();
                this->config->set_playlists_dir((char *)result.getFullPathName().toRawUTF8());
                this->reloadSettingsWidgets();
            }
            delete chooser;
        }
        else if (!name.compareIgnoreCase(juce::String("tagsdir button"))) {
            // changing the default tags directory
            if (this->playlist == NULL) return;

            juce::FileChooser *chooser = new juce::FileChooser(
                juce::String("Select the current playlist's tags directory"),
                juce::File(this->playlist->get_tags_dir())
            );

            if (chooser->browseForDirectory()) {
                juce::File result = chooser->getResult();
                if (this->acquire_playlist_write_lock()) return;
                this->playlist->set_tags_dir((char *)result.getFullPathName().toRawUTF8());
                this->playlist->set_lsnd_tags_dirs();
                this->release_playlist_write_lock();
                this->config->set_tags_dir(this->playlist->get_tags_dir());
                this->reloadSettingsWidgets();
            }
            delete chooser;
        }
        else if (!name.compareIgnoreCase(juce::String("new playlist button"))) {
            // making a new playlist
            this->stopPlayback();

            if (this->acquire_playlist_write_lock()) return;
            delete this->playlist;
            this->playlist = new Playlist();
            this->playlist->set_tags_dir(config->get_tags_dir());
            this->playlist->set_filepath(strcpycat(this->config->get_playlists_dir(), "untitled.play"));
            this->release_playlist_write_lock();

            // reload the widgets
            this->loadPlaylistToWidgets();
        }
        else if (!name.compareIgnoreCase(juce::String("load playlist button"))) {
            // loading a playlist from a file
            juce::FileChooser *chooser = new juce::FileChooser(
                juce::String("Select a playlist to load..."),
                juce::File(this->config->get_playlists_dir()),
                juce::String("*.play")
            );

            if (chooser->browseForFileToOpen()) {
                juce::File result = chooser->getResult();
                Playlist *new_playlist = new Playlist((char *)result.getFullPathName().toRawUTF8());

                if (new_playlist == NULL) {
                    // bad playlist. let it get deleted.
                } else if (new_playlist->is_valid()) {
                    // stop the current playback and replace the playlist
                    this->stopPlayback();
                    delete this->curr_samples;
                    this->curr_samples = NULL;
                    if (this->acquire_playlist_write_lock()) return;
                    delete this->playlist;
                    this->playlist = new_playlist;
                    this->release_playlist_write_lock();
                    new_playlist = NULL;

                    // reload the widgets
                    this->loadPlaylistToWidgets();
                }
                delete new_playlist;
            }
            delete chooser;
        }
        else {
            // something to do with the playlist
            if (this->playlist == NULL)       return;
            if (!this->playlist->is_valid())  return;

            int curr_cmdl_sel = this->getSelectedTrackIndex();
            CommandList *cmdl = this->playlist->get_command_list(curr_cmdl_sel);

            if      (!name.compareIgnoreCase(juce::String("save playlist button"))) {
                // save playlist to file
                juce::FileChooser *chooser = new juce::FileChooser(
                    juce::String("Save playlist as..."),
                    juce::File(this->playlist->get_filepath()),
                    juce::String("*.play")
                );

                if (chooser->browseForFileToSave(true)) {
                    juce::File result = chooser->getResult();
                    this->playlist->set_filepath(result.getFullPathName().toRawUTF8());
                    this->playlist->serialize();
                    this->reloadSettingsWidgets();
                }
                delete chooser;
            }
            else if (!name.compareIgnoreCase(juce::String("stop button"))) {
                // stop pressed
                this->stopPlayback();
            }
            else if (!name.compareIgnoreCase(juce::String("play button"))) {
                // play/pause pressed. decide what to do.
                bool select_track = false;
                if (this->playlist->is_stopped()) {
                    select_track = true;
                    this->startPlayback();
                } else if (this->playlist->is_paused()) {
                    this->resumePlayback();
                } else {
                    this->pausePlayback();
                }
                if (this->getSelectedTrackIndex() < 0 || select_track) {
                    this->selectPlaylistTreeIndex(this->playlist->curr_command_list());
                }
            }
            else if (!name.compareIgnoreCase(juce::String("next track button"))) {
                // increment to the next playlist and start playing
                bool is_playing = (this->playlist->is_playing());
                this->stopPlayback();
                this->playlist->inc_command_list();

                if (is_playing) this->startPlayback();
                setActiveIndexes();
                this->selectPlaylistTreeIndex(this->active_track);
            }
            else if (!name.compareIgnoreCase(juce::String("add track button"))) {
                // adding tracks to playlist
                juce::FileChooser *chooser = new juce::FileChooser(
                    juce::String("Select tracks to add to playlist."),
                    juce::File(this->playlist->get_tags_dir()),
                    juce::String("*.sound_looping;*.sound")
                );

                if (chooser->browseForMultipleFilesToOpen()) {
                    const juce::Array<juce::File> results = chooser->getResults();

                    for (int i = 0; i < results.size(); i++) {
                        HaloTag *tag = load_tag_at_path((char *)results[i].getFullPathName().toRawUTF8(),
                            this->playlist->get_tags_dir());

                        if (tag == NULL) continue;
                        if (this->acquire_playlist_write_lock()) continue;
                        if (!tag->is_valid()) {
                            // tag wasn't valid
                            delete tag;
                        } else if (tag->tag_header->tag_class == TagClass::snd) {
                            // add the tag to the playlist
                            this->playlist->add_command_list((SndTag *)tag);
                            delete tag; // unload the sound since we dont need it now
                        } else if (tag->tag_header->tag_class == TagClass::lsnd) {
                            // add the tag to the playlist
                            this->playlist->add_command_list((LsndTag *)tag);
                        } else {
                            // wrong kind of tag
                            delete tag;
                        }
                        this->release_playlist_write_lock();
                    }
                    this->reloadPlaylistTree();
                }
                delete chooser;
            }
            else if (!name.compareIgnoreCase(juce::String("remove track button"))) {
                // removing track from the playlist
                bool set_playlist_sel = false;
                if (this->playlist->curr_command_list() == curr_cmdl_sel) {
                    this->stopPlayback();
                    set_playlist_sel = true;
                }
                if (this->acquire_playlist_write_lock()) return;
                this->playlist->remove_command_list(curr_cmdl_sel);
                this->release_playlist_write_lock();
                this->selectPlaylistTreeIndex(-1);
                this->reloadPlaylistTree();
                if (curr_cmdl_sel >= this->playlist->command_list_count) {
                    curr_cmdl_sel = this->playlist->command_list_count - 1;
                }
                if (set_playlist_sel) this->playlist->select_command_list(curr_cmdl_sel);
                this->selectPlaylistTreeIndex(curr_cmdl_sel);
                this->setActiveIndexes();
                if (this->getSelectedTrackIndex() == -1 && !this->playlist->is_stopped()) {
                    this->stopPlayback();
                }
            }
            else if (!name.compareIgnoreCase(juce::String("shift track up button"))) {
                // moving track up in the playlist
                if (curr_cmdl_sel <= 0) return;
                if (this->acquire_playlist_write_lock()) return;
                this->playlist->move_command_list(curr_cmdl_sel - 1, curr_cmdl_sel);
                this->release_playlist_write_lock();
                this->setActiveIndexes();
                this->selectPlaylistTreeIndex(curr_cmdl_sel - 1, true);
                this->reloadPlaylistTree(true);
            }
            else if (!name.compareIgnoreCase(juce::String("shift track down button"))) {
                // moving track down in the playlist
                if (curr_cmdl_sel >= this->playlist->command_list_count - 1) return;
                if (this->acquire_playlist_write_lock()) return;
                this->playlist->move_command_list(curr_cmdl_sel + 1, curr_cmdl_sel);
                this->release_playlist_write_lock();
                this->setActiveIndexes();
                this->selectPlaylistTreeIndex(curr_cmdl_sel + 1, true);
                this->reloadPlaylistTree(true);
            }
            else if (!name.compareIgnoreCase(juce::String("loop playlist button"))) {
                // track loop pressed
                this->playlist->loop = button->getToggleState();
                this->playlist->shuffle &= this->playlist->loop;
            }
            else if (!name.compareIgnoreCase(juce::String("play shuffled button"))) {
                // track shuffle pressed
                this->playlist->shuffle = button->getToggleState();
                this->playlist->loop |= this->playlist->shuffle;
            }
            else {
                // something to do with command lists

                curr_cmdl_sel     = this->playlist->curr_command_list();
                int curr_cmd_sel  = this->getSelectedCommandIndex();
                Command *cmd      = this->playlist->get_command(curr_cmd_sel, curr_cmdl_sel);
                bool redraw_only  = true;

                if (!name.compareIgnoreCase(juce::String("add command button"))) {
                    // adding command to the command list
                    if (this->acquire_playlist_write_lock()) return;
                    this->playlist->add_command(curr_cmdl_sel);
                    this->release_playlist_write_lock();
                    this->reloadCommandsButtons();
                    redraw_only = false;
                }

                if (cmd != NULL && curr_cmd_sel >= 0) {
                    if      (!name.compareIgnoreCase(juce::String("play ordered button"))) {
                        // command "normal" pressed
                        cmd->ordered = button->getToggleState();
                        if (cmd->ordered) cmd->any = false;
                        this->reloadCommandsButtons();
                    }
                    else if (!name.compareIgnoreCase(juce::String("play any button"))) {
                        // command "any" pressed
                        cmd->any = button->getToggleState();
                        if (cmd->any) cmd->ordered = false;
                        this->reloadCommandsButtons();
                    }
                    else if (!name.compareIgnoreCase(juce::String("play endless button"))) {
                        // command "endless" pressed
                        cmd->endless_loop = button->getToggleState();
                    }
                    else if (!name.compareIgnoreCase(juce::String("play alt button"))) {
                        // command "alt" pressed
                        SndTag *snd_tag     = playlist->get_snd_tag(LsndSectionType::loop, false);
                        SndTag *snd_tag_alt = playlist->get_snd_tag(LsndSectionType::loop, true);
                        bool new_alt_state = button->getToggleState();
                        if (snd_tag == NULL && !new_alt_state && snd_tag_alt != NULL) {
                            button->setToggleState(true, dontSendNotification);
                        }
                        else if (snd_tag_alt == NULL && new_alt_state && snd_tag != NULL) {
                            button->setToggleState(false, dontSendNotification);
                        }
                        else {
                            cmd->alt = new_alt_state;
                        }
                        this->reloadCommandsButtons();  // reload the perm slider maxvalue
                    }
                    else if (!name.compareIgnoreCase(juce::String("skip button"))) {
                        // command "skip" pressed
                        cmd->skip = button->getToggleState();
                    }
                    else if (!name.compareIgnoreCase(juce::String("remove command button"))) {
                        // removing command from the command list
                        if (this->acquire_playlist_write_lock()) return;
                        this->playlist->remove_command(curr_cmd_sel, curr_cmdl_sel);
                        this->release_playlist_write_lock();
                        this->setActiveIndexes();
                        this->selectCommandsTreeIndex(max(curr_cmd_sel - 1, 0));
                        this->reloadCommandsButtons();
                        redraw_only = false;
                    }
                    else if (!name.compareIgnoreCase(juce::String("shift command up button"))) {
                        // moving command up in the command list
                        if (curr_cmd_sel <= 0) return;
                        if (this->acquire_playlist_write_lock()) return;
                        this->playlist->move_command(curr_cmd_sel - 1, curr_cmd_sel);
                        this->release_playlist_write_lock();
                        this->setActiveIndexes();
                        this->selectCommandsTreeIndex(curr_cmd_sel - 1, true);
                    }
                    else if (!name.compareIgnoreCase(juce::String("shift command down button"))) {
                        // moving command down in the command list
                        if (curr_cmd_sel >= cmdl->command_count - 1) return;
                        if (this->acquire_playlist_write_lock()) return;
                        this->playlist->move_command(curr_cmd_sel + 1, curr_cmd_sel);
                        this->release_playlist_write_lock();
                        this->setActiveIndexes();
                        this->selectCommandsTreeIndex(curr_cmd_sel + 1, true);
                    }
                }

                this->reloadCommandsTree(redraw_only);
                return;
            }
            this->reloadPlaylistButtons();
        }
    }

    void sliderValueChanged(juce::Slider *slider) {
        if (slider == NULL || slider == nullptr) return;
        juce::String name = slider->getName();

        double val = slider->getValue();

        if (!name.compareIgnoreCase(juce::String("volume slider"))) {
            // volume slider changed
            this->setVolume((float)val/100);
        }
        else {
            if (this->playlist == NULL)       return;
            if (!this->playlist->is_valid())  return;

            int curr_cmdl_sel = this->getSelectedTrackIndex();
            CommandList *cmdl = this->playlist->get_command_list(curr_cmdl_sel);

            if (!name.compareIgnoreCase(juce::String("playtime slider"))) {
                // playtime slider changed
                if (cmdl == NULL) return;
                if (0.0 <= val && val <= (double)0xFFFFFFFF) cmdl->play_length = (uint32)val;
            }
            else {
                int curr_cmd_sel = this->getSelectedCommandIndex();
                Command *cmd = this->playlist->get_command(curr_cmd_sel);

                if (cmd == NULL || curr_cmd_sel < 0) return;

                if      (!name.compareIgnoreCase(juce::String("permutation to play slider"))) {
                    // permutation slider changed
                    SndTag *snd_tag = playlist->get_snd_tag(this->playlist->curr_section, cmd->alt);
                    if (snd_tag == NULL) {
                        slider->setValue((double)cmd->perm_index + 1, dontSendNotification);
                    }
                    else if (1.0 <= val && val <= (double)(snd_tag->max_actual_perm() + 1)) {
                        cmd->perm_index = ((sint16)val) - 1;
                    }
                }
                else if (!name.compareIgnoreCase(juce::String("loop command count slider"))) {
                    // repeat count slider changed
                    if (1.0 <= val && val <= (double)(COMMAND_LOOP_MAX + 1)) {
                        cmd->loop_count = ((uint32)val) - 1;
                    }
                }
                else {
                    return;
                }
                this->reloadCommandsTree(true);
            }
        }
    }

    void updatePlayInfo() {
        PlaylistPanel *playlist_panel = (PlaylistPanel *)this->controls_panel.tabbedWindows->getTabContentComponent(0);
        CommandsPanel *commands_panel = (CommandsPanel *)this->controls_panel.tabbedWindows->getTabContentComponent(1);
        playlist_panel->timePlayedLabel->setText(juce::String((int)playlist->play_timer()), dontSendNotification);
        commands_panel->currentLoopLabel->setText(juce::String(playlist->loop_iteration + 1), dontSendNotification);
        commands_panel->currentPermLabel->setText(juce::String(playlist->curr_perm() + 1), dontSendNotification);
        setActiveIndexes();

        CommandList *cmdl = this->playlist->get_command_list();
        juce::DocumentWindow *main_window = (juce::DocumentWindow *)(this->getParentComponent());
        if (cmdl == NULL) {
            main_window->setName(ProjectInfo::projectName);
        } else {
            main_window->setName(ProjectInfo::projectName + juce::String(":  ") + juce::String(cmdl->lsnd_path));
        }
    }

    void updateTreeSelections() {
        if (this->acquire_playlist_read_lock()) return;
        if (this->playlist->curr_command_list() != this->getSelectedTrackIndex()) {
            this->selectPlaylistTreeIndex(this->playlist->curr_command_list());
        }
        this->release_playlist_read_lock();
        // make sure the sliders are always up to date
        this->reloadCommandsButtons();
        // make sure the tree is always properly displayed
        this->controls_panel.tabbedWindows->getTabContentComponent(0)->repaint();
        this->controls_panel.tabbedWindows->getTabContentComponent(1)->repaint();
    }

    //==============================================================================
    int getSelectedTrackIndex() {
        PlaylistPanel *playlist_panel = (PlaylistPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(0));
        TreeView     *tree = playlist_panel->playlistTree;
        TreeViewItem *root = tree->getRootItem();
        int item_ct = root->getNumSubItems();
        for (int i = 0; i < item_ct; i++) {
            if (root->getSubItem(i)->isSelected()) return i;
        }
        return -1;
    }

    int getSelectedCommandIndex() {
        CommandsPanel *commands_panel = (CommandsPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(1));
        TreeView     *tree = commands_panel->commandsTree;
        TreeViewItem *root = tree->getRootItem();
        int item_ct = root->getNumSubItems();
        for (int i = 0; i < item_ct; i++) {
            if (root->getSubItem(i)->isSelected()) return i;
        }
        return -1;
    }

    void setActiveIndexes() {
        if (this->playlist == NULL) return;
        if (this->acquire_playlist_read_lock()) return;
        this->active_track   = this->playlist->curr_command_list();
        this->active_command = this->playlist->curr_command();
        this->release_playlist_read_lock();
    }

    void loadPlaylistToWidgets() {
        this->reloadSettingsWidgets();

        // select the first track in the playlist
        this->reloadPlaylistTree();
        this->selectPlaylistTreeIndex(0);

        this->reloadPlaybackButtons();
    }

    //==============================================================================
    void reloadSettingsWidgets() {
        SettingsPanel *settings_panel = (SettingsPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(2));

        if (this->config->get_playlists_dir() != NULL){
            settings_panel->playlistsDir->setText(juce::String(this->config->get_playlists_dir()));
        }

        if (this->playlist == NULL) return;
        if (this->acquire_playlist_read_lock()) return;
        if (this->playlist->get_tags_dir() != NULL) {
            settings_panel->playlistTagsDir->setText(juce::String(this->playlist->get_tags_dir()));
        } else {
            settings_panel->playlistTagsDir->setText(juce::String(""));
        }
        if (this->playlist->get_filepath() != NULL) {
            settings_panel->playlistPath->setText(juce::String(this->playlist->get_filepath()));
        } else {
            settings_panel->playlistPath->setText(juce::String(""));
        }
        this->release_playlist_read_lock();
    }

    void reloadPlaybackButtons() {
        if (this->playlist == NULL) return;
        PlaybackPanel *playback_panel = (PlaybackPanel *)(this->controls_panel.playbackPanel);
        if (this->playlist->is_paused() || this->playlist->is_stopped()) {
            playback_panel->playButton->setButtonText(juce::String("Play"));
        } else {
            playback_panel->playButton->setButtonText(juce::String("Pause"));
        }
    }

    void selectPlaylistTreeIndex(int index, bool force_reselect = false) {
        bool no_playlist = this->playlist == NULL;
        if (!no_playlist) no_playlist = !this->playlist->is_valid();
        if (no_playlist) return;

        PlaylistPanel *playlist_panel = (PlaylistPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(0));
        TreeView      *tree = playlist_panel->playlistTree;
        TreeViewItem  *root = tree->getRootItem();

        if (index >= root->getNumSubItems()) return;

        if (this->getSelectedTrackIndex() != index || force_reselect) {
            // clear the selections and select the specified index
            if (index >= 0) {
                root->getSubItem(index)->setSelected(true, true);
            } else {
                tree->clearSelectedItems();
            }
        }
        root->treeHasChanged();
        this->reloadPlaylistButtons();
        this->reloadCommandsTree();
        this->selectCommandsTreeIndex(0);
        this->reloadCommandsButtons();
    }

    void reloadPlaylistTree(bool redraw_only = false) {
        bool no_playlist = this->playlist == NULL;
        if (!no_playlist) no_playlist = !this->playlist->is_valid();

        int curr_cmdl_sel = this->getSelectedTrackIndex();
        PlaylistPanel *playlist_panel = (PlaylistPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(0));
        TreeView      *tree = playlist_panel->playlistTree;
        TreeViewItem  *root = tree->getRootItem();

        if (no_playlist) return;

        CommandList *cmdls = this->playlist->command_lists;
        if (cmdls == NULL) {
            root->clearSubItems();
            return;
        }

        if (this->acquire_playlist_read_lock()) return;
        if (redraw_only) {
            for (int i = min(this->playlist->command_list_count, root->getNumSubItems()) - 1; i >= 0; i--) {
                TextTreeItem *item = ((TextTreeItem *)root->getSubItem(i));
                juce::String new_string;

                if (!is_valid_command_list(&cmdls[i])) {
                    new_string = juce::String("<INVALID>");
                } else if (cmdls[i].lsnd_tag == NULL) {
                    new_string = juce::String("MISSING") + juce::String(cmdls[i].lsnd_path);
                } else {
                    new_string = juce::String(cmdls[i].lsnd_path);
                }
                item->text = new_string;
            }
        } else {
            root->clearSubItems();
            for (int i = 0; i < this->playlist->command_list_count; i++) {
                if (!is_valid_command_list(&cmdls[i])) {
                    root->addSubItem(new TextTreeItem("<INVALID>"), i);
                } else if (cmdls[i].lsnd_tag == NULL) {
                    root->addSubItem(new TextTreeItem(
                        juce::String("MISSING: ") + juce::String(cmdls[i].lsnd_path)), i);
                } else {
                    root->addSubItem(new TextTreeItem(cmdls[i].lsnd_path), i);
                }
                TextTreeItem *new_item = (TextTreeItem *)(root->getSubItem(i));

                new_item->active_index = &this->active_track;
                new_item->callback_object = this;
                new_item->click_callback = &trackClickedCallback;
                new_item->double_click_callback = &trackDoubleClickedCallback;

                if (i == curr_cmdl_sel) {
                    new_item->setSelected(true, true);
                }
            }
        }
        this->release_playlist_read_lock();
        this->reloadPlaylistButtons();
        root->treeHasChanged();
    }

    void reloadPlaylistButtons() {
        int curr_cmdl_sel = this->getSelectedTrackIndex();

        bool no_playlist = this->playlist == NULL;
        if (!no_playlist) no_playlist = !this->playlist->is_valid();
        PlaylistPanel *playlist_panel = (PlaylistPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(0));

        if (no_playlist) return;

        CommandList *cmdl = this->playlist->get_command_list(curr_cmdl_sel);
        if (cmdl != NULL) playlist_panel->playtimeSlider->setValue((double)cmdl->play_length);
        playlist_panel->loopPlaylistButton->setToggleState(this->playlist->loop,    dontSendNotification);
        playlist_panel->playShuffledButton->setToggleState(this->playlist->shuffle, dontSendNotification);
    }

    void selectCommandsTreeIndex(int index, bool force_reselect = false) {
        int curr_cmdl_sel = this->getSelectedTrackIndex();
        int curr_cmd_sel  = this->getSelectedCommandIndex();
        if (curr_cmdl_sel < 0) return;
        CommandsPanel *commands_panel = (CommandsPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(1));
        TreeView     *tree = commands_panel->commandsTree;
        TreeViewItem *root = tree->getRootItem();

        if (index >= root->getNumSubItems()) return;

        if (curr_cmd_sel != index || force_reselect) {
            // clear the selections and select the specified index
            if (index >= 0) root->getSubItem(index)->setSelected(true, true);
        }
        root->treeHasChanged();
    }

    void reloadCommandsTree(bool redraw_only = false) {
        bool no_playlist = this->playlist == NULL;
        if (!no_playlist) no_playlist = !this->playlist->is_valid();
        if (no_playlist) return;

        if (this->acquire_playlist_read_lock()) return;

        int curr_cmdl_sel = this->playlist->curr_command_list();
        int curr_cmd_sel  = this->getSelectedCommandIndex();
        CommandsPanel *commands_panel = (CommandsPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(1));
        TreeView      *tree = commands_panel->commandsTree;
        TreeViewItem  *root = tree->getRootItem();

        CommandList *cmdl = this->playlist->get_command_list(curr_cmdl_sel);
        if (!is_valid_command_list(cmdl)) {
            root->clearSubItems();
            this->release_playlist_read_lock();
            return;
        }

        if (redraw_only) {
            for (int i = min(cmdl->command_count, root->getNumSubItems()) - 1; i >= 0; i--) {
                Command *cmd = &cmdl->commands[i];
                TextTreeItem *item = ((TextTreeItem *)root->getSubItem(i));
                item->text = get_command_text_string(cmd);
            }
        } else {
            root->clearSubItems();

            for (int i = 0; i < cmdl->command_count; i++) {
                Command *cmd = &cmdl->commands[i];
                root->addSubItem(new TextTreeItem(get_command_text_string(cmd)), i);

                if (!is_valid_command(cmd)) continue;

                TextTreeItem *new_item = (TextTreeItem *)(root->getSubItem(i));
                new_item->active_index    = &this->active_command;
                new_item->callback_object = this;
                new_item->click_callback  = &commandClickedCallback;
                new_item->double_click_callback = &commandDoubleClickedCallback;

                if (i == curr_cmd_sel) {
                    new_item->setSelected(true, true);
                }
            }
            this->selectCommandsTreeIndex(curr_cmd_sel);
        }
        this->release_playlist_read_lock();
        root->treeHasChanged();
    }

    void reloadCommandsButtons() {
        bool no_playlist = this->playlist == NULL;
        if (!no_playlist) no_playlist = !this->playlist->is_valid();

        if (this->acquire_playlist_read_lock()) return;
        int curr_cmdl_sel = this->playlist->curr_command_list();
        int curr_cmd_sel  = this->getSelectedCommandIndex();
        CommandsPanel *commands_panel = (CommandsPanel *)(this->controls_panel.tabbedWindows->getTabContentComponent(1));
        Command       *cmd = this->playlist->get_command(curr_cmd_sel, curr_cmdl_sel);
        if (!is_valid_command(cmd)) {
            this->release_playlist_read_lock();
            return;
        }

        SndTag *snd_tag = this->playlist->get_snd_tag(LsndSectionType::loop, cmd->alt);

        commands_panel->loopCommandCountSlider->setValue((double)(cmd->loop_count + 1));
        if (snd_tag != NULL) {
            commands_panel->permutationToPlaySlider->setRange(1, (double)snd_tag->max_actual_perm() + 1, 1);
        }
        commands_panel->permutationToPlaySlider->setValue((double)(cmd->perm_index + 1));

        commands_panel->playAltButton->setToggleState(cmd->alt, dontSendNotification);
        commands_panel->playAnyButton->setToggleState(cmd->any, dontSendNotification);
        commands_panel->playEndlessButton->setToggleState(cmd->endless_loop, dontSendNotification);
        commands_panel->playOrderedButton->setToggleState(cmd->ordered, dontSendNotification);
        commands_panel->skipButton->setToggleState(cmd->skip, dontSendNotification);
        this->release_playlist_read_lock();

    }

    //==============================================================================
    void startPlayback() {
        if (this->playlist == NULL)        return;
        if (!this->playlist->is_valid())   return;
        if (!this->playlist->is_stopped()) return;

        if (this->acquire_playlist_read_lock()) return;

        if (this->playlist->curr_command_list() < 0) {
            // if no command list is selected, increment to one
            playlist->inc_command_list();
        }

        this->playlist->play();
        this->release_playlist_read_lock();

        setActiveIndexes();
        this->reloadPlaybackButtons();
        this->reloadCommandsTree();

        this->updatePlayInfo();
        setAudioChannels(0, 2);
    }

    void resumePlayback() {
        if (this->playlist == NULL)       return;
        if (!this->playlist->is_valid())  return;
        if (!this->playlist->is_paused()) return;
        if (this->playlist->is_stopped()) return;

        if (this->playlist->is_paused()) {
            this->playlist->resume_timers();
        }

        this->reloadPlaybackButtons();
        this->updatePlayInfo();
        setAudioChannels(0, 2);
    }

    void pausePlayback() {
        if (this->playlist == NULL)      return;
        if (!this->playlist->is_valid()) return;

        this->playlist->pause();
        this->reloadPlaybackButtons();
        this->shutdownAudio();
    }

    void stopPlayback() {
        if (this->playlist == NULL)      return;
        if (!this->playlist->is_valid()) return;

        if (this->acquire_playlist_read_lock()) return;
        this->delete_curr_samples = true;
        this->playlist->stop();
        this->release_playlist_read_lock();

        setActiveIndexes();
        this->reloadPlaybackButtons();
        this->updatePlayInfo();
        this->shutdownAudio();
    }

    //==============================================================================
    bool acquire_playlist_read_lock() {
        uint32 timeout = 0;
        while (this->lock_playlist_reading) {
            if (timeout > 100) return true;
            Sleep(1);
            timeout++;
        }
        return false;
    }

    bool acquire_playlist_write_lock() {
        uint32 timeout = 0;
        while (this->playlist_reader_count) {
            if (timeout > 100) return true;
            Sleep(1);
            timeout++;
        }
        this->lock_playlist_reading = true;
        return false;
    }

    bool release_playlist_read_lock() {
        if (!this->playlist_reader_count) return true;
        this->playlist_reader_count--;
        if (this->playlist_reader_count < 0) this->playlist_reader_count = 0;
        return false;
    }

    bool release_playlist_write_lock() {
        if (!this->lock_playlist_reading) return true;
        this->lock_playlist_reading = false;
        return false;
    }

    //==============================================================================
    void prepareToPlay (int samples_per_block_expected, double sample_rate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
    }

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        if (this->delete_curr_samples) {
            // exhausted the current samples
            delete this->curr_samples;
            this->curr_samples = NULL;
            this->delete_curr_samples = false;
        }

        if (this->acquire_playlist_read_lock()) return;

        if (this->playlist == NULL || this->resampler == nullptr) return;
        if (this->playlist->is_paused() || this->playlist->is_stopped()) {
            bufferToFill.clearActiveBufferRegion();
            this->release_playlist_read_lock();
            return;
        }

        this->deviceManager.getAudioDeviceSetup(setup);
        double  out_rate = this->setup.sampleRate;
        double  in_rate;
        double  rate_ratio;
        bool    end_track = false;
        float   fade_scale = 1.0;
        float   fade_in_end  = this->playlist->fade_in_end();
        float   fade_out_end = this->playlist->fade_out_end();

        if (this->playlist->fade_in() && fade_in_end != 0.0) {
            fade_scale = (float)abs(this->playlist->play_timer() / fade_in_end);
        } else if (this->playlist->fade_out() && fade_out_end != 0.0) {
            fade_scale = (float)(1.0 - abs(this->playlist->fade_out_timer() / fade_out_end));
        }

        fade_scale = (float)max(0.0, min(1.0, (double)fade_scale));

        float  *i_samples;
        float  *o_samples;
        uint32  req_samp_ct = bufferToFill.numSamples;
        uint32  o_channels  = (uint32)bufferToFill.buffer->getNumChannels();
        uint32  out_samp_i  = 0;  // the index of the last sample given to the buffer to fill

        // make sure we dont stack smash
        if (o_channels > 16 || o_channels == 0) {
            this->release_playlist_read_lock();
            return;
        }

        // allocate some temp pointers so we dont have to know channel counts at compile time
        float **buffers = (float **)alloca(sizeof(float *) * o_channels);

        // Get a pointer to the start sample in the buffer for each audio output channel
        for (uint32 j = 0; j < o_channels; j++) {
            buffers[j] = bufferToFill.buffer->getWritePointer(j, bufferToFill.startSample);
        }

        //this->updatePlayInfo();
        MessageManager::callAsync(std::bind(&MainContentComponent::updatePlayInfo, this));

        for (;;) {
            if (fade_scale <= 0.0) break;

            // loop here until the number of samples being requested have been given
            // loop will break at the bottom if the sample buffer has been filled.
            if (this->playlist == NULL) break;

            if (this->curr_samples == NULL) {
                // need to get the next samples to decode
                int prev_cmd = this->playlist->curr_command();
                this->curr_samples = this->playlist->get_next_samples();
                if (this->curr_samples == NULL) {
                    // if the samples are still NULL and playback isnt paused/stopped,
                    // then we need to increment to the next track in the playlist.
                    end_track = true;
                    break;
                }

                in_rate    = this->curr_samples->sample_rate;
                rate_ratio = in_rate / out_rate;
                if (abs(rate_ratio - this->resampler->getResamplingRatio()) > 0.0001) {
                    // change the sample rate if it differs too much
                    bufferToFill.clearActiveBufferRegion();
                    this->resampler->setResamplingRatio(rate_ratio);
                    this->release_playlist_read_lock();
                    return;
                }

                if (prev_cmd != this->playlist->curr_command()) {
                    MessageManager::callAsync(std::bind(&MainContentComponent::updateTreeSelections, this));
                }
            }

            uint32  i_channels = this->curr_samples->channel_count;
            uint32  channels = min(i_channels, o_channels);

            // decode the samples and make sure they could actually be decoded
            this->curr_samples->decode_to_pcm_float32(req_samp_ct);
            if (this->curr_samples->decoded_sample_data == NULL) {
                end_track = true;
                break;
            }

            uint32  i = 0;
            uint32  samps_to_give = min(this->curr_samples->decoded_sample_count(), req_samp_ct);
            // copy the decoded samples into the buffer
            for (uint32 c = 0; c < channels; c++) {
                // sample data is interleaved, so we need to iterate over it like so.
                i_samples = c + (float *)this->curr_samples->decoded_sample_data;
                o_samples = buffers[c] + out_samp_i;

                for (i = 0; i < samps_to_give; i++) {
                    o_samples[i] = fade_scale * i_samples[i * i_channels];
                }
            }
            out_samp_i += samps_to_give;

            if (this->curr_samples->decoding_finished()) {
                // exhausted the current samples
                delete this->curr_samples;
                this->curr_samples = NULL;
            }

            // break if we supplied the number of samples required.
            if (out_samp_i >= req_samp_ct) break;

            // subtract the number of samples we gave on this pass from how many are requested
            req_samp_ct -= samps_to_give;
        }
        this->release_playlist_read_lock();

        if (end_track || fade_scale <= 0.0) {
            this->delete_curr_samples = true;
            this->playlist->stop();
            this->playlist->inc_command_list();
            if (this->playlist->get_lsnd_tag() != NULL) this->playlist->play();
            MessageManager::callAsync(std::bind(&MainContentComponent::updateTreeSelections, this));
            MessageManager::callAsync(std::bind(&MainContentComponent::reloadPlaybackButtons, this));
            MessageManager::callAsync(std::bind(&MainContentComponent::updatePlayInfo, this));
        }

        this->setActiveIndexes();
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }

    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        controls_panel.setBounds(proportionOfWidth (0.0f), proportionOfHeight (0.0f),
                                 proportionOfWidth (1.0f), proportionOfHeight (1.0f));
    }

    void setAudioChannels(int numInputChannels, int numOutputChannels, const XmlElement* const xml = nullptr)
    {
        String audioError = deviceManager.initialise(numInputChannels, numOutputChannels, xml, true);
        jassert(audioError.isEmpty());

        deviceManager.addAudioCallback(&audioSourcePlayer);
        audioSourcePlayer.setSource(this->resampler);
    }

    void shutdownAudio()
    {
        audioSourcePlayer.setSource(nullptr);
        deviceManager.removeAudioCallback(&audioSourcePlayer);
        deviceManager.closeAudioDevice();
    }


    Playlist            *playlist;
    SoundSamples        *curr_samples;

    bool                 delete_curr_samples;

    AudioDeviceManager   deviceManager;

private:
    //==============================================================================

    // Your private member variables go here...
    juce::ResamplingAudioSource *resampler;
    juce::AudioSourcePlayer      audioSourcePlayer;
    juce::AudioDeviceManager::AudioDeviceSetup setup;

    ControlsPanel   controls_panel;
    ComposerConfig *config;
    char           *working_dir;

    int             active_track;
    int             active_command;
    uint32          playlist_reader_count;
    bool            lock_playlist_reading;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

void trackClickedCallback(void *object, int index) {
    auto *app = (MainContentComponent *)object;
    app->selectPlaylistTreeIndex(index);
}

void trackDoubleClickedCallback(void *object, int index) {
    auto *app = (MainContentComponent *)object;
    app->selectPlaylistTreeIndex(index);
    app->stopPlayback();
    app->playlist->select_command_list(index);
    app->startPlayback();
}

void commandClickedCallback(void *object, int index) {
    auto *app = (MainContentComponent *)object;
    app->reloadCommandsButtons();
}

void commandDoubleClickedCallback(void *object, int index) {
    auto *app = (MainContentComponent *)object;
    app->selectCommandsTreeIndex(index);
    app->reloadCommandsButtons();
    if (app->playlist == NULL)       return;
    if (!app->playlist->is_valid())  return;

    app->stopPlayback();

    // play the selected permutation
    app->startPlayback();
    app->playlist->curr_section = LsndSectionType::loop;
    app->playlist->select_command(index);

    app->setActiveIndexes();
    app->reloadPlaybackButtons();
}

juce::String get_command_text_string(Command *cmd) {
    juce::String name = juce::String();
    if (is_valid_command(cmd)) {
        if (cmd->skip) name += "SKIP ";
        else           name += "PLAY ";

        if (cmd->any) {
            name += ": any ";
        } else if (cmd->ordered) {
            name += ": normal ";
        } else {
            name += ": perm ";
            name += juce::String(cmd->perm_index + 1);
            name += " ";
        }

        if (cmd->alt) name += ": alt ";

        if (cmd->endless_loop) {
            name += ": endlessly ";
        } else {
            name += ": ";
            name += juce::String(cmd->loop_count + 1);
            if (cmd->loop_count == 0) name += " time ";
            else                      name += " times ";
        }
    } else {
        name += "<invalid command>";
    }
    return name;
}

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
