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

#include "config.h"
#include "util/util.h"
#include <iostream>

using std::cout;


ComposerConfig::ComposerConfig() {
    // make sure these are null so erase_config doesnt free random memory
    this->data = nullptr;
    this->filepath = nullptr;
    this->new_config();
}

ComposerConfig::ComposerConfig(char *input_path) : ComposerConfig() {
    this->parse(input_path);
}

ComposerConfig::~ComposerConfig() {
    this->erase_config();
}

void ComposerConfig::erase_config() {
    if (this->data != nullptr) {
        free(this->data->tags_dir);
        free(this->data->last_playlist);
        free(this->data->playlists_dir);
    }

    free(this->data);
    free(this->filepath);
    this->data = nullptr;
    this->filepath = nullptr;
}

bool ComposerConfig::set_filepath(const char *new_path) {
    size_t new_alloc_len = strlen(new_path);
    char *new_alloc_path = (char *)malloc(new_alloc_len + 1);
    if (new_alloc_path == nullptr) return true;

    // should probably do some checking to make sure the new_path
    // is a valid filepath before setting it.
    free(this->filepath);
    this->filepath_len = new_alloc_len;
    this->filepath = new_alloc_path;

    memcpy(this->filepath, new_path, new_alloc_len + 1);
    return false;
}

char *ComposerConfig::get_filepath() { return this->filepath; }

bool ComposerConfig::set_tags_dir(const char *new_tags_dir) {
    char *new_alloc_path = copy_dir_string(new_tags_dir);
    if (new_alloc_path == nullptr) return true;

    free(this->data->tags_dir);
    this->data->tags_dir_len = strlen(new_alloc_path);
    this->data->tags_dir = new_alloc_path;
    return false;
}

char *ComposerConfig::get_tags_dir() {
    if (!this->is_valid()) return nullptr;
    return this->data->tags_dir;
}

bool ComposerConfig::set_last_playlist(const char *new_last_playlist) {
    size_t new_alloc_len = strlen(new_last_playlist);
    char *new_alloc_path = (char *)malloc(new_alloc_len + 1);
    if (new_alloc_path == nullptr) return true;

    // should probably do some checking to make sure the new_path
    // is a valid filepath before setting it.
    free(this->data->last_playlist);
    this->data->last_playlist_len = new_alloc_len;
    this->data->last_playlist     = new_alloc_path;

    memcpy(this->data->last_playlist, new_last_playlist, new_alloc_len + 1);
    return false;
}

char *ComposerConfig::get_last_playlist() {
    if (!this->is_valid()) return nullptr;
    return this->data->last_playlist;
}

bool ComposerConfig::set_playlists_dir(const char *new_playlists_dir) {
    char *new_alloc_path = copy_dir_string(new_playlists_dir);
    if (new_alloc_path == nullptr) return true;

    free(this->data->playlists_dir);
    this->data->playlists_dir_len = strlen(new_alloc_path);
    this->data->playlists_dir     = new_alloc_path;
    return false;
}

char *ComposerConfig::get_playlists_dir() {
    if (!this->is_valid()) return nullptr;
    return this->data->playlists_dir;
}

void ComposerConfig::new_config() {
    this->erase_config();
    this->data = (ConfigData *)calloc(1, sizeof(ConfigData));
    this->data->sig = CONFIG_HEADER_SIG;
    this->data->header_size = sizeof(ConfigData);
    this->data->last_volume = 1.0;

    char *working_dir = get_working_dir();
    if (working_dir == nullptr) return;

    this->set_filepath(strcpycat(working_dir, (char *)DEF_CONFIG_NAME));
    #if defined(__linux__) || defined(UNIX)
    this->set_tags_dir(strcpycat(working_dir, "tags/"));
    this->set_playlists_dir(strcpycat(working_dir, "playlists/"));
    #elif defined(_WIN32)
    this->set_tags_dir(strcpycat(working_dir, "tags\\"));
    this->set_playlists_dir(strcpycat(working_dir, "playlists\\"));
    #endif
    free(working_dir);

}

