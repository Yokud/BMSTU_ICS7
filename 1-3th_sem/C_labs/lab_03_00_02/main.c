#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define MATRIX_SIZE_ERROR 2
#define TARGET_ERROR 3
#define OK 0

#define N 10
#define M 10
#define NMAX 20

#define FILL_BY 100

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

size_t target_input(long *target)
{
    if (scanf("%ld", target) != 1 || *target < 0 || *target > 9)
        return TARGET_ERROR;
    return OK;
}

long first_digit_of(long b)
{
    while (b >= 10)
        b /= 10;
    return b;
}

void shift_rows_and_ins_fill_by_row(long a[N][M], size_t *n, size_t m, size_t src_row)
{
    for (size_t dst_row = *n; dst_row > src_row; dst_row--)
        for (size_t j = 0; j < m; j++)
            a[dst_row][j] = a[dst_row - 1][j];

    for (size_t j = 0; j < m; j++)
        a[src_row][j] = FILL_BY;
    
    if (*n < NMAX)
        *n += 1;
}

void solve(long a[N][M], size_t *n, size_t m, long target)
{
    for (size_t i = 0; i < *n; i++)
    {
        size_t start = 0, end = 0;
        for (size_t j = 0; j < m; j++)
        {
            long el = labs(a[i][j]);
            start += first_digit_of(el) == target;
            end += (el % 10) == target;
        }

        if (start == end && start)
        {
            shift_rows_and_ins_fill_by_row(a, n, m, i + 1);
            i++;
        }
    }
}

int main(void)
{
    long a[NMAX][M];
    size_t n, m;
    size_t er;
    long target;

    if ((er = mtr_input(a, &n, &m)) != OK)
    {
        switch (er)
        {
            case INPUT_ERROR:
                printf("Input error\n");
                return INPUT_ERROR;
            case MATRIX_SIZE_ERROR:
                printf("Matrix size error\n");
                return MATRIX_SIZE_ERROR;  
        }
    }
    
    if (target_input(&target) != OK)
    {
        printf("Target error\n");
        return TARGET_ERROR;
    }

    solve(a, &n, m, target);
    mtr_print(a, n, m);

    return EXIT_SUCCESS;
}