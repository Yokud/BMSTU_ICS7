#include "data_structure.h"


int input(inttype **arr, size_t *len)
{
    if (!arr)
        return INPUT_ERROR;

    if (scanf("%zu", len) != 1 || *len == 0)
        return INPUT_ERROR;

    *arr = malloc((*len) * sizeof(inttype));

    if (!arr)
        return ALLOC_ERROR;

    for (size_t i = 0; i < *len; i++)
        if (scanf("%ld", *arr + i) != 1)
        {
            set_len(arr, *len, 0);
            return INPUT_ERROR;
        }

    return OK;
}

void output(inttype *arr, size_t len)
{
    if (!arr)
        return;

    for (size_t i = 0; i < len; i++)
        printf("%ld ", arr[i]);
    printf("\n");
}

size_t set_len(inttype **arr, size_t len, size_t newlen)
{
    if (!arr)
        return 0;

    inttype *temp = realloc(*arr, newlen * sizeof(inttype));

    if (!temp)
        return len;
    else
        *arr = temp;
    
    return newlen;
}

void del_elems_with_prime_indexes(inttype **arr, size_t *len)
{
    size_t count_of_prime_indexes = 0;   

    for (size_t i = *len - 1; i; i--)
        if (is_prime(i))
        {
            for (size_t j = i; j < *len - 1 - count_of_prime_indexes; j++)
                (*arr)[j] = (*arr)[j + 1];

            count_of_prime_indexes++;
        }

    if (set_len(arr, *len, *len - count_of_prime_indexes) == *len)
        return;
    
    (*len) -= count_of_prime_indexes;
}

int is_prime(inttype num)
{
    if (num < 2)
        return 0;

    for (inttype i = 2; i < num; i++)
        if (num % i == 0)
            return 0;

    return 1;
}