#include "files.h"

size_t sign_exchanging_count(FILE *f, size_t *sign_count)
{
    size_t count = 0;
    long num;
    int prev_sign, sign;
    
    if (fscanf(f, "%ld", &num) == 1)
    {
        count++;
        sign = num >= 0 ? 1 : -1;
        prev_sign = sign;
        while (fscanf(f, "%ld", &num) == 1)
        {
            count++;
            sign = num >= 0 ? 1 : -1;
            if (sign != prev_sign)
            {
                prev_sign = sign;
                (*sign_count)++;
            }
        }
    }
    else
        return FILE_ERROR;
    
    if (count == 1)
        return NO_SEQUENCE;

    return OK;
}

int main(void)
{
    FILE *f = stdin;
    size_t err, sign_count = 0;

    if ((err = sign_exchanging_count(f, &sign_count)) != OK)
    {
        switch (err)
        {
            case FILE_ERROR:
                return FILE_ERROR;
            case NO_SEQUENCE:
                return NO_SEQUENCE;
        }
    }
    else
        printf("%zu", sign_count);

    return EXIT_SUCCESS;
}