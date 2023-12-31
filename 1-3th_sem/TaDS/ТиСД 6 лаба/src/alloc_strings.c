#include "alloc_strings.h"

char *str_dup(char *s)
{
    char *temp = malloc((strlen(s) + 1) * sizeof(char));

    if (temp)
        strcpy(temp, s);
    
    return temp;
}

int getline(char **lineptr, size_t *len, FILE *f)
{
    int c;
    char *temp;

    *len = 0;
    *lineptr = NULL;

    while ((c = fgetc(f)) != '\n' && c != EOF)
    {
        temp = realloc(*lineptr, (*len + 1) * sizeof(char));

        if (temp)
        {
            *lineptr = temp;
            (*lineptr)[(*len)++] = c;
        }
        else
            return ALLOC_ERROR;
    }

    if (!(*len))
        return READ_ERROR;    
    
    temp = realloc(*lineptr, (*len + 1) * sizeof(char));

    if (temp)
    {
        *lineptr = temp;
        (*lineptr)[*len] = '\0';
    }
    else
        return ALLOC_ERROR;

    return OK;
}