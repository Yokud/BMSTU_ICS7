#ifndef ALLOC_STRINGS_H
#define ALLOC_STRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define READ_ERROR -1
#define ALLOC_ERROR -5

int getline(char **lineptr, size_t *len, FILE *f);
char *str_dup(char *s);

#endif