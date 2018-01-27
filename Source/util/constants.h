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
/*
Defines the basic data types found in tags, a collection of constants
defining the fourcc's for each tag type and blam engine version, and
other constants, such as the max size a tag can be before it wont be loaded.
*/

//#pragma pack(push, 1)
#pragma once
#include <cstdint>
#include <stdio.h>
#include <sys/types.h>
#include "JuceHeader.h"
using juce::uint8;
using juce::uint16;
using juce::uint32;
using juce::uint64;

typedef int8_t   sint8;
typedef int16_t  sint16;
typedef int32_t  sint32;
typedef int64_t  sint64;
//typedef uint8_t  uint8;
//typedef uint16_t uint16;
//typedef uint32_t uint32;
//typedef uint64_t uint64;

typedef uint32_t pointer32;

typedef uint8_t  pad;
typedef uint16_t pad2;
typedef uint32_t pad4;
typedef uint64_t pad8;

#define FOURCC(a, b, c, d) (uint32)(((((( (a) << 8) | (b)) << 8) | (c)) << 8) | (d))
#define DUMB_STATIC_ASSERT(x) typedef char assertion_on_struct_size[(!!(x))*2-1]

const uint32 MAX_TAG_SIZE    = 1024 * 1024 * 64;  // max of 64Mb tag file
const uint32 MAX_CFG_STR_LEN = 1024 * 4;          // max of 1Kb per string
const uint32 TAG_HEADER_SIZE = 64;  // a tag must be at least the size of its header
const long INDENT_SIZE = 4; // number of spaces to indent when printing

/*
Define the fourcc ints for the tag classes.

TODO: There should be 81 more of these for the basic Halo 1 classes, and
even more if you include open sauce. I dont have time to type them.
*/
enum class TagClass : uint32 {
    snd  = FOURCC('s', 'n', 'd', '!'),
    lsnd = FOURCC('l', 's', 'n', 'd'),
    none = 0xFFFFFFFF,
};

/*
Define the fourcc ints for the blam engine versions.
*/

enum class EngineId : uint32 {
    halo_1 = FOURCC('b', 'l', 'a', 'm'),
    halo_2 = FOURCC('!', 'm', 'l', 'b'),
    FORCE_32BIT = 0xFFFFFFFF,
};
//#pragma pack(pop)
