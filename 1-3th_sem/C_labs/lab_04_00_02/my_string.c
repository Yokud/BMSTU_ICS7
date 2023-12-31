#include "my_string.h"

size_t read_line(string_t s, size_t n, size_t *str_len)
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
        
    *str_len = i;
    return OK;
}

size_t lexems_of(string_t s, size_t len, words_t lexems, size_t *n, const char *delim)
{
    word_t lexem;
    size_t j = 0;
    *n = 0;
    lexem[0] = '\0';

    for (size_t i = 0; i <= len; i++)
    {
        while (is_delim(s[i], delim) == YES && lexem[0] == '\0')
            i++;

        if (is_delim(s[i], delim) == NO && s[i] != '\0')
        {
            lexem[j + 1] = '\0';
            lexem[j++] = s[i];
        }
        else
        {
            lexem[j] = '\0';
            if (word_len(lexem) > WORD_LEN_MAX)
                return WORD_LEN_ERROR;
            
            add_lexem(lexems, n, lexem);

            j = 0;
            lexem[0] = '\0';
        }
    }

    if (*n == 0)
        return STRING_NO_WORDS_ERROR;

    return OK;
}

void add_lexem(words_t lexems, size_t *n, word_t lexem)
{
    size_t lexem_len = word_len(lexem);
    if (is_in_lexems(lexems, *n, lexem) == NO && lexem_len)
    {
        for (size_t k = 0; k <= lexem_len; k++)
            lexems[*n][k] = lexem[k]; 
        (*n)++;
    }
}

size_t is_delim(const char c, const char *delim)
{
    for (char *del = (char*)delim; *del != '\0'; del++)
        if (c == *del)
            return YES;
    return NO;
}

size_t is_in_lexems(words_t lexems, size_t n, word_t lexem)
{
    for (size_t i = 0; i < n; i++)
        if (word_cmp(lexems[i], lexem))
            return YES;
    return NO;
}

size_t word_cmp(word_t w1, word_t w2)
{
    if (word_len(w1) != word_len(w2))
        return NO;

    for (size_t i = 0; w1[i] != '\0' && w2[i] != '\0'; i++)
        if (w1[i] != w2[i])
            return NO;
    return YES;
}

size_t word_count(string_t s, size_t len, word_t w, const char *delim)
{
    size_t count = 0;
    word_t lexem;
    size_t j = 0;
    lexem[0] = '\0';

    for (size_t i = 0; i <= len; i++)
    {
        while (is_delim(s[i], delim) && lexem[0] == '\0')
            i++;

        if (is_delim(s[i], delim) == NO && s[i] != '\0')
        {
            lexem[j + 1] = '\0';
            lexem[j++] = s[i];
        }
        else
        {
            lexem[j] = '\0';
            if (word_cmp(w, lexem))
                count++;
            
            j = 0;
            lexem[0] = '\0';
        }
    }

    return count;
}

size_t word_len(word_t w)
{
    size_t i;
    for (i = 0; w[i] != '\0'; i++);

    return i;
}