/*
  TXboxAdpcmDecoder class
  (c) 2005 Benjamin Haisch
  Revision 2 with stereo support

###
  C conversion 0.1.3
  by Luigi Auriemma
  e-mail: aluigi@autistici.org
  web:    aluigi.org

    Copyright 2005,2006 Luigi Auriemma
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
    http://www.gnu.org/licenses/gpl.txt

###
  Conversion back to C++ 0.1.4
  by Devin Bobadilla
  e-mail: mosesbobadilla@gmail.com


  This software is being distributed under a GPLv3 license.

*/

#include <stdio.h>
#include <stdint.h>

#define XBOX_ADPCM_BLOCKSIZE 36
#define XBOX_PCM_BLOCKSIZE   130
#define MAX_CHANNEL_COUNT    6   // 6 channels is more than we'll ever need
const uint8_t SAMPLES_PER_XBOX_ADPCM_BLOCK = XBOX_PCM_BLOCKSIZE / sizeof(int16_t);


class DecodedPcmStream {
public:
    char *stream;
    int   stream_len;
    int   channels;
    int   sample_rate;  // 22050, 44100, etc
    int   bit_rate;     //
    int   block_size;   // should be PCM_BLOCKSIZE
    DecodedPcmStream();
    ~DecodedPcmStream();
};

int decode_xboxadpcm_stream(
    uint8_t *in,
    uint8_t *out,
    int in_block_count,
    int channels
);

DecodedPcmStream *get_decoded_xboxadpcm_stream(
    char *src,      // input stream
    int   src_len,  // length of the input stream
    int   channels  // number of channels, usually 2
);