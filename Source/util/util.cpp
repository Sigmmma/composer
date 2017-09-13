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

#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include "util.h"

#if defined(__linux__) || defined(UNIX)
    #include <time.h>
    #include <unistd.h>
    double time_now() {
        // returns a timestamp in milliseconds
        struct timespec result;
        clock_gettime(CLOCK_REALTIME, &result);
        return (result.tv_sec  * 1000.0 +
                result.tv_nsec / 1000000.0);
    }

    // emulate sleep from windows
    void Sleep(uint32 dwMilliseconds) {
        struct timespec sleep_time;
        sleep_time.tv_sec  =  dwMilliseconds / 1000;
        sleep_time.tv_nsec = (dwMilliseconds % 1000)*1000000;
        nanosleep(&sleep_time, NULL);
    }

#elif defined(_WIN32)
    #include <windows.h>
    double time_now() {
        // returns a timestamp in milliseconds
        FILETIME   ftime;
        SYSTEMTIME stime;
        double result;

        // get the current time and convert it to a filetime
        GetSystemTime(&stime);
        SystemTimeToFileTime(&stime, &ftime);

        result = (((long long)ftime.dwHighDateTime) << 32) / 10000.0;
        return result + (ftime.dwLowDateTime / 10000.0);
}
#else
    crash  // need to write another platform specific time function
#endif

inline int gcd(int x, int y) {
    for (;;) {
        if (x == 0) return y;
        y %= x;
        if (y == 0) return x;
        x %= y;
    }
}

char *strcpycat(char *left, char *right, bool l_free, bool r_free) {
    char *new_str = strcpycat(left, right);
    if (l_free && left != NULL)  free(left);
    if (r_free && right != NULL)  free(right);
    return new_str;
}

char *strcpycat(char *left, char *right) {
    if (left == NULL || right == NULL) {
        // what the hell do you think you're doing?
        return NULL;
    }

    size_t left_len = strlen(left);
    char *new_str = (char *)malloc(left_len + strlen(right) + 1);
    if (new_str == NULL) {
        // couldn't allocate space for new string
        return NULL;
    }

    strcpy(new_str, left);
    strcpy(new_str + left_len, right);
    return new_str;
}

bool file_exists(const char *name) {
    struct stat buffer;
    return (stat(name, &buffer) == 0);

}

#if defined(__linux__) || defined(UNIX)
char *get_working_dir() {
    char * cwd = getcwd(NULL, 0);
    size_t len = strlen(cwd);
    if (cwd[len - 1] != '/') {
        char *new_cwd = (char *)malloc(len + 2);
        memcpy(new_cwd, cwd, len);
        new_cwd[len] = '/';
        new_cwd[len + 1] = '\0';
        free(cwd);
        return new_cwd;
    } else {
        return cwd;
    }
}
#elif defined(_WIN32)
char *get_working_dir() {
    char  str_fit_pad = 1;
    long  alloc_len = 32;  // start off with a 32 character buffer
    PATHSTR_TYPE path = (PATHSTR_TYPE)malloc((alloc_len + str_fit_pad) * PATHSTR_SIZE);

    if (path == NULL) {
        // couldn't allocate buffer
        return NULL;
    }

    long path_len = GetModuleFileName(NULL, (PATHSTR_TYPE)path, alloc_len);

    // loop until the path string fits within the buffer
    while (path_len == alloc_len) {
        if (alloc_len * PATHSTR_SIZE > 1024 * 2) {
            // should NEVER need larger than a 2kb string buffer
            return NULL;
        }

        // the allocated length isn't long enough; free the old
        // path string and allocate a larger one.
        alloc_len *= 2;
        free(path);
        path = (PATHSTR_TYPE)malloc((alloc_len + str_fit_pad) * PATHSTR_SIZE);
        if (path == NULL) {
            // couldn't allocate buffer
            return NULL;
        }

        path_len = GetModuleFileName(NULL, path, alloc_len);
    }

    if (path_len == 0 || path_len >= alloc_len) {
        // couldn't get the path, or doing so would make
        // a larger string than would ever be necessary
        return NULL;
    }

    // truncate the string to remove the executable name.
    // path_len is the number of non-null characters in the
    // path, so path[path_len] should give us the terminator
    while (path[path_len - 1] != PATH_DELIMS[0] &&
           path[path_len - 1] != PATH_DELIMS[1]) {
        path_len--;
        if (path_len <= 0) break;
    }

    // null terminate the string at the point after the last path separator
    path[path_len] = 0;

    #if PATHSTR_SIZE == 1
    // characters are single bytes, so no bytes need be removed
    return (char *)path;
    #else
    // in order to use the string, we'll need to make it not utf16 or utf32
    char *char_path = (char *)calloc(path_len + 1, 1);

    for (int i = 0; i < path_len; i++) {
        // copy the first byte of every character into a new string
        char_path[i] = ((char *)path)[i * PATHSTR_SIZE];
    }
    free(path);

    return char_path;
    #endif
}
#endif

