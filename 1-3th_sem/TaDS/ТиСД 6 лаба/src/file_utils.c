#include "file_utils.h"

char *search_in_file(FILE *f, char *word)
{
    if (!f || !word)
        return NULL;

    char *temp;
    size_t temp_len;

    fseek(f, 0L, SEEK_SET);

    while (!feof(f) && getline(&temp, &temp_len, f) > 0)
    {
        if (!strcmp(temp, word))
            return temp;
    }

    return NULL;
}

int insert_to_file(FILE *f, char *word)
{
    if (!f || !word)
        return INPUT_ERROR;

    fseek(f, 0L, SEEK_END);
    fprintf(f, "%s\n", word);

    return OK;
}

int file_size(FILE *f, size_t *size)
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
