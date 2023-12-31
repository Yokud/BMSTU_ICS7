#ifndef FILES_H
#define FILES_H

#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ARGS_INPUT_ERROR -1
#define FILE_ERROR -2
#define INPUT_ERROR -3
#define READ_ERROR -4
#define PUT_ERROR -5

int f_has_only_numbers(FILE *f);
void print_file(FILE *f);
size_t file_size(FILE *f, size_t *size);
size_t str_to_pos_int(char *s);
void create_bin_file(FILE *f, char *number);
int print_bin_file(FILE *f);
int sort_file(FILE *f);
int get_number_by_pos(FILE *f, int *num, size_t pos);
int put_number_by_pos(FILE *f, int num, size_t pos);

#endif