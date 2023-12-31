#include <stdio.h>
#include <stdlib.h>

#define N 64

#define OK 0
#define N_INPUT_ERROR 2
#define P_INPUT_ERROR 3
#define INPUT_ERROR 4

long last_min(long a[N], long n)
{
    if (n == 0)
        return 0;

    long min = a[0];
    for (int i = 0; i <= n; i++)
        if (a[i] <= min)
            min = a[i];
    
    return min;
}

void shift(long a[N], long *n, int i)
{
    for (int j = i; j < *n - 1; j++)
        a[j] = a[j + 1];
    (*n)--;
}

long arr_input(long a[N], long n)
{
    for (int i = 0; i < n; i++)
        if (scanf("%ld", &a[i]) != 1)
            return INPUT_ERROR;
    
    return OK;
}

void arr_output(long a[N], long n)
{
    for (int i = 0; i < n; i++)
        printf("%ld ", a[i]);
}

int main(void)
{
    long n, p, a[N];
    long x;

    if (scanf("%ld", &n) != 1 || n > N || n < 0)
    {
        printf("n input error\n");
        return N_INPUT_ERROR;
    }

    if (scanf("%ld", &p) != 1 || p >= n || p < 0)
    {
        printf("p input error\n");
        return P_INPUT_ERROR;
    }

    if (arr_input(a, n) != OK)
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    x = 3 * last_min(a, p);

    for (int i = 0; i < n; i++)
        if (a[i] > x)
        {
            shift(a, &n, i);
            i--;
        }

    arr_output(a, n);

    return EXIT_SUCCESS;
}