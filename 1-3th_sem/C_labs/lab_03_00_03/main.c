#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define MATRIX_SIZE_ERROR 2
#define OK 0

#define N 10
#define M 10

size_t mtr_input(long a[N][M], size_t *n, size_t *m)
{
    if (scanf("%zu%zu", n, m) != 2)
        return INPUT_ERROR;
    
    if (!(0 < *n && *n <= N) || !(0 < *m && *m <= M))
        return MATRIX_SIZE_ERROR;
    
    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
            if (scanf("%ld", &a[i][j]) != 1)
                return INPUT_ERROR;
            
    return OK;
}

void mtr_print(long a[N][M], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%ld ", a[i][j]);
        printf("\n");
    }
}

long sum_of_row(long a[N][M], size_t n, size_t m, size_t row)
{
    long sum = 0;

    for (size_t i = 0; i < m && n; i++)
        sum += a[row][i];
    
    return sum;
}

void swap_rows(long a[N][M], size_t n, size_t m, size_t src_row, size_t dst_row)
{
    for (size_t i = 0; i < m && n; i++)
    {
        long buf = a[dst_row][i];
        a[dst_row][i] = a[src_row][i];
        a[src_row][i] = buf;
    }
}

void sort_rows_by_sum(long a[N][M], size_t n, size_t m)
{
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (sum_of_row(a, n, m, j) > sum_of_row(a, n, m, j + 1))
                swap_rows(a, n, m, j, j + 1);
}

int main(void)
{
    long a[N][M];
    size_t n, m;
    size_t er;

    if ((er = mtr_input(a, &n, &m)) == OK)
    {
        sort_rows_by_sum(a, n, m);
        mtr_print(a, n, m);
    }
    else
        switch (er)
        {
            case INPUT_ERROR:
                printf("Input error\n");
                return INPUT_ERROR;
            case MATRIX_SIZE_ERROR:
                printf("Matrix size error\n");
                return MATRIX_SIZE_ERROR;
        }
    
    return EXIT_SUCCESS;
}