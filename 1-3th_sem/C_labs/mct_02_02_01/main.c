#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>


// Функция получает на вход строку и считает в ней количество строчных букв.
// Возвращает количество строчных букв в строке.
size_t count_of_lowercase_letters(const char *s)
{
    size_t i, count;

    i = 0;
    count = 0;

    while (s[i] != '\0')
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            count++;
        i++;
    }

    return count;
}


int main(void)
{
    if (count_of_lowercase_letters(" ") != 0)
    {
        puts("ERROR"); 
        return EXIT_FAILURE;
    }
    if (count_of_lowercase_letters("a") != 1)
    {
        puts("ERROR"); 
        return EXIT_FAILURE;
    }
    if (count_of_lowercase_letters("123AAaaAA") != 2)
    {
        puts("ERROR"); 
        return EXIT_FAILURE;
    }
    if (count_of_lowercase_letters("") != 0)
    {
        puts("ERROR"); 
        return EXIT_FAILURE;
    }
    if (count_of_lowercase_letters("123AA") != 0)
    {
        puts("ERROR"); 
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}