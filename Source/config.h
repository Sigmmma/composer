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
#include "util/constants.h"

const uint32 CONFIG_HEADER_SIG  = FOURCC('?', 'p', 'm', 'C');
const uint32 CONFIG_HEADER_SIZE = 128;

#if defined(_WIN32)
const char DEF_CONFIG_NAME[] = "composer_config.cfg";
#else
const char DEF_CONFIG_NAME[] = ".composer_config.cfg";
#endif


typedef struct ConfigData {
    uint32 sig;          // should be CONFIG_HEADER_SIG
    uint32 header_size;  // should be sizeof(ConfigData)
    uint32 tags_dir_len; // should be strlen(ConfigData->tags_dir)
    char  *tags_dir;
    uint32 last_playlist_len; // should be strlen(ConfigData->last_playlist)
    char  *last_playlist;

    float  last_volume;

    uint32 playlists_dir_len;
    char  *playlists_dir;

    pad    slack_space[CONFIG_HEADER_SIZE - 4 * 9];
} ConfigData; DUMB_STATIC_ASSERT(sizeof(ConfigData) == CONFIG_HEADER_SIZE);

class ComposerConfig {
public:
    ComposerConfig();
    ComposerConfig(char *input_path);
    ~ComposerConfig();

    ConfigData *data;

    uint32      filepath_len;
    char       *filepath;

    bool    set_filepath(const char *new_path);
    char   *get_filepath();
    bool    set_tags_dir(const char *new_tags_dir);
    char   *get_tags_dir();
    bool    set_last_playlist(const char *new_last_playlist);
    char   *get_last_playlist();
    bool    set_playlists_dir(const char *new_playlists_dir);
    char   *get_playlists_dir();

    void    parse(char *input_path);
    size_t  serialize();

    void    new_config();
    void    erase_config();

    bool    is_valid();
};
