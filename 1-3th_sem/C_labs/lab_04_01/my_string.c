#include "my_string.h"

char *my_strpbrk(const char *s, const char *accept)
{
    for (char *ch_s = (char*)s; *ch_s != '\0'; ch_s++)
        for (char *ch_ac = (char*)accept; *ch_ac != '\0'; ch_ac++)
            if (*ch_s == *ch_ac)
                return ch_s;

    return NULL;
}

size_t my_strspn(const char *s, const char *accept)
{
    size_t len = 0;
    
    for (char *ch_s = (char*)s; *ch_s != '\0'; ch_s++)
    {
        size_t is_include = 0;
        for (char *ch_ac = (char*)accept; *ch_ac != '\0'; ch_ac++)
            if (*ch_s == *ch_ac)
                is_include++;
        if (is_include)
            len++;
        else
            return len;
    }
            
    return len;
}

size_t my_strcspn(const char *s, const char *reject)
{
    size_t len = 0;
    
    for (char *ch_s = (char*)s; *ch_s != '\0'; ch_s++)
    {
        size_t is_include = 0;
        for (char *ch_ac = (char*)reject; *ch_ac != '\0'; ch_ac++)
            if (*ch_s == *ch_ac)
                is_include++;
        if (is_include == 0)
            len++;
        else
            return len;
    }
            
    return len;
}
char *my_strchr(const char *s, int c)
{
    for (; *s != '\0'; s++)
        if (*s == c)
            return (char*)s;
    
    if (*s == c)
        return (char*)s;
    
    return NULL;
}

char *my_strrchr(const char *s, int c)
{
    long str_len = 0;
    for (char *ch = (char*)s; *ch != '\0'; ch++, str_len++);

    for (long i = str_len; i >= 0; i--)
        if (*(s + i) == c)
            return (char*)(s + i);

    return NULL;
}