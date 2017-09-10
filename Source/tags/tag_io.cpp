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

#include "common.h"
#include "tag_io.h"
#include <iostream>
#include <stdio.h>

#include "sound.h"
#include "sound_looping.h"
#include "../util/util.h"

using std::cout;

HaloTag::HaloTag() {
    this->tag_header = NULL;
    this->tag_data   = NULL;
    this->filepath   = NULL;
    this->tags_dir   = NULL;
    this->tag_data_size = 0;
    this->filepath_len = 0;
    this->tags_dir_len = 0;
}

HaloTag::HaloTag(char *data, long data_size, const char *new_filepath, const char *new_tags_dir) : HaloTag() {
    if ((data == NULL) || (new_filepath == NULL)) return;

    this->tag_header = (TagHeader*)data;
    this->tag_data   = data + TAG_HEADER_SIZE;
    this->tag_data_size = data_size - TAG_HEADER_SIZE;

    this->set_filepath(new_filepath);
    this->set_tags_dir(new_tags_dir);

    this->tag_class = this->tag_header->tag_class;
}

HaloTag::~HaloTag() {
    free(tag_header);
    // dont need to free tag_data as it is in the same buffer as tag_header
    free(this->filepath);
    free(this->tags_dir);
    this->tag_header = NULL;
    this->tag_data = NULL;
    this->filepath = NULL;
    this->tags_dir = NULL;
}

bool HaloTag::set_filepath(const char *new_path) {
    size_t new_alloc_len = strlen(new_path);
    char *new_alloc_path = (char *)malloc(new_alloc_len + 1);
    if (new_alloc_path == NULL) return true;

    // should probably do some checking to make sure the new_path
    // is a valid filepath before setting it.
    free(this->filepath);
    this->filepath_len = new_alloc_len;
    this->filepath = new_alloc_path;

    memcpy(this->filepath, new_path, new_alloc_len + 1);
    return false;
}

char *HaloTag::get_filepath() {
    if (!this->is_valid()) return NULL;

    return this->filepath;
}

bool HaloTag::set_tags_dir(const char *new_tags_dir) {
    char *new_alloc_path = copy_dir_string(new_tags_dir);
    if (new_alloc_path == NULL) return true;

    free(this->tags_dir);
    this->tags_dir_len = strlen(new_alloc_path);
    this->tags_dir = new_alloc_path;

    return false;
}

char *HaloTag::get_tags_dir() {
    if (!this->is_valid()) return NULL;

    return this->tags_dir;
}


bool HaloTag::is_valid() {
    return (this->tag_data != NULL &&
            this->filepath != NULL &&
            this->tags_dir != NULL &&
            this->tag_header != NULL);
}

HaloTag *load_tag_at_path(const char *path, const char *tags_dir) {
    if (path     == NULL) return NULL;
    if (tags_dir == NULL) return NULL;

    cout << "loading: " << path << '\n';
    if (!file_exists(path)) {
        // file doesnt exist
        return NULL;
    }

    FILE *tag_file = fopen(path, "rb");
    if (!tag_file) {
        // couldn't load the tag for some reason
        cout << "Could not load tag\n";
        return NULL;
    }

    fseek(tag_file, 0, SEEK_END);
    long length = ftell(tag_file);
    fseek(tag_file, 0, SEEK_SET);

    if (length > MAX_TAG_SIZE) {
        // max tag size exceeded
        cout << "Max size exceeded\n";
        fclose(tag_file);
        return NULL;
    } else if (length < TAG_HEADER_SIZE) {
        // tag isn't even large enough to parse its header
        cout << "Tag too small\n";
        fclose(tag_file);
        return NULL;
    }

    // copy the tag file into memory
    char *tag_buffer = (char *)malloc(length);
    fread(tag_buffer, length, 1, tag_file);
    fclose(tag_file);

    // byteswap the header and read it to determine the tag type
    TagHeader *tag_header = (TagHeader *)tag_buffer;
    byteswap_tag_header(*tag_header);

    if (tag_header->engine_id != ENGINE_ID_HALO_1) {
        // incorrect version for the engine. free the buffer we just made
        cout << "Engine ID does not match: \n";
        cout << tag_header->engine_id << " != " << ENGINE_ID_HALO_1 << '\n';
        free(tag_buffer);
        return NULL;
    }

    HaloTag *halo_tag;
    if (tag_header->tag_class == TAG_CLASS_SND) {
        halo_tag = new SndTag(tag_buffer, length, path, tags_dir);
    } else if (tag_header->tag_class == TAG_CLASS_LSND) {
        halo_tag = new LsndTag(tag_buffer, length, path, tags_dir);
    } else {
        halo_tag = new HaloTag(tag_buffer, length, path, tags_dir);
    }

    return halo_tag;
}

bool HaloTag::add_reflexive_entry(Reflexive *reflexive, uint32 entry_size) {
    /*
    DO NOT USE THIS METHOD!
    It will not work right with the way the current tag loading system works.
    */
    if (reflexive == NULL) return true;
    return this->insert_reflexive_entry(reflexive, entry_size, reflexive->size);
}
bool HaloTag::insert_reflexive_entry(Reflexive *reflexive, uint32 entry_size, sint32 index) {
    /*
    DO NOT USE THIS METHOD!
    It will not work right with the way the current tag loading system works.
    */
    if (index < 0) return true;
    if (reflexive == NULL) return true;
    if (index > reflexive->size) return true;

    char *new_entry = (char *)calloc(1, entry_size);
    if (new_entry == NULL) return true;

    // if the current command_list doesnt exist we just use the new one as it
    if (reflexive->pointer == NULL || reflexive->size == 0) {
        free((char *)reflexive->pointer);
        reflexive->pointer = (pointer32)new_entry;
        reflexive->size = 1;
        return false;
    }

    char *new_entries = (char *)realloc(
        (char *)reflexive->pointer, (reflexive->size + 1) * entry_size);
    if (new_entries == NULL) {
        // couldn't allocate memory for the larger reflexive array.
        // free the new_entry
        free(new_entry);
        return true;
    }

    size_t u_half_size = entry_size * (reflexive->size - index);
    if (u_half_size > 0) {
        // move the upper half of the array up 1 entry
        memmove(new_entries + ((index + 1) * entry_size),
                new_entries + (index * entry_size),
                u_half_size);
    }
    memcpy(new_entries + (index * entry_size), new_entry, entry_size);
    free(new_entry);

    reflexive->pointer = (pointer32)new_entries;
    reflexive->size++;

    return false;
}
bool HaloTag::remove_reflexive_entry(Reflexive *reflexive, uint32 entry_size, sint32 index) {
    // does not work yet
    return true;
}
bool HaloTag::move_reflexive_entry(Reflexive *reflexive, uint32 entry_size, sint32 src, sint32 dest) {
    // does not work yet
    return true;
}