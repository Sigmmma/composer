// tag_parser_test.cpp : Defines the entry point for the console application.
//

#include "tags\tag_io.h"
#include "tags\sound.h"
#include "tags\sound_looping.h"
#include "config.h"
#include "util.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;

void print_dependencies(LsndTag *lsnd_tag) {
    cout << "\nPrinting dependencies\n";
    for (int i = 0; i < lsnd_tag->track_sound_count; i++) {
        if (lsnd_tag->track_sounds[i].start != NULL)
            lsnd_tag->track_sounds[i].start->print();
        if (lsnd_tag->track_sounds[i].loop != NULL)
            lsnd_tag->track_sounds[i].loop->print();
        if (lsnd_tag->track_sounds[i].end != NULL)
            lsnd_tag->track_sounds[i].end->print();
        if (lsnd_tag->track_sounds[i].alt_loop != NULL)
            lsnd_tag->track_sounds[i].alt_loop->print();
        if (lsnd_tag->track_sounds[i].alt_end != NULL)
            lsnd_tag->track_sounds[i].alt_end->print();
    }
    for (int i = 0; i < lsnd_tag->detail_sound_count; i++) {
        if (lsnd_tag->detail_sounds[i].sound != NULL)
            lsnd_tag->detail_sounds[i].sound->print();
    }
}

int main()
{
    srand((unsigned int) (time(0)));
    cout << "Loading tags...\n";

    ComposerConfig *config = new ComposerConfig("C:\\My Repos\\composer\\test_files\\test.cfg");

    LsndTag *lsnd_tag = (LsndTag *)load_tag_at_path(strcpycat(
        config->data->tags_dir, "haloperc\\haloperc.sound_looping"));
    lsnd_tag->config = config;

    /**/
	lsnd_tag->print();
    lsnd_tag->load_dependencies();
    print_dependencies(lsnd_tag);

    SndTag       *snd_tag = lsnd_tag->track_sounds[0].loop;
    SoundSamples *snd_samples;
    for (int i = 0; i < 100; i++) {
        snd_samples = snd_tag->get_next_samples();
        snd_samples->decode_samples();
        delete snd_samples;
    }

    lsnd_tag->unload_dependencies();
    print_dependencies(lsnd_tag);

    /*
    FILE *out = fopen("C:\\My Repos\\composer\\test_files\\test.pcm", "wb");

    SndTag       *snd_tag;
    SoundSamples *snd_samples;
    sint16 next_index;

    snd_tag = lsnd_tag->track_sounds[0].start;
    do {
        snd_samples = snd_tag->get_next_samples();
        snd_samples->decode_samples();
        next_index = snd_samples->next_perm_index;

        fwrite(snd_samples->sample_data,
            snd_samples->sample_data_size,
            1, out);

        delete snd_samples;
    } while (next_index != -1);

    snd_tag = lsnd_tag->track_sounds[0].loop;
    int loop_count = 0;
    do {
        snd_samples = snd_tag->get_next_samples();
        snd_samples->decode_samples();
        next_index = snd_samples->next_perm_index;

        fwrite(snd_samples->sample_data,
            snd_samples->sample_data_size,
            1, out);

        delete snd_samples;
        if (next_index == -1)
            loop_count++;
    } while (loop_count < 0);

    snd_tag = lsnd_tag->track_sounds[0].alt_loop;
    loop_count = 0;
    do {
        snd_samples = snd_tag->get_next_samples();
        snd_samples->decode_samples();
        next_index = snd_samples->next_perm_index;

        fwrite(snd_samples->sample_data,
            snd_samples->sample_data_size,
            1, out);

        delete snd_samples;
        if (next_index == -1)
            loop_count++;
    } while (loop_count < 40);

    fclose(out);*/
    system("pause");
    return 0;
}