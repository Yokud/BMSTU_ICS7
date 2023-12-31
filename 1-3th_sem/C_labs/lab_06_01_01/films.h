#ifndef READ_AND_SEARCH_H
#define READ_AND_SEARCH_H

#include "film.h"

#define END_READ_SUC 42

int read_film(FILE *f, film_t *film_dst);
int read_films(FILE *f, film_t films[], size_t *films_count, field_key key);
int insert_film(film_t films[], size_t films_count, film_t film, field_key field);
film_t *bin_search(film_t films[], size_t films_count, char *key, field_key field);
int fread_line(FILE *f, char s[], size_t n);
void print_films(film_t films[], size_t films_count);

#endif