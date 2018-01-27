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

#include "common.h"

class HaloTag {
public:
    HaloTag();
    HaloTag(char *data, long data_size, const char *new_filepath, const char *new_tags_dir);
    ~HaloTag();

    TagHeader *tag_header;
    TagClass   tag_class;
    size_t     tag_data_size;
    char      *tag_data;

    size_t     filepath_len;
    char      *filepath;

    size_t     tags_dir_len;
    char      *tags_dir;

    bool  is_valid();
    bool  set_filepath(const char *new_path);
    char *get_filepath();

    bool  set_tags_dir(const char *new_tags_dir);
    char *get_tags_dir();

};

HaloTag *load_tag_at_path(const char *path, const char *tags_dir);