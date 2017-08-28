// config_test.cpp : Defines the entry point for the console application.
//

#include "config.h"
#include "util.h"
#include <iostream>
#include <windows.h>

using std::cout;

int main()
{
    cout << "Creating config...\n\n";

    ComposerConfig *cfg = new ComposerConfig();
    cfg->set_tags_dir("C:\\My Repos\\composer\\test_files\\");
    cfg->set_filepath("C:\\My Repos\\composer\\test_files\\test.cfg");
    cout << "Config size       == " << cfg->serialize() << '\n';

    ComposerConfig *test = new ComposerConfig(cfg->filepath);

    char *working_dir = get_working_dir();
    cout << "Working directory == " << working_dir << "\n\n";

    system("pause");
    return 0;
}