#include "dyn_arrs.h"

void free_arr(void **pb, void **pe)
{
    free(*pb);
    *pb = NULL;
    *pe = NULL;
}

int create_arr(int **pb, int **pe, long count)
{
    int *p_temp = NULL;

    if (*pb != NULL || *pe != NULL || pb == NULL || pe == NULL)
        return ALLOC_ERROR;

    if (count <= 0)
        return COUNT_ERROR;

    p_temp = malloc(count * sizeof(int));

    if (p_temp == NULL)
        return ALLOC_ERROR;
    else
    {
        *pb = p_temp;
        *pe = *pb + count;
    }

    return OK;
}