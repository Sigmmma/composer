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

#include "sound.h"
#include "sound_looping.h"
#include "tag_io.h"
#include "../util/util.h"
#include <iostream>

using std::cout;

LsndTag::LsndTag() : HaloTag() {
    this->track_sounds  = NULL;
    this->detail_sounds = NULL;
    this->track_sound_count  = 0;
    this->detail_sound_count = 0;
}

LsndTag::LsndTag(char *data, long data_size, const char *new_filepath, const char *new_tags_dir) :
                 HaloTag(data, data_size, new_filepath, new_tags_dir) {
    this->track_sounds  = NULL;
    this->detail_sounds = NULL;
    this->track_sound_count  = 0;
    this->detail_sound_count = 0;
    this->parse();
}

LsndTag::~LsndTag() {
    this->unload_dependencies();
    free(this->track_sounds);
    free(this->detail_sounds);
}

void LsndTag::parse() {
    /*
    Parses an lsnd tag's buffer to byteswap everything to little endian
    and set pointers to reflexives, rawdata, and dependency paths.
    */
    this->unload_dependencies();

    DetailSound *d_sound;
    Track       *track;

    char *curr_pos = this->tag_data;
    LsndBody *tag_body = (LsndBody *)curr_pos;
    byteswap_lsnd_body(tag_body);

    // skip over the tag body
    curr_pos += sizeof(LsndBody);

    // set the pointer to the cdmg dependency and skip over it
    curr_pos = parse_dependency(&tag_body->continuous_damage_effect, curr_pos);

    if (tag_body->tracks.size > 0) {
        curr_pos = parse_reflexive(&tag_body->tracks, curr_pos,
                                   sizeof(Track));
        track = (Track *)get_tag_pointer(&tag_body->tracks);

        for (sint32 i = 0; i < tag_body->tracks.size; i++, track++) {
            byteswap_lsnd_track(track);
            curr_pos = parse_dependency(&track->start, curr_pos);
            curr_pos = parse_dependency(&track->loop, curr_pos);
            curr_pos = parse_dependency(&track->end, curr_pos);
            curr_pos = parse_dependency(&track->alt_loop, curr_pos);
            curr_pos = parse_dependency(&track->alt_end, curr_pos);
        }
    }

    if (tag_body->detail_sounds.size > 0) {
        curr_pos = parse_reflexive(&tag_body->detail_sounds, curr_pos,
                                   sizeof(DetailSound));
        d_sound = (DetailSound *)get_tag_pointer(&tag_body->detail_sounds);

        for (sint32 i = 0; i < tag_body->detail_sounds.size; i++, d_sound++) {
            byteswap_lsnd_detail_sound(d_sound);
            curr_pos = parse_dependency(&d_sound->sound, curr_pos);
        }
    }
    this->track_sound_count  = tag_body->tracks.size;
    this->detail_sound_count = tag_body->detail_sounds.size;
}

void LsndTag::serialize() {
    /*
    Any serializer functions will just be placeholders for now.
    */
    if (!this->is_valid()) return;
}

bool LsndTag::reset_sound_states() {
    LoadedTrack       *tracks   = this->track_sounds;
    //LoadedDetailSound *d_sounds = this->detail_sounds;
    if (tracks != NULL) {
        for (int i = 0; i < this->track_sound_count; i++) {
            if (tracks[i].start != NULL)    tracks[i].start->set_actual_perm_index(-1);
            if (tracks[i].loop != NULL)     tracks[i].loop->set_actual_perm_index(-1);
            if (tracks[i].end != NULL)      tracks[i].end->set_actual_perm_index(-1);
            if (tracks[i].alt_loop != NULL) tracks[i].alt_loop->set_actual_perm_index(-1);
            if (tracks[i].alt_end != NULL)  tracks[i].alt_end->set_actual_perm_index(-1);
        }
    } else {
        return true;
    }
    /*
    if (d_sounds != NULL) {
        for (int i = 0; i < this->detail_sound_count; i++) {
            if (d_sounds[i].sound != NULL) d_sounds[i].sound->set_actual_perm_index(-1);
        }
    }*/

    return false;
}

