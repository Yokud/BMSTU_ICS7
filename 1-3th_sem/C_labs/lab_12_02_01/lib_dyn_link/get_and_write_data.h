#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl


#define OK 0
#define READ_ERROR -1
#define COUNT_ERROR -2
#define FILE_ERROR -3

ARR_DLL int ARR_DECL get_count(FILE *f, long *count);
ARR_DLL int ARR_DECL read(FILE *f, int *pb, int *pe);
ARR_DLL void ARR_DECL write(FILE *f, int *pb, int *pe);

#endif