#include "data_structure.h"


int create_matrix(matrix_t *matrix_ptr, long n, long m)
{
    if (n <= 0 || m <= 0)
        return INPUT_ERROR;

    matrix_ptr->n = n;
    matrix_ptr->m = m;
    matrix_ptr->matrix = calloc(matrix_ptr->m, sizeof(double *));

    if (!matrix_ptr->matrix)
        return ALLOC_ERROR;

    for (long i = 0; i < matrix_ptr->m; i++)
    {
        matrix_ptr->matrix[i] = malloc(matrix_ptr->n * sizeof(double));

        if (!matrix_ptr->matrix[i])
        {
            free_matrix(matrix_ptr);
            return ALLOC_ERROR;
        }
    }

    return OK;
}

int scanf_matrix(matrix_t *matrix_ptr)
{
    if (scanf("%ld %ld", &matrix_ptr->n, &matrix_ptr->m) != 2)
        return INPUT_ERROR;

    if (create_matrix(matrix_ptr, matrix_ptr->n, matrix_ptr->m))
        return ALLOC_ERROR;

    for (long i = 0; i < matrix_ptr->m; i++)
        for (long j = 0; j < matrix_ptr->n; j++)
            if (scanf("%lf", &matrix_ptr->matrix[i][j]) != 1)
            {
                free_matrix(matrix_ptr);
                return INPUT_ERROR;
            }

    return OK;
}

void print_matrix(const matrix_t *matrix_ptr)
{
    printf("%ld %ld\n", matrix_ptr->n, matrix_ptr->m);

    for (long i = 0; i < matrix_ptr->m; i++)
    {
        for (long j = 0; j < matrix_ptr->n; j++)
            printf("%.6lf ", matrix_ptr->matrix[i][j]);
        printf("\n");
    }     
}

void free_matrix(matrix_t *matrix_ptr)
{
    for (long i = 0; i < matrix_ptr->m; i++)
        free(matrix_ptr->matrix[i]);
    free(matrix_ptr->matrix);
}


double sum_of_elems_in_col(matrix_t *matrix_ptr, size_t col)
{
    double sum = 0.0;

    if (col >= matrix_ptr->m)
        return 0.0;

    for (size_t i = 0; i < matrix_ptr->n; i++)
        sum += matrix_ptr->matrix[col][i];

    return sum;
}

void del_col(matrix_t *matrix_ptr, size_t col)
{
    free(matrix_ptr->matrix[col]);

    for (size_t i = col; i < matrix_ptr->m - 1; i++)
        matrix_ptr->matrix[i] = matrix_ptr->matrix[i + 1];

    double **temp = realloc(matrix_ptr->matrix, (matrix_ptr->m - 1) * sizeof(double *));

    if (temp)
        matrix_ptr->matrix = temp;
}

size_t get_max_sum_in_col(matrix_t *matrix_ptr)
{
    size_t col = 0;
    double sum = sum_of_elems_in_col(matrix_ptr, col);
    double newsum;

    for (size_t i = 0; i < matrix->m; i++)
        if ((newsum = sum_of_elems_in_col(matrix_ptr, i)) > sum)
        {
            col = i;
            sum = newsum;
        }

    return col;
}