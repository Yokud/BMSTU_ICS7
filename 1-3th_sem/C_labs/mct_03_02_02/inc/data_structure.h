#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ALLOC_ERROR 1
#define INPUT_ERROR 2

typedef struct 
{
    long n;
    long m;
    double **matrix;
} matrix_t;

int create_matrix(matrix_t *matrix_ptr, long n, long m);
int scanf_matrix(matrix_t *matrix_ptr);
void print_matrix(const matrix_t *matrix_ptr);
void free_matrix(matrix_t *matrix_ptr);
double sum_of_elems_in_col(matrix_t *matrix_ptr, size_t col);
size_t get_max_sum_in_col(matrix_t *matrix_ptr);
void del_col(matrix_t *matrix_ptr, size_t col);

#endif