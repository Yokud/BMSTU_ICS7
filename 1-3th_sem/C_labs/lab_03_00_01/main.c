#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define MATRIX_SIZE_ERROR 2
#define OK 0

#define N 10
#define M 10

#define YES 1
#define NO 0

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

void mtr_print(int a[N][M], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    printf("\n");
}

size_t is_in_descending_order(long b[N][M], size_t n, size_t j)
{
    if (n < 2)
        return NO;

    for (size_t i = 0; i < n - 1; i++)
    {
        if (b[i][j] <= b[i + 1][j])
            return NO;
    }

    return YES;
}

void mtr_form_array(long a[N][M], size_t n, size_t m, long *b)
{
    for (size_t j = 0; j < m; j++)
        if (is_in_descending_order(a, n, j))
            b[j] = 1;
        else
            b[j] = 0;
}

void arr_print(const long *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%ld ", a[i]);
}

int main(void)
{
    long a[N][M];
    size_t n, m;
    long b[M];
    size_t er;

    if ((er = mtr_input(a, &n, &m)) == OK)
    {
        mtr_form_array(a, n, m, b);
        arr_print(b, m);
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