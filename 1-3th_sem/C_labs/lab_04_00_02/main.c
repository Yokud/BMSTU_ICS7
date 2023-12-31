#include "my_string.h"

int main(void)
{    
    string_t str;
    size_t str_len;

    words_t lexems;
    size_t lexems_n;

    size_t str_err;
    size_t lexem_err;

    if ((str_err = read_line(str, STRING_LEN_MAX + 1, &str_len)) != OK)
    {
        switch (str_err)
        {
            case STRING_LEN_ERROR:
                printf("String is too long\n");
                return STRING_LEN_ERROR;
            case STRING_VOID_ERROR:
                printf("String is void\n");
                return STRING_VOID_ERROR;
        }
    }

    if ((lexem_err = lexems_of(str, str_len, lexems, &lexems_n, DELIMS)) == OK)
    {
        printf("Result: ");
        for (size_t i = 0; i < lexems_n; i++)
            printf("%s %zu\n", lexems[i], word_count(str, str_len, lexems[i], DELIMS));
    }
    else
    {
        switch (lexem_err)
        {
            case WORD_LEN_ERROR:
                printf("String has too long word\n");
                return WORD_LEN_ERROR;
            case STRING_NO_WORDS_ERROR:
                printf("String has no words\n");
                return STRING_NO_WORDS_ERROR;
        } 
    }
    
    return EXIT_SUCCESS;
}