#ifndef MY_STRING_H
#define MY_STRING_H

#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define STRING_LEN_MAX 256
#define WORD_LEN_MAX 16

#define OK 0
#define STRING_LEN_ERROR 1
#define WORD_LEN_ERROR 2
#define STRING_NO_WORDS_ERROR 3
#define STRING_VOID_ERROR 4

#define DELIMS " ,;:-.!?"

#define YES 1
#define NO 0

typedef char string_t[STRING_LEN_MAX + 1];
typedef char word_t[WORD_LEN_MAX + 1];
typedef char words_t[STRING_LEN_MAX][WORD_LEN_MAX + 1];

size_t read_line(string_t s, size_t n, size_t *str_len);
size_t is_delim(const char c, const char *delim);
size_t lexems_of(string_t s, size_t len, words_t lexems, size_t *n, const char *delim);
size_t word_count(string_t s, size_t len, word_t w, const char *delim);
size_t word_cmp(word_t w1, word_t w2);
size_t word_len(word_t w);
size_t is_in_lexems(words_t lexems, size_t n, word_t lexem);
void add_lexem(words_t lexems, size_t *n, word_t lexem);

#endif
