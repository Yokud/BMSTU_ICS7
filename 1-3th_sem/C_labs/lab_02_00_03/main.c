#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#define NMAX 10

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

size_t is_palindrome(long x)
{
    if (x < 0)
        return EXIT_FAILURE;

    long xo, xn;
    xn = 0;
    xo = x;
    
    while (xo)
    {
        xn *= 10;
        xn += xo % 10;
        xo /= 10;
    }

    if (x == xn)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

size_t shift_minus_ones_to_right(long a[], size_t n)
{
    long r;

    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (a[j] == -1 && a[j + 1] != -1)
            {
                r = a[j + 1];
                a[j + 1] = a[j];
                a[j] = r;
            }

    return EXIT_SUCCESS;
}

size_t delete_palindromes(long a[], size_t *n)
{
    size_t count;
    count = 0;

    for (size_t i = 0; i < *n; i++)
    {
        if (!is_palindrome(a[i]))
        {
            a[i] = -1;
            count++;
        }
    }

    if (count > 0 && count < *n)
    {
        shift_minus_ones_to_right(a, *n);
        *n -= count;
        return EXIT_SUCCESS;
    }
    else if (!count)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
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
        if (delete_palindromes(a, &n) == EXIT_FAILURE)
            return EXIT_FAILURE;
        else
        {
            output(a, n);
            return EXIT_SUCCESS;
        }
    }
}