#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define MATRIX_SIZE_ERROR 2
#define NO_PRIME_ERROR 3
#define OK 0

#define YES 1
#define NO 0

#define N 10
#define M 10
#define PRIMES_MAX 100

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

size_t is_prime(long num)
{
    if (num <= 1)
        return NO;

    for (size_t i = 2; i < (size_t)num; i++)
        if (num % i == 0)
            return NO;
    
    return YES;
}

void arr_reverse(long a[PRIMES_MAX], size_t n)
{
    for (size_t i = 0; i < n / 2; i++)
    {
        long buf = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = buf;
    }
}

size_t solve(long a[N][M], size_t n, size_t m)
{
    long primes[PRIMES_MAX];
    size_t n_primes = 0;
    size_t k;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_prime(a[i][j]))
            {
                primes[n_primes] = a[i][j];
                n_primes++;
            }
    
    if (n_primes == 0)
        return NO_PRIME_ERROR;

    arr_reverse(primes, n_primes);

    k = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_prime(a[i][j]))
            {
                a[i][j] = primes[k];
                k++;
            }

    return OK;
}

int main(void)
{
    long a[N][M];
    size_t n, m;
    size_t er;

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

    if (solve(a, n, m) != OK)
    {
        printf("Prime elements does not exist\n");
        return NO_PRIME_ERROR;
    }
    else
        mtr_print(a, n, m);
    
    return EXIT_SUCCESS;
}