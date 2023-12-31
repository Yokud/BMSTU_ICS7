#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#define NMAX 10

size_t create(long a[], size_t *n, size_t newsize)
{
    *n = newsize;

    for (size_t i = 0; i < *n; i++)
        a[i] = 0;

    return EXIT_SUCCESS;
}

size_t delete(long a[], size_t *n)
{
    for (size_t i = 0; i < *n; i++)
        a[i] = 0;

    *n = 0;

    return EXIT_SUCCESS;
}

size_t input(long a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (scanf("%ld", &a[i]) != 1)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

size_t output(long a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%ld ", a[i]);

    return EXIT_SUCCESS;
}

double average(long a[], size_t n)
{
    long sum;

    sum = 0;

    for (size_t i = 0; i < n; i++)
        sum += a[i];
    
    return (double)sum / n;
}

size_t new_array(long a[], size_t n_a, long b[], size_t *n_b)
{
    size_t j, count;
    double avr;

    avr = average(a, n_a);
    count = 0;
    j = 0;

    for (size_t i = 0; i < n_a; i++)
        if (a[i] > avr)
            count++;

    if (count)
    {
        *n_b = 0;
        create(b, n_b, count);

        for (size_t i = 0; i < n_a; i++)
            if (a[i] > avr)
            {
                b[j] = a[i];
                j++;
            }

        return EXIT_SUCCESS;
    }
    else
        return EXIT_FAILURE;
}

int main(void)
{
    size_t n_a, n_b;
    long a[NMAX];
    long b[NMAX];

    if (scanf("%zu", &n_a) != 1 || n_a > NMAX)
        return EXIT_FAILURE;

    if (input(a, n_a) == EXIT_FAILURE)
        return EXIT_FAILURE;
    else
    {
        if (new_array(a, n_a, b, &n_b) == EXIT_SUCCESS)
        {
            output(b, n_b);
            delete(b, &n_b);

            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
}