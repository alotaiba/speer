/*
 * This file is part of project Speer
 * 
 * This code is licensed to you under the terms of the MIT License, or, at
 * your option, the terms of the GNU General Public License version 3.0.
 * See the LICENSE file for the text of the licenses.
 * 
 * Copyright (c) 2012 Abdulrahman Al-Otaiba
 * Dual-licensed under MIT and/or GPLv3.
 */
#ifndef speer_libspeer_h
#define speer_libspeer_h

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <speex/speex.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int speer_verbose;

//Public API
int speer_speex_convert_to_raw_bytes(short ***bytes, const char *file_name, int *frames, int *frame_size);
int speer_write_speex_to_file(const char *input_dir, const char *output_dir);

//Helper functions used internally
int speer_file_select(const struct dirent *entry);
int speer_file_sort(const struct dirent **a, const struct dirent **b);
int speer_file_parse_int_part(const char *file_name);

#endif
