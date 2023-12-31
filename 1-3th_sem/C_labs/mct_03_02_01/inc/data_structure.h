#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ALLOC_ERROR 1
#define INPUT_ERROR 2

typedef long inttype;

int input(inttype **arr, size_t *len);
void output(inttype *arr, size_t len);
size_t set_len(inttype **arr, size_t len, size_t newlen);
int is_prime(inttype num);
void del_elems_with_prime_indexes(inttype **arr, size_t *len);

#endif