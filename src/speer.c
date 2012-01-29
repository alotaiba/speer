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
#include "libspeer.h"

int main (int argc, const char * argv[])
{
    int c;
    speer_verbose = 0;
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'v':
                    speer_verbose = 1;
                    break;
                    
                default:
                    printf("speer: illegal option %c\n", c);
                    argc = 0;
                    break;
            }
        }
    }
    
    if (argc != 2) {
        printf("Usage: speer input_speex_files_dir output_speex_files_dir\n");
    } else {
        int status = speer_write_speex_to_file(argv[0], argv[1]);
        if (status && speer_verbose) {
            printf("Done\n");
        }
        if (!status) {
            fprintf(stderr, "Error happened while encoding files\n");
        }
    }
    
    return 0;
}