bool LsndTag::load_dependencies() {
    if (!this->is_valid()) return true;
    if (this->track_sounds != NULL && this->detail_sounds != NULL) return false;

    free(this->track_sounds);
    free(this->detail_sounds);
    this->track_sounds = (LoadedTrack *)calloc(
        this->track_sound_count, sizeof(LoadedTrack));
    this->detail_sounds = (LoadedDetailSound  *)calloc(
        this->detail_sound_count, sizeof(LoadedDetailSound));

    LsndBody    *lsnd_body = (LsndBody *)this->tag_data;
    Track       *tracks    = (Track*)get_tag_pointer(&lsnd_body->tracks);
    //DetailSound *d_sounds  = (DetailSound*)get_tag_pointer(&lsnd_body->detail_sounds);

    for (int i = 0; i < this->track_sound_count; i++) {
        if (this->track_sounds == NULL) break;

        this->track_sounds[i].flags = tracks->flags;
        this->track_sounds[i].gain  = tracks->gain;
        this->track_sounds[i].fade_in_duration  = tracks->fade_in_duration;
        this->track_sounds[i].fade_out_duration = tracks->fade_out_duration;

        if (this->track_sounds[i].start == NULL)
            this->track_sounds[i].start = (SndTag *)load_tag_at_path(
                strcpycat(this->tags_dir,
                    strcpycat((char *)get_tag_pointer(&tracks->start), ".sound"), 0, 1), this->tags_dir);

        if (this->track_sounds[i].loop == NULL)
            this->track_sounds[i].loop = (SndTag *)load_tag_at_path(
                strcpycat(this->tags_dir,
                    strcpycat((char *)get_tag_pointer(&tracks->loop), ".sound"), 0, 1), this->tags_dir);

        if (this->track_sounds[i].end == NULL)
            this->track_sounds[i].end = (SndTag *)load_tag_at_path(
                strcpycat(this->tags_dir,
                    strcpycat((char *)get_tag_pointer(&tracks->end), ".sound"), 0, 1), this->tags_dir);

        if (this->track_sounds[i].alt_loop == NULL)
            this->track_sounds[i].alt_loop = (SndTag *)load_tag_at_path(
                strcpycat(this->tags_dir,
                    strcpycat((char *)get_tag_pointer(&tracks->alt_loop), ".sound"), 0, 1), this->tags_dir);

        if (this->track_sounds[i].alt_end == NULL)
            this->track_sounds[i].alt_end = (SndTag *)load_tag_at_path(
                strcpycat(this->tags_dir,
                    strcpycat((char *)get_tag_pointer(&tracks->alt_end), ".sound"), 0, 1), this->tags_dir);
    }

    /*for (int i = 0; i < this->detail_sound_count; i++) {
        if (this->detail_sounds == NULL) break;

        this->detail_sounds[i].gain  = d_sounds->gain;
        this->detail_sounds[i].flags = d_sounds->flags;
        this->detail_sounds[i].random_period_bounds = d_sounds->random_period_bounds;

        if (this->detail_sounds[i].sound == NULL)
            this->detail_sounds[i].sound = (SndTag *)load_tag_at_path(
                strcpycat(this->tags_dir,
                    strcpycat((char *)get_tag_pointer(&d_sounds->sound), ".sound"), 0, 1), this->tags_dir);
    }*/
    return false;
}

