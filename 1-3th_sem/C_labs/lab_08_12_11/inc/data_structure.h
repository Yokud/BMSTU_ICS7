#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INPUT_ERROR -1
#define ALLOC_ERROR -2
#define DIM_ERROR -3

typedef struct 
{
    long n;
    long m;
    double **matrix;
} matrix_t;

int create_matrix(matrix_t *matrix_ptr, long n, long m);
int fscanf_matrix(FILE *f, matrix_t *matrix_ptr);
void fprint_matrix(FILE *f, const matrix_t *matrix_ptr);
void free_matrix(matrix_t *matrix_ptr);

int matrix_add(matrix_t *a, matrix_t *b, matrix_t *res);
int matrix_mult(matrix_t *a, matrix_t *b, matrix_t *res);
int matrix_det(matrix_t *matrix_ptr, double *det);
int matrix_cmp(matrix_t *a, matrix_t *b);

#endif