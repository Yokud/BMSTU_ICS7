#include "files.h"

size_t f_is_null(FILE *f)
{
    if (f == NULL)
        return FILE_ERROR;

    return OK;
}

void print_file(FILE *f)
{
    char str[16];
    while (fgets(str, sizeof(str), f))
        printf("%s", str);
}

size_t file_size(FILE *f, size_t *size)
{
    long sz;
    if (fseek(f, 0L, SEEK_END))
        return FILE_ERROR;

    sz = ftell(f);
    if (sz < 0)
        return FILE_ERROR;
    
    *size = sz;
    return fseek(f, 0L, SEEK_SET);
}