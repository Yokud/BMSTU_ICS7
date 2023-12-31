#include "my_snprintf.h"

//ld d hd c s
int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    if (s == format)
        return NOT_RESTRICT_ERROR;

    if (!format)
        return NULL_ERROR;

    size_t i = 0;
    va_list value;

    va_start(value, format);

    for (size_t j = 0; format[j]; j++)
    {
        if (format[j] != '%')
        {
            if (s && n && i < n)
                s[i] = format[j];
            i++;
        }
        else
        {
            if (format[j + 1] == 'd')
            {
                int num = va_arg(value, int);
                char *value_str = num_to_a(num);
                
                if (!value_str)
                {
                    va_end(value);
                    s[i] = '\0';
                    return ALLOC_ERROR;
                }

                for (size_t k = 0; value_str[k]; k++, i++)
                    if (s && n && i < n)
                        s[i] = value_str[k];
                
                free(value_str);
                j += 1;
            }
            else if (format[j + 1] == 'c')
            {
                char ch = va_arg(value, int);

                if (s && n && i < n - 1)
                    s[i] = ch;
                i++;
                j += 1;
            }
            else if (format[j + 1] == 's')
            {
                char *str = va_arg(value, char *);

                if (!str)
                {
                    va_end(value);
                    s[i] = '\0';
                    return NULL_ERROR;
                }

                for (size_t k = 0; str[k]; k++, i++)
                    if (s && n && i < n)
                        s[i] = str[k];

                j += 1;
            }
            else if (format[j + 1] == 'l')
            {
                if (format[j + 2] == 'd')
                {
                    long num = va_arg(value, long);
                    char *value_str = num_to_a(num);
                    
                    if (!value_str)
                    {
                        va_end(value);
                        s[i] = '\0';
                        return ALLOC_ERROR;
                    }

                    for (size_t k = 0; value_str[k]; k++, i++)
                        if (s && n && i < n)
                            s[i] = value_str[k];
                    
                    free(value_str);
                    j += 2;
                }
                else
                {
                    va_end(value);
                    s[i] = '\0';
                    return ARG_ERROR;
                }
            }
            else if (format[j + 1] == 'h')
            {
                if (format[j + 2] == 'd')
                {
                    short num = va_arg(value, int);
                    char *value_str = num_to_a(num);
                    
                    if (!value_str)
                    {
                        va_end(value);
                        s[i] = '\0';
                        return ALLOC_ERROR;
                    }

                    for (size_t k = 0; value_str[k]; k++, i++)
                        if (s && n && i < n)
                            s[i] = value_str[k];
                    
                    free(value_str);
                    j += 2;
                }
                else
                {
                    va_end(value);
                    s[i] = '\0';
                    return ARG_ERROR;
                }
            }
            else
            {
                va_end(value);
                s[i] = '\0';
                return ARG_ERROR;
            }
        }
    }

    if (s && n)
    {
        if (i < n)
            s[i] = '\0';
        else
            s[n - 1] = '\0';
    }

    va_end(value);

    return i;
}

char *num_to_a(long num)
{
    int i, sign;
    char *s, c;
    unsigned str_len;

    str_len = get_num_len(num) + (num < 0 ? 1 : 0);
    s = malloc(sizeof(char) * (str_len + 1));

    if (!s)
        return NULL;

    i = 0;
    sign = num >= 0 ? 1 : -1;

    do
    {
        s[i++] = sign * (num % 10) + '0';
    } while (num /= 10);

    if (sign == -1)
        s[i++] = '-';

    s[i] = '\0';
 
    for (size_t j = 0, k = str_len - 1; j < k; j++, k--) 
    {
        c = s[j];
        s[j] = s[k];
        s[k] = c;
    }

    return s;
}

unsigned get_num_len(long num)
{
    unsigned len = 1;

    while (num > 9 || num < -9)
    {
        len++;
        num /= 10;
    }
    
    return len;
}