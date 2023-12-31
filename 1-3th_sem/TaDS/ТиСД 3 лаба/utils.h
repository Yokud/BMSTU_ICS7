#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

int max_j(int *j, int begin, int end);
int is_zero(double d);
void swap(char *a, char *b, size_t size);
uint64_t tick(void);
void input_string(char *msg, char *str, int max_len);

#endif