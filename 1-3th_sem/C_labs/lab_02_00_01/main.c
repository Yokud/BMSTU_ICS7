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

long sum_of_even_numbers(long a[], size_t n)
{
    long sum;
    size_t count;

    count = 0;
    sum = 0;

    for (size_t i = 0; i < n; i++)
        if (a[i] % 2 == 0)
        {
            sum += a[i];
            count += 1;
        }
    
    if (count)
        return sum;
    else
        return -1;
}

int main(void)
{
    size_t n;
    long a[NMAX];


    if (scanf("%zu", &n) != 1 || n > NMAX)
        return EXIT_FAILURE;

    if (input(a, n) == EXIT_FAILURE)
        return EXIT_FAILURE;
    else
    {
        long sum = sum_of_even_numbers(a, n);
        if (sum != -1)
        {
            printf("%ld", sum);
            return EXIT_SUCCESS;
        }
        else
        {
            printf("Lack of even elements in array");
            return EXIT_FAILURE;
        }
    }
}