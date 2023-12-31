#ifndef SORT_AND_FILTER_H
#define SORT_AND_FILTER_H

#include "defines.h"
#include "dyn_arrs.h"

#define FILTER_VOID_ERROR -1
#define DATA_ERROR -2

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void *bin_search(void *base, size_t nmemb, size_t size, void *key, int (*compar)(const void *, const void *));
void swap(char *a, char *b, size_t size);

#endif