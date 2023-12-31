#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#define NMAX 10

size_t input(long *pstart, long *pend)
{
    for (long *pcurr = pstart; pcurr < pend; pcurr++)
        if (scanf("%ld", pcurr) != 1)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

long sum_of_prods_pos_numbers(long *pstart, long *pend)
{
    long x = *pstart;
    long sum = *pstart;

    long *pcurr = pstart;

    while (pcurr < pend - 1 && *pcurr >= 0)
    {
        pcurr++;
        x *= *pcurr;
        sum += x;
    } 
    
    return sum;
}

int main(void)
{
    size_t n;
    long a[NMAX];
    long *pstart, *pend;

    if (scanf("%zu", &n) != 1 || n > NMAX || n == 0)
        return EXIT_FAILURE;

    pstart = a;
    pend = pstart + n;

    if (input(pstart, pend) == EXIT_FAILURE)
        return EXIT_FAILURE;
    else
    {
        printf("%ld", sum_of_prods_pos_numbers(pstart, pend));
        return EXIT_SUCCESS;
    }
}