void LsndTag::unload_dependencies() {
    if (this->track_sounds != NULL) {
        for (int i = 0; i < this->track_sound_count; i++) {
            delete this->track_sounds[i].start;
            delete this->track_sounds[i].loop;
            delete this->track_sounds[i].end;
            delete this->track_sounds[i].alt_loop;
            delete this->track_sounds[i].alt_end;
            this->track_sounds[i].start = NULL;
            this->track_sounds[i].loop = NULL;
            this->track_sounds[i].end = NULL;
            this->track_sounds[i].alt_loop = NULL;
            this->track_sounds[i].alt_end = NULL;
        }
        this->track_sounds = NULL;
    }

    if (this->detail_sounds != NULL) {
        // these aren't actually loaded, because the code that loads them
        // is commented out, so we dont actually need to do anything.
        /*for (int i = 0; i < this->detail_sound_count; i++) {
            delete this->detail_sounds[i].sound;
            this->detail_sounds[i].sound = NULL;
        }*/
        this->detail_sounds = NULL;
    }
}

void LsndTag::print() {
    if (!this->is_valid()) {
        cout << "Tag is invalid\n";
        return;
    }

    cout << "tag_path      == " << this->filepath << std::endl;
    cout << "tag_data_size == " << this->tag_data_size << std::endl;
    cout << "is_valid_tag  == " << this->is_valid() << std::endl;
    print_tag_header(*this->tag_header, 0);

    char *indent1 = make_indent_str(1);
    char *indent2 = make_indent_str(2);

    DetailSound *d_sound;
    Track *track;
    LsndBody *body = (LsndBody *)this->tag_data;

    cout << "{ tag_body, ptr == " << (&body) << '\n';
    cout << indent1 << "detail_sound_period_at_zero == "
        << (body->detail_sound_period_at_zero) << '\n';
    cout << indent1 << "detail_sound_period_at_one == "
        << (body->detail_sound_period_at_one) << '\n';

    //print_dependency(body->continuous_damage_effect, "continuous_damage_effect", 1);
    //print_reflexive(body->tracks, "tracks", 1);
    if (body->tracks.size > 0) {
        track = (Track *)get_tag_pointer(&body->tracks);

        for (sint32 i = 0; i < body->tracks.size; i++, track++) {
            cout << indent1 << "{ #" << i << " track, ptr == " << (&track) << '\n';
            cout << indent2 << "gain           == " << (track->gain) << '\n';
            cout << indent2 << "fade_in_time   == " << (track->fade_in_duration) << '\n';
            cout << indent2 << "fade_out_time  == " << (track->fade_out_duration) << '\n';
            print_dependency(track->start, "start", 2);
            print_dependency(track->loop, "loop", 2);
            print_dependency(track->end, "end", 2);
            print_dependency(track->alt_loop, "alt_loop", 2);
            print_dependency(track->alt_end, "alt_end", 2);
            cout << indent1 << "}\n";
        }
    }

    //print_reflexive(body->detail_sounds, "detail_sounds", 1);
    if (body->detail_sounds.size > 0) {
        d_sound = (DetailSound *)get_tag_pointer(&body->detail_sounds);

        for (sint32 i = 0; i < body->detail_sounds.size; i++, d_sound++) {
            cout << indent1 << "{ #" << i << " detail_sound, ptr == "
                << (&d_sound) << '\n';
            print_dependency(d_sound->sound, "sound", 2);
            cout << indent2 << "gain               == " << (d_sound->gain) << '\n';
            cout << indent2 << "random_period_low  == " << (d_sound->random_period_bounds.from) << '\n';
            cout << indent2 << "random_period_high == " << (d_sound->random_period_bounds.to) << '\n';
            cout << indent1 << "}\n";
        }
    }
    cout << "}\n";
}

static void byteswap_lsnd_detail_sound(LsndDetailSound *detail_sound) {
    byteswap_dependency(detail_sound->sound);
    byteswap_array_32((char *)&(detail_sound->random_period_bounds), 2);
    byteswap_32((char *)&(detail_sound->gain));
    byteswap_32((char *)&(detail_sound->flags));
    byteswap_array_32((char *)&(detail_sound->yaw_bounds), 2);
    byteswap_array_32((char *)&(detail_sound->pitch_bounds), 2);
    byteswap_array_32((char *)&(detail_sound->distance_bounds), 2);
}

