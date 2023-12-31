#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#define NMAX 10000

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

size_t bubble_sort(long a[], size_t n)
{
    long r;

    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
            {
                r = a[j + 1];
                a[j + 1] = a[j];
                a[j] = r;
            }

    return EXIT_SUCCESS;
}

int main(void)
{
    size_t n;
    long a[NMAX];

    if (scanf("%zu", &n) != 1 || n > NMAX || n == 0)
        return EXIT_FAILURE;

    if (input(a, n) == EXIT_FAILURE)
        return EXIT_FAILURE;
    else
    {
        bubble_sort(a, n);
        output(a, n);
        return EXIT_SUCCESS;
    }
}