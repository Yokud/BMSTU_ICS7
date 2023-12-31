#include <stdio.h>
#include <stdlib.h>

#define N 64

#define OK 0
#define R_INPUT_ERROR 2
#define C_INPUT_ERROR 3
#define INPUT_ERROR 4

long last_col_min(long m[N][N], long r, int j)
{
    if (r == 0)
        return 0;

    long min = m[0][j];
    for (int i = 0; i < r; i++)
        if (m[i][j] <= min)
            min = m[i][j];
    
    return min;
}

void swap_cols(long m[N][N], long r, int j1, int j2)
{
    for (int i = 0; i < r; i++)
    {
        long buf = m[i][j2];
        m[i][j2] = m[i][j1];
        m[i][j1] = buf;
    }
}

long mtr_input(long m[N][N], long *r, long *c)
{
    if (scanf("%ld", r) != 1 || *r > N || *r < 0)
        return R_INPUT_ERROR;
    
    if (scanf("%ld", c) != 1 || *c > N || *c < 0)
        return C_INPUT_ERROR;

    for (int i = 0; i < *r; i++)
        for (int j = 0; j < *c; j++)
            if (scanf("%ld", &m[i][j]) != 1)
                return INPUT_ERROR;
    
    return OK;
}

void mtr_output(long m[N][N], long r, long c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            printf("%ld ", m[i][j]);
        printf("\n");
    }
}

int main(void)
{
    long r, c, m[N][N];
    long er;
    
    if ((er = mtr_input(m, &r, &c)) != OK)
        switch (er)
        {
            case R_INPUT_ERROR:
                printf("r input error\n");
                return R_INPUT_ERROR;
            case C_INPUT_ERROR:
                printf("c input error\n");
                return C_INPUT_ERROR;
            case INPUT_ERROR:
                printf("Input error\n");
                return INPUT_ERROR;
        }

    for (int i = 0; i < c - 1; i++)
        for (int j = 0; j < c - i - 1; j++)
            if (last_col_min(m, r, j) < last_col_min(m, r, j + 1))
                swap_cols(m, r, j, j + 1);

    mtr_output(m, r, c);

    return EXIT_SUCCESS;
}