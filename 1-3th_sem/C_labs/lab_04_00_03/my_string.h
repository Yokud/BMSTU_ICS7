#ifndef MY_STRING_H
#define MY_STRING_H

#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN_MAX 256
#define WORD_LEN_MAX 16

#define OK 0
#define STRING_LEN_ERROR 1
#define WORD_LEN_ERROR 2
#define STRING_NO_WORDS_ERROR 3
#define STRING_VOID_ERROR 4
#define NULL_ARR_ERROR 5

#define DELIMS " ,;:-.!?"

#define YES 1
#define NO 0

typedef char string_t[STRING_LEN_MAX + 1];
typedef char *word_t;
typedef char *words_t[STRING_LEN_MAX];

size_t read_line(string_t s, size_t n);
size_t lexems_of(string_t s, words_t lexems, size_t *n, const char *delim);
size_t delete_last_like_words(words_t lexems, size_t n);
void reverse_lexems(words_t lexems, size_t n);
void result_string(string_t s, words_t lexems, size_t n, size_t not_null_els);
void words_processing(words_t lexems, size_t n);
void delete_other_first_letters(word_t word);

#endif
