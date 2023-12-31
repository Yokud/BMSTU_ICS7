#ifndef FILES_H
#define FILES_H

#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define FILE_ERROR 1
#define NO_SEQUENCE 2

typedef char file_name[16];

size_t f_is_null(FILE *f);
void print_file(FILE *f);
size_t file_size(FILE *f, size_t *size);

#endif