char *dirname(const char *path) {
    if (path == NULL) return NULL;
    size_t path_len = strlen(path);

    while (path[path_len - 1] != PATH_DELIMS[0] &&
           path[path_len - 1] != PATH_DELIMS[1]) {
        path_len--;
        if (path_len == 0) return NULL;
    }
    char *dir = (char *)malloc(path_len + 1);

    if (dir == NULL)   return NULL;
    else if (path_len) strncpy(dir, path, path_len);

    dir[path_len] = '\0';
    return dir;
}

char *copy_dir_string(const char *dir_path) {
    // should probably do some checking to make sure the new_path
    // is a valid filepath before setting it.

    size_t new_alloc_len = strlen(dir_path);
    bool add_sep = new_alloc_len == 0;
    #if defined(_WIN32)
    if (!add_sep) add_sep = dir_path[new_alloc_len - 1] != '\\';
    #else
    if (!add_sep) add_sep = dir_path[new_alloc_len - 1] != '/';
    #endif
    if (add_sep) new_alloc_len += 1;

    char *new_alloc_path = (char *)malloc(new_alloc_len + 1);
    if (new_alloc_path == NULL) return NULL;

    memcpy(new_alloc_path, dir_path, new_alloc_len + 1);
    #if defined(_WIN32)
    if (add_sep) new_alloc_path[new_alloc_len - 1] = '\\';
    #else
    if (add_sep) new_alloc_path[new_alloc_len - 1] = '/';
    #endif
    new_alloc_path[new_alloc_len] = 0;
    return new_alloc_path;
}

char *sanitize_path(char *path, bool in_place=false) {
    if (path == NULL) return NULL;

    size_t path_len = strlen(path);
    if (!in_place) {
        char *new_path = (char *)malloc(path_len + 1);
        memcpy(new_path, path, path_len);
        path = new_path;
    }
    for (size_t i=0; i < path_len; i++) {
        #if defined(_WIN32)
        if (path[i] == '/') path[i] = '\\';
        #else
        if (path[i] == '\\') path[i] = '/';
        #endif
    }
    return path;
}

inline bool caseinscmp(char x, char y) {
    if (x > 0x40 && y > 0x40) {
        if (x < 0x5B) x += 0x20;
        if (y < 0x5B) y += 0x20;
    }
    return x == y;
}

SplitStr *splitdir(char *str, char *dir) {
    if (str == NULL) return NULL;
    SplitStr *str_struct = (SplitStr *)calloc(1, sizeof(SplitStr));
    size_t dir_length = strlen(dir);
    size_t str_length = strlen(str);
    str_struct->left  = (char *)calloc(str_length, 1);
    str_struct->right = (char *)calloc(str_length, 1);
    if (str_struct == NULL || str_struct->left == NULL || str_struct->right == NULL) {
        free(str_struct->left);
        free(str_struct->right);
        free(str_struct);
        return NULL;
    }

    size_t i = 0;
    for (;;) {
        if (i >= dir_length) break;
        if (i >= str_length) break;
        if (!caseinscmp(dir[i], str[i])) break;
        i++;
    }

    if (i > 0)          memcpy(str_struct->left,  str, i);
    if (i < str_length) memcpy(str_struct->right, str + i, str_length - i);
    str_struct->left  = (char *)realloc(str_struct->left, i + 1);
    str_struct->right = (char *)realloc(str_struct->right, str_length - i + 1);

    if (str_struct->left == NULL || str_struct->right == NULL) {
        free(str_struct->left);
        free(str_struct->right);
        free(str_struct);
        return NULL;
    }

    return str_struct;
}

SplitStr *splitext(char *str) {
    if (str == NULL) return NULL;
    SplitStr *str_struct = (SplitStr *)calloc(1, sizeof(SplitStr));
    size_t str_length = strlen(str);
    str_struct->left = (char *)calloc(str_length, 1);
    str_struct->right = (char *)calloc(str_length, 1);
    if (str_struct == NULL || str_struct->left == NULL || str_struct->right == NULL) {
        free(str_struct->left);
        free(str_struct->right);
        free(str_struct);
        return NULL;
    }

    size_t i = str_length;
    for (;;) {
        if (str[i] == '.') break;
        #if defined(_WIN32)
        if (i == 0 || str[i] == '\\') {
        #else
        if (i == 0 || str[i] == '/'){;
        #endif
            i = str_length;
            break;
        }
        i--;
    }

    if (i > 0)          memcpy(str_struct->left, str, i);
    if (i < str_length) memcpy(str_struct->right, str + i, str_length - i);
    str_struct->left  = (char *)realloc(str_struct->left, i + 1);
    str_struct->right = (char *)realloc(str_struct->right, str_length - i + 1);

    if (str_struct->left == NULL || str_struct->right == NULL) {
        free(str_struct->left);
        free(str_struct->right);
        free(str_struct);
        return NULL;
    }

    return str_struct;
}
