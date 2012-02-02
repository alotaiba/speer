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

int speer_file_select(const struct dirent *entry)
{
    
    if ((strcmp(entry->d_name, ".") == 0) || 
        (strcmp(entry->d_name, "..") == 0) || 
        (strncmp(entry->d_name, ".", 1) == 0) ||
        ((S_ISDIR(entry->d_type)) && (S_ISREG(entry->d_type))) )
        return 0;
    else
        return 1;
}

int speer_file_sort(const struct dirent **a, const struct dirent **b)
{
    int number1 = speer_file_parse_int_part((*a)->d_name);
    int number2 = speer_file_parse_int_part((*b)->d_name);
    
    if (number1 >= 0 && number1 >= 0) {
        return (number1 - number2);
    } else {
        return 0;
    }
}

int speer_file_parse_int_part(const char *file_name)
{
    int retvalue = 0;
    regex_t reg;
    regmatch_t matches[1];
    //Look for any file that has numbers appeneded, i.e. input-3.spx
    char *pattern = "[0-9]+";
    regcomp(&reg, pattern, REG_EXTENDED);
    
    if (regexec(&reg, file_name, 1, matches,0) == 0) {
        int len = (int)(matches[0].rm_eo - matches[0].rm_so);
        char *output = malloc(sizeof(char)*(len+1));
        strncpy(output, (file_name + matches[0].rm_so), len);
        //Terminate the last character
        output[len+1] = '\0';
        retvalue = atoi(output);
    }
    
    regfree(&reg);
    
    return retvalue;
}

int speer_speex_convert_to_raw_bytes(short ***bytes, const char *file_name, int *frames, int *frame_size)
{
    FILE *input_file;
    unsigned long input_file_len;
    char *buffer;
    
    SpeexBits bits;
    void *dec_state;
    speex_bits_init(&bits);
    dec_state = speex_decoder_init(&speex_wb_mode);
    
    int fsize = 0;
    speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &fsize);
    *frame_size = fsize; //Copy frame size to parameter
    
    input_file = fopen(file_name, "r");
    
    if (input_file == NULL) {
        fprintf(stderr, "Can't open input file!\n");
        return 0;
    }
    
    fseek(input_file, 0, SEEK_END);
    input_file_len = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    
    //Allocate memory
    buffer = (char *)malloc(input_file_len + 1);
    if (!buffer)
    {
        fclose(input_file);
        fprintf(stderr, "Memory error!\n");
        return 0;
    }
    //Read whole file contents into buffer
    size_t read_state = fread(buffer, 1, input_file_len, input_file);
    if (read_state <= 0) {
        fprintf(stderr, "Error reading from input file!\n");
        return 0;
    }
    
    speex_bits_read_from(&bits, buffer, (int)input_file_len);
    int i = 0;
    *frames = 0;
    *bytes = malloc(sizeof(int) * fsize * 100);
    while (speex_bits_remaining(&bits) > 0)
    {
        short *output = malloc(sizeof(int) * fsize);
        int ret = speex_decode_int(dec_state, &bits, output);
        if (ret == -1)
        {
            free(output);
            break;
        }
        (*bytes)[i] = malloc(sizeof(int) * fsize);
        memcpy((*bytes)[i], output, sizeof(short)*fsize);
        
        ++i;
        *frames = i;
        free(output);
    }
    
    free(buffer);
    fclose(input_file);
    
    return 1;
}

int speer_write_speex_to_file(const char *input_dir, const char *output_dir)
{
    struct dirent **files;
    int count;
    
    count = scandir(input_dir, &files, speer_file_select, speer_file_sort);
    if (count <= 0) {
        fprintf(stderr, "No files found");
        return 0;
    }
    
    FILE *output_file;
    
    char output_file_name[] = "output.raw";
    char output_file_path[1024];
    sprintf(output_file_path, "%s/%s", output_dir, output_file_name);
    output_file = fopen(output_file_path, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Can't open output file!\n");
        return 0;
    }
    
    int status = 0;
    for (int i = 0; i < count; ++i) {
        printf("Converted: %s\n", files[i]->d_name);
        char input_file_path[1024];
        sprintf(input_file_path, "%s/%s", input_dir, files[i]->d_name);
        short **speex_bytes;
        int frames;
        int frame_size;
        status = speer_speex_convert_to_raw_bytes(&speex_bytes, input_file_path, &frames, &frame_size);
        if (!status) {
            fprintf(stderr, "Error happened decoding: %s\n", files[i]->d_name);
            continue;
        }
        for(int i = 0;i < frames; ++i) {
            fwrite((short*)speex_bytes[i], sizeof(short)*frame_size, 1, output_file);
            free(speex_bytes[i]);
        }
        free(speex_bytes);
        if (speer_verbose) {
            printf("Converted: %s\n", files[i]->d_name);
        }
    }
    if (speer_verbose) {
        printf("Output file saved: %s\n", output_file_path);
    }
    fclose(output_file);
    return 1;
}