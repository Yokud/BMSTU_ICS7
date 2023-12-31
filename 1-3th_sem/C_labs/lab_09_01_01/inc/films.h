#ifndef READ_AND_SEARCH_H
#define READ_AND_SEARCH_H

#include "film.h"

int get_count_of_films(FILE *f, size_t *count);
int read_films(FILE *f, film_t ***films, size_t *films_count, field_key key);
int insert_film(film_t **films, size_t films_count, size_t cur_films_count, film_t *film, field_key field);
film_t *bin_search(film_t **films, size_t films_count, char *key, field_key field);
void print_films(film_t **films, size_t films_count);
void free_films(film_t **films, size_t films_count);

#endif