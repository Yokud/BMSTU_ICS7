#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H


#include <stdarg.h>
#include <stdlib.h>

#define NOT_RESTRICT_ERROR -1
#define NULL_ERROR -2
#define ARG_ERROR -3
#define ALLOC_ERROR -4

char *num_to_a(long num);
unsigned get_num_len(long num);

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...);

#endif