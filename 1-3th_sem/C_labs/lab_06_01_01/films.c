#include "films.h"

int fread_line(FILE *f, char s[], size_t n)
{
    int ch;
    size_t i = 0;
    while ((ch = fgetc(f)) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
        else
            return STRLEN_ERROR;
    s[i] = '\0';

    if (!i)
        return INPUT_ERROR;

    return OK;
}

int read_film(FILE *f, film_t *film_dst)
{
    film_t film_src;
    int err = OK;

    if (feof(f))
        return END_READ_SUC;

    if ((err = fread_line(f, film_src.title, TITLE_LEN_MAX + 1)) == OK)
    {
        if ((err = fread_line(f, film_src.name, NAME_LEN_MAX + 1)) == OK)
        {
            if (fscanf(f, "%ld\n", &(film_src.year)) && film_src.year > 0)
                *film_dst = film_src;
            else
                err = YEAR_ERROR;
        }
    }

    return err;
}

int read_films(FILE *f, film_t films[], size_t *films_count, field_key field)
{
    film_t film;
    int err = OK;

    *films_count = 0;

    for (size_t i = 0; err == OK; i++)
        if ((err = read_film(f, &film)) == OK)
        {
            (*films_count)++;
            err = insert_film(films, i, film, field);
        }

    if (*films_count == 0)
        err = INPUT_ERROR;
    else if (err == END_READ_SUC)
        err = OK;
    
    return err;
}


int insert_film(film_t films[], size_t films_count, film_t film, field_key field)
{
    size_t pos = films_count;

    if (films_count >= FILMS_MAX)
        return OVERFLOW_ERROR;

    while (pos && cmp_struct_by_field(&film, &films[pos - 1], field) < 0)
        pos--;

    if (films_count)
        for (size_t i = films_count; i > pos; i--)
            films[i] = films[i - 1];
    
    films[pos] = film;

    return OK;
}


film_t *bin_search(film_t films[], size_t films_count, char *key, field_key field)
{
    size_t low, high, middle;

    low = 0;
    high = films_count - 1;
    middle = low + (high - low) / 2;  // Во избежание возможности переполнения

    while (low < high)
    {
        if (cmp_key_with_field(key, &films[middle], field) < 0)
            high = middle - 1;
        else if (cmp_key_with_field(key, &films[middle], field) > 0)
            low = middle + 1;
        else 
            return &films[middle];

        middle = low + (high - low) / 2;
    }

    if (!cmp_key_with_field(key, &films[middle], field))
        return &films[middle];
    else
        return NULL;
}

void print_films(film_t films[], size_t films_count)
{
    for (size_t i = 0; i < films_count; i++)
        print_film(&films[i]);
}