#ifndef FILM_H
#define FILM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "alloc_strings.h"

#define OK 0
#define INPUT_ERROR -1
#define GETLINE_ERROR -2
#define YEAR_ERROR -3
#define KEY_ERROR -4
#define ALLOC_ERROR -5

typedef struct
{
    char *title;
    char *name;
    long year;
} film_t;

typedef enum enumfieldkeys
{
    TITLE,
    NAME,
    YEAR,
    KEY_ERR = KEY_ERROR
} field_key;

film_t *create_film(char *title, char *name, long year);
film_t *read_film(FILE *f);
void print_film(const film_t *film);
void free_film(film_t *film_ptr);
field_key key_value(const char *field);
int cmp_key_with_field(const char *key, const film_t *film, field_key field);
int cmp_struct_by_field(const film_t *f1, const film_t *f2, field_key field);
long get_year(const char *year_str);

#endif