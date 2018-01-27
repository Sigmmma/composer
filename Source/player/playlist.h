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

#pragma once

#include "../tags/common.h"
#include "../tags/sound_looping.h"

const uint32 PLAYLIST_HEADER_SIG = FOURCC('y', 'a', 'l', 'P');
const uint32 COMMAND_LIST_SIG    = FOURCC('t', 's', 'l', 'C');
const uint32 COMMAND_SIG         = FOURCC('d', 'n', 'm', 'C');
const uint32 PLAYLIST_HEADER_SIZE = 64;
const uint32 COMMAND_LIST_SIZE    = 64;
const uint32 COMMAND_SIZE         = 16;
const uint32 COMMAND_LOOP_MAX     = 999;

typedef struct Command {
    uint32  sig;         // should be COMMAND_SIG

    sint16  perm_index;  // permutation index to play.

    sint16  unused0;

    uint32  loop_count   : 10; // number of extra loops to play. cap at COMMAND_LOOP_MAX
    uint32  endless_loop : 1;  // play the command endlessly. loop_count
                               // and play_end are ignored if this is set.
    uint32  any     : 1;  // play any permutation.
    uint32  alt     : 1;  // play alt_loop or alt_end(if available).
    uint32  ordered : 1;  // let the snd_tag choose which permutation to play
                          // by calling snd_tag->set_actual_perm_index(-1) and
                          // calling snd_tag->get_next_samples() until either
                          // the samples run out, the play_length is exceeded,
                          // or the loop_count is exceeded(measure by checking
                          // if samples->next_perm_index == -1(end of chain)).
    uint32  skip    : 1;  // skip this item. useful for disabling commands in
                          // a command_list without actually removing them.
    uint32  unused1 : 2;

    pad    slack_space[COMMAND_SIZE - 4*2 - 2*2];
} Command; DUMB_STATIC_ASSERT(sizeof(Command) == COMMAND_SIZE);

typedef struct CommandList {
    uint32        sig;           // should be COMMAND_LIST_SIG

    uint32        lsnd_path_len;
    pad           pad0[4];

    sint32        command_count; // signed to prevent sint32 comparison to uint32.
    pad           pad1[8];

    uint32        play_length;   // number of seconds to play this lsnd_tag
                                 // before switching to the next lsnd_tag.
                                 // this takes precedence over looping forever.
                                 // 0 == no play time limit
    // flags
    uint32        is_sound : 1;  // lsnd_path actually points to a SndTag, and
                                 // a fake LsndTag must be made to handle it.

    pad    slack_space[COMMAND_LIST_SIZE - 4 * 8 - sizeof(char *) * 3];

    char         *lsnd_path;     // tags_dir relative path to the lsnd_tag to play.
    Command      *commands;      // commands specifying which permutations to play.
    LsndTag      *lsnd_tag;      // the LsndTag this permlist governs playing.
} CommandList; DUMB_STATIC_ASSERT(sizeof(CommandList) == COMMAND_LIST_SIZE);

typedef struct PlaylistHeader {
    uint32       sig;                // should be PLAYLIST_HEADER_SIG

    uint32       tags_dir_len;
    pad          pad0[4];

    sint32       command_list_count; // signed to prevent sint32 comparison to uint32
    pad          pad1[4];

    // flags
    uint32       shuffle : 1;        // go through permlists in a random order.
    uint32       loop    : 1;        // endlessly play the permlists.
    uint32       unused  : 30;

    pad          slack_space[PLAYLIST_HEADER_SIZE - 4 * 6 - sizeof(char *) * 2];

    char        *tags_dir;           // tags_dir that all the lsnd_tags are located in.
    CommandList *command_lists;      // permlists specifying which lsnd_tags to play and how.

} PlaylistHeader; DUMB_STATIC_ASSERT(sizeof(PlaylistHeader) == PLAYLIST_HEADER_SIZE);


class Playlist {
public:
    Playlist();
    Playlist(char *);
    ~Playlist();

    sint32          command_list_count; // signed to prevent sint32 comparison to uint32
    CommandList    *command_lists;      // command lists specifying which lsnd_tags to play and how.

    size_t          filepath_len;
    char           *filepath;

    size_t          tags_dir_len;
    char           *tags_dir;      // tags_dir that all the lsnd_tags are located in.

    // flags
    uint16        shuffle        : 1;   // go through permlists in a random order.
    uint16        loop           : 1;   // endlessly play the permlists.
    uint16        loop_iteration : 10;  // [0, 1000]
    uint16        alt            : 1;   // whether or not we are playing alt sounds
    uint16        track          : 2;   // mostly just here for completeness
    uint16        unused1        : 1;

    LsndSectionType  curr_section;

protected:
    sint32        _curr_command_list;
    sint32        _curr_command;

    double        pause_start;  // millisec timestamp that the playback was paused at.
                                // if this value is positive, the playback is considered paused.
                                // otherwise, the playback is considered to be running.
    double        play_start;      // millisec timestamp that the current track started playing.
    double        fade_out_start;  // millisec timestamp that the current track started fading out.

public:
    char         *get_filepath();
    bool          set_filepath(const char *);

    char         *get_tags_dir();
    bool          set_tags_dir(const char *);
    bool          set_lsnd_tags_dirs();
    bool          set_lsnd_tags_dirs(char *new_tags_dir);

    char         *get_list_filepath();
    bool          set_list_filepath(const char *);

    int           curr_command_list();
    int           curr_command();
    sint16        curr_perm();

    double        play_timer();
    double        play_timer(double);
    double        fade_out_timer();
    double        fade_out_timer(double);
    double        fade_in_end();
    double        fade_out_end();
    bool          fade_in();
    bool          fade_out();

    void          pause_timers();
    void          resume_timers();
    bool          is_paused();
    bool          is_stopped();
    bool          is_playing();
    void          play();
    void          pause();
    void          stop();

    SoundSamples *get_next_samples();
    SndTag       *get_snd_tag();
    SndTag       *get_snd_tag(LsndSectionType section, bool use_alt);
    LsndTag      *get_lsnd_tag();
    LsndTag      *get_lsnd_tag(int);

    CommandList  *get_command_list();
    CommandList  *get_command_list(int);
    bool          inc_command_list();
    bool          select_command_list(int);
    bool          add_command_list();
    bool          add_command_list(SndTag *);
    bool          add_command_list(LsndTag *);
    bool          insert_command_list(int);
    bool          insert_command_list(int, SndTag *);
    bool          insert_command_list(int, LsndTag *);
    bool          remove_command_list();
    bool          remove_command_list(int);
    bool          move_command_list(int, int);

    Command      *get_command();
    Command      *get_command(int);
    Command      *get_command(int, int);
    bool          inc_command();
    bool          select_command(int);
    bool          add_command();
    bool          add_command(int);
    bool          insert_command(int);
    bool          insert_command(int, int);
    bool          remove_command();
    bool          remove_command(int);
    bool          remove_command(int, int);
    bool          move_command(int, int);
    bool          move_command(int, int, int);

    void    parse(char *);
    size_t  serialize();

    void    new_playlist();
    void    erase_playlist();

    bool    is_valid();
};

bool is_valid_command(Command *);
bool is_valid_command_list(CommandList *);
Command     *new_command();
CommandList *new_command_list();