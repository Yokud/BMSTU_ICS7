#include "my_string.h"

size_t read_line(string_t s, size_t n)
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

    return OK;
}

size_t lexems_of(string_t s, words_t lexems, size_t *n, const char *delim)
{
    word_t lexem = (word_t)strtok(s, delim);
    *n = 0;

    while (lexem != NULL)
    {
        size_t lexem_len = strlen(lexem);
        if (lexem_len > WORD_LEN_MAX || !lexem_len)
            return WORD_LEN_ERROR;

        lexems[*n] = lexem; 
        (*n)++;

        lexem = (word_t)strtok(NULL, delim);
    }

    if (*n == 0)
        return STRING_NO_WORDS_ERROR;

    return OK;
}

void reverse_lexems(words_t lexems, size_t n)
{
    for (size_t i = 0; i < n / 2; i++)
    {
        word_t buf = lexems[i];
        lexems[i] = lexems[n - 1 - i];
        lexems[n - 1 - i] = buf;
    }
}

void result_string(string_t s, words_t lexems, size_t n, size_t not_null_els)
{
    strcpy(s, "");
    size_t j = 0;
    for (size_t i = 0; i < n; i++)
        if (lexems[i] != NULL)
            if (j < not_null_els - 1)
            {
                strncat(s, lexems[i], WORD_LEN_MAX);
                strncat(s, " ", WORD_LEN_MAX);
                j++;
            }
            else
                strncat(s, lexems[i], WORD_LEN_MAX);
        else
            continue;       
}

size_t delete_last_like_words(words_t lexems, size_t n)
{
    word_t last_word = lexems[n - 1];
    size_t null_count = 0;

    for (size_t i = 0; i < n; i++)
        if (!strcmp(lexems[i], last_word))
        {
            lexems[i] = NULL;
            null_count++;
        }
    
    return n - null_count;
}

void delete_other_first_letters(word_t word)
{
    size_t j = 1;
    char fst_ch = word[0];
    char result_word[WORD_LEN_MAX + 1];

    result_word[0] = fst_ch;
    result_word[1] = '\0';

    for (size_t i = 1; word[i] != '\0'; i++)
    {
        if (word[i] != fst_ch)
        {
            result_word[j + 1] = '\0';
            result_word[j++] = word[i];
        }
    }

    strcpy(word, result_word);
}

void words_processing(words_t lexems, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (lexems[i] != NULL)
            delete_other_first_letters(lexems[i]);
}