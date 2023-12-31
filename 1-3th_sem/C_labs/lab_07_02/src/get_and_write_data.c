#include "get_and_write_data.h"


int get_count(FILE *f, long *count)
{
    int value = 0;
    
    *count = 0;

    if (f == NULL || count == NULL)
        return READ_ERROR;

    while (fscanf(f, "%d", &value) == 1)
        (*count)++;

    if (*count == 0)
        return COUNT_ERROR;
    if (!feof(f))
        return READ_ERROR;

    rewind(f);
    return OK;
}       

int read(FILE *f, int *pb, int *pe)
{
    if (pb == NULL || pe == NULL || f == NULL)
        return READ_ERROR;
    
    for (int *pa = pb; pa < pe; pa++)
        if (fscanf(f, "%d", pa) != 1)
            return READ_ERROR;
    return OK;
}

void write(FILE *f, int *pb, int *pe)
{
    if (f == NULL || pb == NULL || pe == NULL)
        return;

    for (int *pa = pb; pa < pe; pa++)
        fprintf(f, "%d ", *pa);
}