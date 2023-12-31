#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc_strings.h"

#define OK 0
#define INPUT_ERROR -1
#define FILE_ERROR -2

char *search_in_file(FILE *f, char *word);
int insert_to_file(FILE *f, char *word);
int file_size(FILE *f, size_t *size);

#endif