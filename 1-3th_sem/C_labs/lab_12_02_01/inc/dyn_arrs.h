#ifndef DYNAMIC_ARRS_H
#define DYNAMIC_ARRS_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define COUNT_ERROR -2
#define ALLOC_ERROR -2

int create_arr(int **pb, int **pe, long count);
void free_arr(void **pb, void **pe);

#endif