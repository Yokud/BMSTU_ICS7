#include "films.h"


int get_count_of_films(FILE *f, size_t *count)
{
    film_t *film_ptr;
    *count = 0;

    if (f == NULL || count == NULL)
        return INPUT_ERROR;

    while ((film_ptr = read_film(f)))
    {
        free_film(film_ptr);
        (*count)++;
    }

    if (*count == 0 || !feof(f))
        return INPUT_ERROR;

    rewind(f);
    return OK;
}

int read_films(FILE *f, film_t ***films, size_t *films_count, field_key field)
{
    film_t *film_ptr;
    int err = OK;

    if ((err = get_count_of_films(f, films_count)) != OK)
        return err;

    *films = calloc(*films_count, sizeof(film_t *));

    if (!(*films))
        return ALLOC_ERROR;

    for (size_t i = 0; err == OK && i < *films_count; i++)
        if ((film_ptr = read_film(f)))
            err = insert_film(*films, *films_count, i, film_ptr, field);
        else
        {
            free_films(*films, *films_count);
            err = INPUT_ERROR;
        }
    
    return err;
}


int insert_film(film_t **films, size_t films_count, size_t cur_films_count, film_t *film_ptr, field_key field)
{
    if (!films || !film_ptr || cur_films_count > films_count)
        return INPUT_ERROR;

    size_t pos = cur_films_count;

    while (pos && cmp_struct_by_field(film_ptr, films[pos - 1], field) < 0)
        pos--;

    for (size_t i = cur_films_count; i > pos; i--)
        films[i] = films[i - 1];
    
    films[pos] = film_ptr;

    return OK;
}


film_t *bin_search(film_t **films, size_t films_count, char *key, field_key field)
{
    size_t low, high, middle;

    low = 0;
    high = films_count - 1;
    middle = low + (high - low) / 2;  // Во избежание возможности переполнения

    while (low < high)
    {
        if (cmp_key_with_field(key, films[middle], field) < 0)
            high = middle - 1;
        else if (cmp_key_with_field(key, films[middle], field) > 0)
            low = middle + 1;
        else 
            return films[middle];

        middle = low + (high - low) / 2;
    }

    if (!cmp_key_with_field(key, films[middle], field))
        return films[middle];
    else
        return NULL;
}

void print_films(film_t **films, size_t films_count)
{
    for (size_t i = 0; i < films_count; i++)
        print_film(films[i]);
}

void free_films(film_t **films, size_t films_count)
{
    if (!films)
        return;

    for (size_t i = 0; i < films_count; i++)
        free_film(films[i]);
    free(films);
}