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

typedef char string_t[STRING_LEN_MAX + 1];
typedef char word_t[WORD_LEN_MAX + 1];

char *my_strpbrk(const char *s, const char *accept);
size_t my_strspn(const char *s, const char *accept);
size_t my_strcspn(const char *s, const char *reject);
char *my_strchr(const char *s, int c);
char *my_strrchr(const char *s, int c);

#endif
