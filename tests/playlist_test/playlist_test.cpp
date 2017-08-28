#include <iostream>
#include "config.h"
#include "playlist.h"
#include "util.h"

using std::cout;
using std::cin;

int main()
{
    Playlist *test = new Playlist();

    test->set_tags_dir("C:\\My Repos\\composer\\test_files\\");
    test->parse("C:\\My Repos\\composer\\test_files\\test.play");
    test->set_filepath("C:\\My Repos\\composer\\test_files\\test_resave.play");
    test->serialize();
    test->select_command_list(0);

    int inp = 0;
    cout << "Enter 1 to write song out to file.\n";
    cin >> inp;
    if (inp != 1) {
        while (test->curr_command_list() != -1) {
            cout << test->get_command_list()->lsnd_path << '\n';
            cout << "list: " << test->curr_command_list() << '\n';
            test->play();
            test->curr_section = LSND_SECTION_TYPE_START;
            test->inc_command();
            while (test->curr_command() != -1) {
                cout << "    cmd: " << test->curr_command() << '\n';
                cout << "    perm: " << test->curr_perm() << '\n';
                cout << "        next cmd: ";
                cin >> inp;
                if (inp == -1)
                    test->inc_command();
                else if (inp >= 0)
                    test->select_command(inp);
                else
                    test->stop();

                if (!cin.good()) {
                    cin.clear();
                    cin.ignore(100000000, '\n');
                    cout << '\n';
                }
            }
            cout << "next list: ";
            cin >> inp;
            if (inp < 0)
                test->inc_command_list();
            else
                test->select_command_list(inp);

            cout << '\n';
        }
    } else {
        test->select_command_list(9);
        test->play();
        double playtime_ms = 0.0;
        double sample_len  = 0.0;
        FILE *out = fopen(strcpycat(test->tags_dir, "test.pcm"), "wb");

        if (out != NULL) {
            SoundSamples *samples = test->get_next_samples();

            while (samples != NULL) {
                fwrite(samples->sample_data, 1, samples->sample_data_size, out);
                sample_len = samples->sample_length() / 1000.0;
                playtime_ms += sample_len;

                test->play_timer(playtime_ms);

                if (test->alt) {
                    cout << "   #" << test->curr_perm() << "   ALT   " << playtime_ms << '\n';
                } else {
                    cout << "   #" << test->curr_perm() << "   " << playtime_ms << '\n';
                }
                delete samples;
                samples = test->get_next_samples();

                if (test->curr_section == LSND_SECTION_TYPE_END)
                    test->fade_out_timer(test->fade_out_timer() + sample_len);
            }
        } else {
            cout << "Could not open output file.\n";
        }
    }

    system("pause");
    return 0;
}
