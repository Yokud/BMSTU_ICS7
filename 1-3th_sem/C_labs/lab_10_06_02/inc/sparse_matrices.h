#ifndef SPARSE_MATRICES_H
#define SPARSE_MATRICES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define INPUT_ERROR 1
#define ALLOC_ERROR -5

typedef struct sparse_matrix_list
{
    long row;
    long col;
    long elem;

    struct sparse_matrix_list *next;
} sparse_matrix_t;

typedef enum commands
{
    UNKNOWN_COMMAND,
    OUT,
    ADD,
    MUL,
    LIN
} command_t;

command_t get_command(char *s);
int create_matrix(sparse_matrix_t **matr_a);
void print_matrix(sparse_matrix_t *matr_a);
void free_matrix(sparse_matrix_t *matr_a);

sparse_matrix_t *add_matrices(sparse_matrix_t *matr_a, sparse_matrix_t *matr_b);
sparse_matrix_t *mult_matrices(sparse_matrix_t *matr_a, sparse_matrix_t *matr_b);
int del_row_by_max_elem(sparse_matrix_t **matr_a);

#endif