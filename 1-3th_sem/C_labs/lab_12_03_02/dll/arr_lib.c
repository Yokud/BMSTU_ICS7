#include "arr_lib.h"


DLL void DECL fill_arr_with_prime_nums(long *arr, long n)
{
    if (!arr || n <= 0)
        return;

    long value = 1;

    for (long i = 0; i < n; i++)
    {
        int prime = 1;
        do
        {
            ++value;
            for (long j = 0; j < i && arr[j] <= value / 2 && (prime = value % arr[j] != 0); ++j)
                ;
        } while (!prime);

        arr[i] = value;
    }
}

DLL int DECL take_elems_after_even(long *arr_src, long len_src, long *arr_dst, long *len_dst)
{
    long n = 0;

    for (long i = 0; i < len_src; i++)
        if (arr_src[i] % 2 == 0 && i + 1 < len_src)
            n++;

    if (n > *len_dst)
    {
        *len_dst = n;
        return OVERFLOW;
    }

    n = 0;
    for (long i = 0; i < len_src; i++)
        if (arr_src[i] % 2 == 0 && i + 1 < len_src)
            arr_dst[n++] = arr_src[i + 1];

    *len_dst = n;

    return OK;
}