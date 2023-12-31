#ifndef FILES_H
#define FILES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define READ_ERROR -1
#define COUNT_ERROR -2
#define FILE_ERROR -3

int get_count(FILE *f, long *count);
int read(FILE *f, int *pb, int *pe);
void write(FILE *f, int *pb, int *pe);

#endif