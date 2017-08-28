// xbox_adpcm_codec_test.cpp : Defines the entry point for the console application.
//

#include "xbadpcm.h"
#include <iostream>

using std::cout;

int main()
{
    FILE *in_file  = fopen("C:\\My Repos\\composer\\test_files\\haloperc\\test.adpcm", "rb");
    FILE *out_file = fopen("C:\\My Repos\\composer\\test_files\\haloperc\\test.pcm", "wb");

    if (!in_file) {
        // couldn't load the file for some reason
        cout << "Could not load audio file\n";
        return 1;
    }

    fseek(in_file, 0, SEEK_END);
    int length = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);

    // copy the audio data into memory
    char *in_data = (char *)malloc(length);
    fread(in_data, length, 1, in_file);
    fclose(in_file);

    DecodedPcmStream *decoded_pcm = get_decoded_xboxadpcm_stream(in_data, length, 2);

    // write the decoded pcm audio to a file
    fwrite(decoded_pcm->stream, decoded_pcm->stream_len, 1, out_file);
    fclose(out_file);

    system("pause");
    return 0;
}

