#ifndef SORT_H
#define SORT_H

#define ITERATIONS 100
#define FILE_NAME_LEN 30

#include "structures.h"
#include <time.h>

unsigned long long tick(void);
void measure_sorting_time(void);
void swap_theatres(struct Theatre *a, struct Theatre *b);
void mysort_thtr(struct Theatre *base, int nitems);
void swap_keys(struct Key *a, struct Key *b);
void mysort_keys(struct Key *base, size_t nitems);

#endif