static void byteswap_lsnd_track(LsndTrack *track) {
    byteswap_32((char *)&(track->flags));
    byteswap_32((char *)&(track->gain));
    byteswap_32((char *)&(track->fade_in_duration));
    byteswap_32((char *)&(track->fade_out_duration));
    byteswap_dependency(track->start);
    byteswap_dependency(track->loop);
    byteswap_dependency(track->end);
    byteswap_dependency(track->alt_loop);
    byteswap_dependency(track->alt_end);
}

static void byteswap_lsnd_body(LsndBody *lsnd_body) {
    byteswap_32((char *)&(lsnd_body->flags));
    byteswap_32((char *)&(lsnd_body->detail_sound_period_at_zero));
    byteswap_32((char *)&(lsnd_body->unknown0));
    byteswap_32((char *)&(lsnd_body->unknown1));
    byteswap_32((char *)&(lsnd_body->detail_sound_period_at_one));
    byteswap_32((char *)&(lsnd_body->unknown2));
    byteswap_32((char *)&(lsnd_body->unknown3));
    byteswap_32((char *)&(lsnd_body->unknown4));
    byteswap_32((char *)&(lsnd_body->unknown5));

    byteswap_dependency(lsnd_body->continuous_damage_effect);
    byteswap_reflexive(lsnd_body->tracks);
    byteswap_reflexive(lsnd_body->detail_sounds);
}

LsndTag *make_lsnd_tag_for_snd_tag(SndTag *snd_tag) {
    if (snd_tag == NULL)      return NULL;
    if (!snd_tag->is_valid()) return NULL;

    TagHeader *tag_header;
    LsndBody  *tag_data;
    Track     *track;
    char      *snd_path;

    SplitStr *dir_split = splitdir(snd_tag->get_filepath(), snd_tag->get_tags_dir());
    if (dir_split == NULL) return NULL;

    SplitStr *ext_split = splitext(dir_split->right);
    free(dir_split->left);
    free(dir_split->right);
    free(dir_split);
    if (ext_split == NULL) return NULL;

    uint32 path_size = strlen(ext_split->left) + 1;

    char *lsnd_data = (char *)calloc(
        1, sizeof(TagHeader) + sizeof(LsndBody) + sizeof(Track) + path_size);

    if (lsnd_data != NULL) {
        tag_header = (TagHeader *)lsnd_data;
        tag_data   = (LsndBody *)(((char *)tag_header) + sizeof(TagHeader));
        track      = (Track    *)(((char *)tag_data)   + sizeof(LsndBody));
        snd_path   = ((char *)track) + sizeof(Track);
        memcpy(snd_path, ext_split->left, path_size);
    }

    free(ext_split->left);
    free(ext_split->right);
    free(ext_split);

    if (lsnd_data == NULL) return NULL;

    tag_header->tag_class = TagClass::lsnd;
    tag_header->header_size = sizeof(TagHeader);
    tag_header->version = 3;
    tag_header->integ0 = 0x00;
    tag_header->integ1 = 0xFF;
    tag_header->engine_id = EngineId::halo_1;

    tag_data->tracks.size = 1;
    set_tag_pointer(&tag_data->tracks, (uint64)track);

    track->loop.tag_class    = TagClass::snd;
    track->loop.path_length  = path_size - 1;
    set_tag_pointer(&track->loop, (uint64)snd_path);

    LsndTag *lsnd_tag = new LsndTag();
    if (lsnd_tag == NULL) {
        free(lsnd_data);
        return NULL;
    }

    lsnd_tag->set_filepath(snd_tag->get_filepath());
    lsnd_tag->set_tags_dir(snd_tag->get_tags_dir());
    lsnd_tag->tag_header = tag_header;
    lsnd_tag->tag_data = (char *)tag_data;
    lsnd_tag->tag_data_size = sizeof(TagHeader) + sizeof(LsndBody) + sizeof(Track) + path_size;
    lsnd_tag->track_sound_count = 1;

    return lsnd_tag;
}
