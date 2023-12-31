#include "files.h"

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

int read_line(char *s, size_t n)
{
    int ch;
    size_t i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
        else
            return STRING_LEN_ERROR;
        
    s[i] = '\0';
    if (!i)
        return STRING_VOID_ERROR;

    return 0;
}