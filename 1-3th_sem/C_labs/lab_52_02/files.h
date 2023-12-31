#ifndef FILES_H
#define FILES_H

#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGS_INPUT_ERROR 53
#define STRING_LEN_ERROR 1
#define STRING_VOID_ERROR 4
#define FILE_ERROR -2

size_t file_size(FILE *f, size_t *size);
int read_line(char *s, size_t n);

#endif