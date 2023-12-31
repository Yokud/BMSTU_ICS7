#ifndef FILES_H
#define FILES_H

#include "defines.h"

#define READ_ERROR -1
#define FILE_ERROR -3

int get_count(FILE *f, long *count);
int read(FILE *f, int *pb, int *pe);
void write(FILE *f, int *pb, int *pe);

#endif