#ifndef STRUCTURES_H
#define STRUCTURES_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#define OK 0
#define INPUT_ERROR -1
#define DIM_ERROR -2 // размеры матриц не совпадают
#define ALLOC_ERROR -3

#define MAX_ROWS 30
#define MAX_COLS 30

#define FILE_NAME_MAX 31

#define ITERATIONS 100

typedef struct 
{
    int m;
    int n;
    int nz_elems; // кол-во ненулевых элементов (длина values и ja)

    double *values; // значения матрицы
    int *ja; // номера столбцов
    int *ia; // номера элементов values, с которых начинается описание очередной строки. Длина равна n + 1
} matrix_t;

int input_matrix(matrix_t *matrix);
void output_matrix(const matrix_t *matrix);
void generate_matrix(matrix_t *matrix, double persent);
int fread_matrix(matrix_t *matrix);
int add_matrixes(matrix_t *m1, matrix_t *m2, matrix_t *res); // для разреженных матриц
void free_matrix(matrix_t *matrix);


typedef struct 
{
    int m;
    int n;
    double **matrix;
} default_matrix_t;

int create_default_matrix(default_matrix_t *dm);
default_matrix_t *add_matrixes_default(default_matrix_t *m1, default_matrix_t *m2); // Стандартный алгоритм сложения матриц
void free_default_matrix(default_matrix_t *matrix);
void generate_default_matrix(default_matrix_t *matrix, double persent);

void measuring_algorithms_time(void); // сравнение алгоритмов сложения

#endif