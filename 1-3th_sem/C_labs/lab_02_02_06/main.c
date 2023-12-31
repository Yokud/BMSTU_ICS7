#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NMAX 10000
#define NUMREP 500

size_t process_0(long a[], size_t n);
size_t process_1(long a[], size_t n);
size_t process_2(long a[], size_t n);

size_t input(long a[], size_t n);

long sum_of_prods_pos_digits_0(long *pstart, long *pend);
long sum_of_prods_pos_digits_1(long a[], size_t n);
long sum_of_prods_pos_digits_2(long *a, size_t n);

int main(void)
{
    clock_t t_0_s, t_1_s, t_2_s;
    clock_t t_0_e, t_1_e, t_2_e;

    size_t n;
    long a[NMAX];

    if (scanf("%zu", &n) != 1 || n > NMAX || n == 0)
        return EXIT_FAILURE;

    if (input(a, n) == EXIT_FAILURE)
        return EXIT_FAILURE;

    t_0_s = clock();
    for (size_t i = 0; i < NUMREP; i++)
        process_0(a, n);
    t_0_e = clock();

    t_1_s = clock();
    for (size_t i = 0; i < NUMREP; i++)
        process_1(a, n);
    t_1_e = clock();

    t_2_s = clock();
    for (size_t i = 0; i < NUMREP; i++)
        process_2(a, n);
    t_2_e = clock();

    printf("Time of process_0: %.6g\n", (double)(t_0_e - t_0_s) / CLOCKS_PER_SEC);
    printf("Time of process_1: %.6g\n", (double)(t_1_e - t_1_s) / CLOCKS_PER_SEC);
    printf("Time of process_2: %.6g\n", (double)(t_2_e - t_2_s) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}

//=============================================================================

size_t process_0(long a[], size_t n)
{
    long *pstart, *pend;

    pstart = a;
    pend = pstart + n;
    long sum = sum_of_prods_pos_digits_0(pstart, pend);
    printf("%ld\n", sum);

    return EXIT_SUCCESS;
}

size_t process_1(long a[], size_t n)
{
    long sum = sum_of_prods_pos_digits_1(a, n);
    printf("%ld\n", sum);

    return EXIT_SUCCESS;
}

size_t process_2(long a[], size_t n)
{
    long sum = sum_of_prods_pos_digits_2(a, n);
    printf("%ld\n", sum);

    return EXIT_SUCCESS;
}

//=============================================================================



//*****************************************************************************

size_t input(long a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (scanf("%ld", &a[i]) != 1)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

//*****************************************************************************



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

long sum_of_prods_pos_digits_0(long *pstart, long *pend)
{
    long x = 1;
    long sum = 0;

    for (long *pcurr = pstart; pcurr < pend; pcurr++)
    {
        x *= *pcurr;
        sum += x;
        
        if (*pcurr < 0)
            break;
    }

    return sum;
}

long sum_of_prods_pos_digits_1(long a[], size_t n)
{
    long x = 1;
    long sum = 0;

    for (size_t i = 0; i < n; i++)
    {
        x *= a[i];
        sum += x;
        
        if (a[i] < 0)
            break;
    }

    return sum;
}

long sum_of_prods_pos_digits_2(long *a, size_t n)
{
    long x = 1;
    long sum = 0;

    for (size_t i = 0; i < n; i++)
    {
        x *= *(a + i);
        sum += x;
        
        if (*(a + i) < 0)
            break;
    }

    return sum;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
