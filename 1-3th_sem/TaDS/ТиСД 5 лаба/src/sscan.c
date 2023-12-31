#include "sscan.h"

int int_sscan(FILE *f, int *dst)
{
    int c, dgt, x = 0;
    bool negative = false, sign = false;
    size_t size = 0;

    c = fgetc(f);
    while (isspace(c))
        c = fgetc(f);
    
    while (c != EOF && !isspace(c))
    {
        if ((c == '-' || c == '+') && !sign)
        {
            if (c == '-')
                negative = true;
            sign = true;
        }
        else
        {
            if (isdigit(c))
            {
                dgt = c - '0';
                if (((double)(INT_MAX - dgt) + 1.0 * negative) / 10.0 < (double)x)
                    return SSC_OVERFLOW;
                x = 10 * x + dgt; 
                size++;
            }       
            else
                return SSC_NDIGIT;
        }
        c = fgetc(f);
    }

    if (!size)
        return SSC_EMPTY;
    *dst = x * (1 - 2 * negative);
    return EXIT_SUCCESS;
}

int bool_sscan(FILE *f, bool *dst)
{
    int temp;
    int rc = int_sscan(f, &temp);
    if (rc)
        return rc;
    if (temp != 0 && temp != 1)
        return SSC_OVERFLOW;
    *dst = temp;
    return EXIT_SUCCESS;
}