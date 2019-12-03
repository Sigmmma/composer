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

#include <iostream>
#include "xbadpcm.h"


#define clamp_to_bounds(x,h,l) \
    if(x > h) {        \
        x = h;         \
    } else if(x < l) { \
        x = l;         \
    }

DecodedPcmStream::DecodedPcmStream() {
    this->channels   = 0;
    this->stream_len = 0;
    this->stream     = NULL;
    this->block_size = XBOX_PCM_BLOCKSIZE;
}

DecodedPcmStream::~DecodedPcmStream() {
    // the stream will NOT be freed upon deleting this object.
    // this is so the stream can be managed by whatever needs to manage it
    //free(this->stream);
}


typedef struct {
    int8_t  index;
    int16_t step_size;
    int16_t predictor;
} TAdpcmState;


const static int16_t STEP_TABLE[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
    19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
    2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};


const static int8_t INDEX_TABLE[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};


int static decode_sample(int code, TAdpcmState *state) {
    int delta, result;

    delta = state->step_size >> 3;
    if(code & 4) delta += state->step_size;
    if(code & 2) delta += state->step_size >> 1;
    if(code & 1) delta += state->step_size >> 2;
    if(code & 8) delta = -delta;
    result           = state->predictor + delta;
    clamp_to_bounds(result, 32767, -32768);
    state->index    += INDEX_TABLE[code];
    clamp_to_bounds(state->index, 88, 0);
    state->step_size  = STEP_TABLE[state->index];
    state->predictor = result;
    return(result);
}


int decode_xboxadpcm_stream(uint8_t *in, uint8_t *out, int in_block_count, int channels) {
    TAdpcmState f_adpcm_state[MAX_CHANNEL_COUNT];
    int16_t     buffers[MAX_CHANNEL_COUNT][8];
    uint32_t    code_buf;
    int         i, j, c, out_block_count;

    for(out_block_count = 0; in_block_count--; out_block_count++) {
        for(c = 0; c < channels; c++) {
            f_adpcm_state[c].predictor = in[0] | (in[1] << 8);    in += 2;
            f_adpcm_state[c].index     = in[0] | (in[1] << 8);    in += 2;
            clamp_to_bounds(f_adpcm_state[c].index, 88, 0);
            f_adpcm_state[c].step_size  = STEP_TABLE[f_adpcm_state[c].index];
        }
        for(i = 8; i; i--) {
            for(c = 0; c < channels; c++) {
                code_buf = in[0] | (in[1] << 8) | (in[2] << 16) | (in[3] << 24);
                in += 4;
                for (j = 0; j < 8; j++) {
                    buffers[c][j] = decode_sample(code_buf & 15, &f_adpcm_state[c]);
                    code_buf >>= 4;
                }
            }
            for(j = 0; j < 8; j++) {
                for(c = 0; c < channels; c++) {
                    *out++ = (buffers[c][j]     ) & 0xff;
                    *out++ = (buffers[c][j] >> 8) & 0xff;
                }
            }
        }
    }
    return(out_block_count * XBOX_PCM_BLOCKSIZE * channels);
}


DecodedPcmStream *get_decoded_xboxadpcm_stream(char *src, int src_len, int channels) {
    int block_ct = 0;
    int in_block_size  = XBOX_ADPCM_BLOCKSIZE * channels;
    int out_block_size = XBOX_PCM_BLOCKSIZE * channels;

    if (channels <= 0) {
        src_len = 0;
    } else if (src_len > 0) {
        src_len -= (src_len % XBOX_ADPCM_BLOCKSIZE);
        block_ct = src_len / in_block_size;
    }

    DecodedPcmStream *decoded_stream = new DecodedPcmStream();
    decoded_stream->stream = (char *)calloc(block_ct, out_block_size);

    decoded_stream->stream_len = decode_xboxadpcm_stream(
        (uint8_t *)src,
        (uint8_t *)decoded_stream->stream,
        block_ct, 
        channels);

    return decoded_stream;
}