void ComposerConfig::parse(char *input_path) {
    FILE *cfg_file = fopen(input_path, "rb");
    long length = 0;

    if (!cfg_file) {
        // couldn't load the config for some reason
        cout << "Could not load config: " << input_path << '\n';
        return;
    }

    fseek(cfg_file, 0, SEEK_END);
    length = ftell(cfg_file);
    fseek(cfg_file, 0, SEEK_SET);

    if (length < CONFIG_HEADER_SIZE) {
        // not even large enough to parse the header
        return;
    }

    // copy the config file into memory
    ConfigData *new_cfg = (ConfigData *)calloc(CONFIG_HEADER_SIZE, 1);
    if (new_cfg == nullptr) return;
    fread(new_cfg, CONFIG_HEADER_SIZE, 1, cfg_file);

    if (new_cfg->tags_dir_len > MAX_CFG_STR_LEN
        || new_cfg->last_playlist_len > MAX_CFG_STR_LEN
        || new_cfg->playlists_dir_len > MAX_CFG_STR_LEN) {
        // max string size exceeded
        free(new_cfg);
        return;
    }

    // read the tags_dir, last_playlist, and playlists_dir into memory
    new_cfg->tags_dir      = (char *)malloc(new_cfg->tags_dir_len + 1);
    new_cfg->last_playlist = (char *)malloc(new_cfg->last_playlist_len + 1);
    new_cfg->playlists_dir = (char *)malloc(new_cfg->playlists_dir_len + 1);
    if (new_cfg->tags_dir == nullptr || new_cfg->last_playlist == nullptr || new_cfg->playlists_dir == nullptr) {
        free(new_cfg->tags_dir);
        free(new_cfg->last_playlist);
        free(new_cfg->playlists_dir);
        free(new_cfg);
        return;
    }

    fread(new_cfg->tags_dir, new_cfg->tags_dir_len + 1, 1, cfg_file);
    fread(new_cfg->last_playlist, new_cfg->last_playlist_len + 1, 1, cfg_file);
    fread(new_cfg->playlists_dir, new_cfg->playlists_dir_len + 1, 1, cfg_file);

    // make sure both strings are null terminated
    new_cfg->tags_dir[new_cfg->tags_dir_len] = 0;
    new_cfg->last_playlist[new_cfg->last_playlist_len] = 0;
    new_cfg->playlists_dir[new_cfg->playlists_dir_len] = 0;

    sanitize_path(new_cfg->tags_dir, true);
    sanitize_path(new_cfg->last_playlist, true);
    sanitize_path(new_cfg->playlists_dir, true);

    // erase any old config and replace it with the new one
    this->erase_config();
    this->data = new_cfg;

    this->set_filepath(input_path);
    fclose(cfg_file);

    if (!this->is_valid()) {
        // config wasn't properly formed. make a default blank one
        this->new_config();
    }
}

size_t ComposerConfig::serialize() {
    if (!this->is_valid()) return 0;

    FILE *cfg_file = fopen(this->filepath, "wb");

    if (!cfg_file) return 0;

    // write the config header
    fwrite(this->data, CONFIG_HEADER_SIZE, 1, cfg_file);
    if (this->data->tags_dir != nullptr) {
        fwrite(this->data->tags_dir, this->data->tags_dir_len + 1, 1, cfg_file);
    }
    if (this->data->last_playlist != nullptr) {
        fwrite(this->data->last_playlist, this->data->last_playlist_len + 1, 1, cfg_file);
    }
    if (this->data->playlists_dir != nullptr) {
        fwrite(this->data->playlists_dir, this->data->playlists_dir_len + 1, 1, cfg_file);
    }

    fseek(cfg_file, 0, SEEK_END);
    long length = ftell(cfg_file);
    fclose(cfg_file);

    return length;
}

bool ComposerConfig::is_valid() {
    if (this->data == nullptr || this->filepath == nullptr) {
        return false;
    } else if (this->data->sig != CONFIG_HEADER_SIG) {
        return false;
    }

    return true;
}
