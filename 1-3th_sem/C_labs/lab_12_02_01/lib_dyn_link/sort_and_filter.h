#ifndef SORT_AND_FILTER_H
#define SORT_AND_FILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

#define OK 0
#define FILTER_VOID_ERROR -1
#define DATA_ERROR -2

ARR_DLL void ARR_DECL mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst);
ARR_DLL void * ARR_DECL bin_search(void *base, size_t nmemb, size_t size, void *key, int (*compar)(const void *, const void *));
ARR_DLL void ARR_DECL swap(int8_t *a, int8_t *b, size_t size);

#endif