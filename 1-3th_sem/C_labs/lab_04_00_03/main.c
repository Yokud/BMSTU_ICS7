#include "my_string.h"

int main(void)
{    
    string_t str, new_str;
    
    words_t lexems;
    size_t lexems_n;

    size_t not_null_els;

    size_t str_err, lexem_err;

    switch (str_err = read_line(str, STRING_LEN_MAX + 1))
    {
        case STRING_LEN_ERROR:
            printf("String is too long\n");
            return STRING_LEN_ERROR;
        case STRING_VOID_ERROR:
            printf("String is void\n");
            return STRING_VOID_ERROR;
        case OK:
            break;
    }


    if ((lexem_err = lexems_of(str, lexems, &lexems_n, DELIMS)) == OK)
    {
        not_null_els = delete_last_like_words(lexems, lexems_n);
        if (!not_null_els)
        {
            printf("String has only one kind of word\n");
            return NULL_ARR_ERROR;
        }

        reverse_lexems(lexems, lexems_n);
        words_processing(lexems, lexems_n);
        result_string(new_str, lexems, lexems_n, not_null_els);
        printf("Result: %s\n", new_str);
    }
    else
        switch (lexem_err)
        {
            case WORD_LEN_ERROR:
                printf("String has too long word\n");
                return WORD_LEN_ERROR;
            case STRING_NO_WORDS_ERROR:
                printf("String has no words\n");
                return STRING_NO_WORDS_ERROR;
        }

    return EXIT_SUCCESS;
}