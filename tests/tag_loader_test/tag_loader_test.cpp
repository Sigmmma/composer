// tag_loader_test.cpp : Defines the entry point for the console application.
//

#include "tags\tag_io.h"
#include "tags\sound.h"
#include "tags\sound_looping.h"
#include <iostream>

using std::cout;

int main()
{
    cout << "Loading tags...\n";

    SndTag *snd_tag   = (SndTag  *)load_tag_at_path("C:\\My Repos\\composer\\test_files\\test_ogg.sound");
    LsndTag *lsnd_tag = (LsndTag *)load_tag_at_path("C:\\My Repos\\composer\\test_files\\test.sound_looping");

    print_sound_tag(snd_tag);
    cout << "\n\n";
    print_sound_looping_tag(lsnd_tag);

    system("pause");
    return 0;
}