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

//#pragma pack(push, 1)
#pragma once
#include "../util/constants.h"


#define ASCIIZ32(name) char name[32]


typedef struct TagHeader {
    pad padding[36];
    TagClass tag_class;
    uint32 checksum;
    uint32 header_size;
    pad padding1[8];
    uint16 version;
    uint8 integ0;
    uint8 integ1;
    EngineId engine_id;
} TagHeader; DUMB_STATIC_ASSERT(sizeof(TagHeader) == TAG_HEADER_SIZE);

typedef struct RawdataRef {
    sint32 size;
    uint32 flags;
    uint32 raw_pointer;
    pointer32 pointer;
    uint32 id;
} RawdataRef; DUMB_STATIC_ASSERT(sizeof(RawdataRef) == 20);

typedef struct Dependency {
    TagClass tag_class;
    pointer32 path_pointer;
    sint32 path_length;
    uint32 id;
} Dependency; DUMB_STATIC_ASSERT(sizeof(Dependency) == 16);

typedef struct Reflexive {
    sint32 size;
    pointer32 pointer;
    uint32 id;
} Reflexive; DUMB_STATIC_ASSERT(sizeof(Reflexive) == 12);

typedef struct FromToFloat {
    float from;
    float to;
} FromToFloat; DUMB_STATIC_ASSERT(sizeof(FromToFloat) == 8);

typedef struct FromToUInt32 {
    uint32 from;
    uint32 to;
} FromToUInt32; DUMB_STATIC_ASSERT(sizeof(FromToUInt32) == 8);

typedef struct FromToSInt32 {
    sint32 from;
    sint32 to;
} FromToSInt32; DUMB_STATIC_ASSERT(sizeof(FromToSInt32) == 8);

typedef struct FromToUInt16 {
    uint16 from;
    uint16 to;
} FromToUInt16; DUMB_STATIC_ASSERT(sizeof(FromToUInt16) == 4);

typedef struct FromToSInt16 {
    sint16 from;
    sint16 to;
} FromToSInt16; DUMB_STATIC_ASSERT(sizeof(FromToSInt16) == 4);


void set_tag_pointer(RawdataRef *, uint64);
void set_tag_pointer(Dependency *, uint64);
void set_tag_pointer(Reflexive *, uint64);

uint64 get_tag_pointer(RawdataRef *);
uint64 get_tag_pointer(Dependency *);
uint64 get_tag_pointer(Reflexive *);

char *parse_dependency(Dependency *dependency, char *curr_pos);
char *parse_reflexive(Reflexive *reflexive, char *curr_pos, size_t struct_size);
char *parse_rawdata_ref(RawdataRef *rawdata_ref, char *curr_pos);

void byteswap_tag_header(TagHeader &tag_header);
void byteswap_rawdata_ref(RawdataRef &rawdata_ref);
void byteswap_dependency(Dependency &dependency);
void byteswap_reflexive(Reflexive &reflexive);

void byteswap_16(char *val);
void byteswap_32(char *val);
void byteswap_array_16(char *data, unsigned int size);
void byteswap_array_32(char *data, unsigned int size);

char *make_indent_str(int indent);
void print_tag_header(TagHeader &tag_header, int indent);
void print_rawdata_ref(RawdataRef &rawdata_ref, char *name, int indent);
void print_dependency(Dependency &dependency, char *name, int indent);
void print_reflexive(Reflexive &reflexive, char *name, int indent);

//#pragma pack(pop)
