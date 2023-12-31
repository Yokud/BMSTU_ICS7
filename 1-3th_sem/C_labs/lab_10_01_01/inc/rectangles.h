#ifndef RECTANGLES_H
#define RECTANGLES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 0
#define INPUT_ERROR -1

typedef struct rectangle
{
    double width;
    double height;
} rect_t;

int fread_rect(FILE *f, void *rect);
void print_rect(void *rect);
int rects_equal(void *rect_a, void *rect_b);
double square(void *rect);
double perimeter(void *rect);
double diagonal(void *rect);

#endif