#ifndef COMPARE_H
#define COMPARE_H

#include "defines.h"
#include <math.h>

int cmp_int(const void *p1, const void *p2);
int cmp_double(const void *p1, const void *p2);
int cmp_chr(const void *p1, const void *p2);
int cmp_arr(const void *a, const void *b, size_t n, size_t size, int (*cmp)(const void *, const void *));
int cmp_str(const void *s1, const void *s2);

#endif