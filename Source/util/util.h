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

#pragma once
#include <windows.h>
#include <sys/stat.h>

#ifdef UNICODE
#define PATHSTR_TYPE LPWSTR
const int PATHSTR_SIZE = sizeof(wchar_t);
const PATHSTR_TYPE PATH_DELIMS = L"\\/";
#else
#define PATHSTR_TYPE LPSTR
const int PATHSTR_SIZE = sizeof(char);
const PATHSTR_TYPE PATH_DELIMS = "\\/";
#endif // !UNICODE

inline int gcd(int x, int y);
double time_now();
char *strcpycat(char *left, char *right);
char *strcpycat(char *left, char *right, bool l_free, bool r_free);
bool file_exists(const char *name);
char *dirname(const char *path);
char *get_working_dir();
char *copy_dir_string(const char *dir_path);