#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define MATRIX_SIZE_ERROR 2
#define NO_ODD_ERROR 4
#define OK 0

#define N 10
#define M 10

size_t mtr_input(long a[N][M], size_t *n, size_t *m)
{
    if (scanf("%zu%zu", n, m) != 2)
        return INPUT_ERROR;
    
    if (!(0 < *n && *n <= N) || !(0 < *m && *m <= M) || (*n != *m))
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


long srch_min_odd_num_undr_mn_diag(long a[N][M], size_t n, size_t m)
{
    long last_odd_el = a[0][0];

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < i && j < m; j++)
            if (a[i][j] % 2 != 0)
                last_odd_el = a[i][j];

    if (last_odd_el == a[0][0])
        return NO_ODD_ERROR;

    long min_odd_el = last_odd_el;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < i && j < m; j++)
            if (a[i][j] < min_odd_el && a[i][j] % 2 != 0)
                min_odd_el = a[i][j];
    
    return min_odd_el;
}

int main(void)
{
    long a[N][M];
    size_t n, m;
    size_t er;
    long min_odd_num_undr_mn_diag;

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

    min_odd_num_undr_mn_diag = srch_min_odd_num_undr_mn_diag(a, n, m);

    if (min_odd_num_undr_mn_diag != NO_ODD_ERROR)
        printf("%ld", min_odd_num_undr_mn_diag);
    else
    {
        printf("Such element does not exist\n");
        return NO_ODD_ERROR;
    }
    

    return EXIT_SUCCESS;
}