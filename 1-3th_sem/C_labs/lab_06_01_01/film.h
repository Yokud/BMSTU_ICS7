#ifndef FILM_H
#define FILM_H

#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TITLE_LEN_MAX 25
#define NAME_LEN_MAX 25
#define FILMS_MAX 15

#define OK 0
#define INPUT_ERROR -1
#define STRLEN_ERROR -2
#define YEAR_ERROR -3
#define KEY_ERROR -4
#define OVERFLOW_ERROR -5

typedef struct
{
    char title[TITLE_LEN_MAX + 1];
    char name[NAME_LEN_MAX + 1];
    long year;
} film_t;

typedef enum enumfieldkeys
{
    TITLE,
    NAME,
    YEAR,
    KEY_ERR = KEY_ERROR
} field_key;

void print_film(const film_t *film);
field_key key_value(const char *field);
int cmp_key_with_field(const char *key, const film_t *film, field_key field);
int cmp_struct_by_field(const film_t *f1, const film_t *f2, field_key field);
long get_year(const char *year_str);

#endif