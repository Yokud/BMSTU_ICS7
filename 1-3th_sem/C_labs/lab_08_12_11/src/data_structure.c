#include "data_structure.h"

int create_matrix(matrix_t *matrix_ptr, long n, long m)
{
    if (n <= 0 || m <= 0)
        return INPUT_ERROR;

    matrix_ptr->n = n;
    matrix_ptr->m = m;
    matrix_ptr->matrix = calloc(matrix_ptr->n, sizeof(double *));

    if (!matrix_ptr->matrix)
        return ALLOC_ERROR;

    for (long i = 0; i < matrix_ptr->n; i++)
    {
        matrix_ptr->matrix[i] = malloc(matrix_ptr->m * sizeof(double));

        if (!matrix_ptr->matrix[i])
        {
            free_matrix(matrix_ptr);
            return ALLOC_ERROR;
        }
    }

    return OK;
}

int fscanf_matrix(FILE *f, matrix_t *matrix_ptr)
{
    if (!f)
        return INPUT_ERROR;

    if (fscanf(f, "%ld %ld", &matrix_ptr->n, &matrix_ptr->m) != 2)
        return INPUT_ERROR;

    if (create_matrix(matrix_ptr, matrix_ptr->n, matrix_ptr->m))
        return ALLOC_ERROR;

    for (long i = 0; i < matrix_ptr->n; i++)
        for (long j = 0; j < matrix_ptr->m; j++)
            if (fscanf(f, "%lf", &matrix_ptr->matrix[i][j]) != 1)
            {
                free_matrix(matrix_ptr);
                return INPUT_ERROR;
            }

    return OK;
}

void fprint_matrix(FILE *f, const matrix_t *matrix_ptr)
{
    if (!f)
        return;

    fprintf(f, "%ld %ld\n", matrix_ptr->n, matrix_ptr->m);

    for (long i = 0; i < matrix_ptr->n; i++)
    {
        for (long j = 0; j < matrix_ptr->m; j++)
            fprintf(f, "%.6lf ", matrix_ptr->matrix[i][j]);
        fprintf(f, "\n");
    }     
}

void free_matrix(matrix_t *matrix_ptr)
{
    for (long i = 0; i < matrix_ptr->n; i++)
        free(matrix_ptr->matrix[i]);
    free(matrix_ptr->matrix);
}

int matrix_add(matrix_t *a, matrix_t *b, matrix_t *res)
{
    if (a->n != b->n || a->m != b->m)
        return DIM_ERROR;

    if (create_matrix(res, a->n, a->m))
        return ALLOC_ERROR;

    for (long i = 0; i < a->n; i++)
        for (long j = 0; j < a->m; j++)
            res->matrix[i][j] = a->matrix[i][j] + b->matrix[i][j];

    return OK;
}

int matrix_mult(matrix_t *a, matrix_t *b, matrix_t *res)
{
    if (a->m != b->n)
        return DIM_ERROR;

    if (create_matrix(res, a->n, b->m))
        return ALLOC_ERROR;

    for (long i = 0; i < res->n; i++)
        for (long j = 0; j < res->m; j++)
        {
            double sum = 0.0;
            for (long r = 0; r < a->m; r++)
                sum += a->matrix[i][r] * b->matrix[r][j];
            res->matrix[i][j] = sum;
        }

    return OK;
}

int matrix_det(matrix_t *matrix_ptr, double *det)
{
    if (matrix_ptr->n != matrix_ptr->m)
        return DIM_ERROR;

    if (matrix_ptr->n == 1)
    {
        *det = matrix_ptr->matrix[0][0];
        return OK;
    }
    else if (matrix_ptr->n == 2)
    {
        *det = matrix_ptr->matrix[0][0] * matrix_ptr->matrix[1][1] - matrix_ptr->matrix[0][1] * matrix_ptr->matrix[1][0];
        return OK;
    }

    *det = 0;
    for (long k = 0; k < matrix_ptr->n; k++)
    {
        matrix_t sub_matrix;
        double minor;

        if (create_matrix(&sub_matrix, matrix_ptr->n - 1, matrix_ptr->m - 1))
            return ALLOC_ERROR;

        for (long i = 1; i < matrix_ptr->n; i++)
            for (long j = 0, sub_j = 0; j < matrix_ptr->m && sub_j < matrix_ptr->m - 1; j++)
                if (j != k)
                    sub_matrix.matrix[i - 1][sub_j++] = matrix_ptr->matrix[i][j];
        
        matrix_det(&sub_matrix, &minor);
        *det += (k % 2 == 0 ? 1 : -1) * matrix_ptr->matrix[0][k] * minor;
        free_matrix(&sub_matrix);
    }

    return OK;
}

int matrix_cmp(matrix_t *a, matrix_t *b)
{
    if (a->n != b->n)
        return a->n - b->n;
    else if (a->m != b->m)
        return a->m - b->m;

    for (long i = 0; i < a->n; i++)
        for (long j = 0; j < a->m; j++)
            if (a->matrix[i][j] != b->matrix[i][j])
                return a->matrix[i][j] - b->matrix[i][j];
    
    return 0;
}