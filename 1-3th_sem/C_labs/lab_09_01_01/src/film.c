#include "film.h"


film_t *create_film(char *title, char *name, long year)
{
    film_t *film_ptr = malloc(sizeof(film_t));

    if (film_ptr)
    {
        film_ptr->title = str_dup(title);
        film_ptr->name = str_dup(name);

        if (film_ptr->title && film_ptr->name && year > 0)
            film_ptr->year = year;
        else
        {
            free_film(film_ptr);
            film_ptr = NULL;
        }
    }

    return film_ptr;
}

film_t *read_film(FILE *f)
{
    film_t *film_ptr;
    char *title, *name;
    long year;
    size_t name_len, title_len;

    if (getline(&title, &title_len, f))
        return NULL;

    if (getline(&name, &name_len, f))
    {
        free(title);
        return NULL;
    }

    if (fscanf(f, "%ld\n", &year) != 1)
    {
        free(title);
        free(name);
        return NULL;
    }

    film_ptr = create_film(title, name, year);
    free(title);
    free(name);

    return film_ptr;
}

void free_film(film_t *film_ptr)
{
    if (!film_ptr)
        return;

    free(film_ptr->title);
    free(film_ptr->name);
    free(film_ptr);
}

field_key key_value(const char *field)
{
    if (!strcmp(field, "title"))
        return TITLE;
    else if (!strcmp(field, "name"))
        return NAME;
    else if (!strcmp(field, "year"))
        return YEAR;
    else
        return KEY_ERR;
}

int cmp_key_with_field(const char *key, const film_t *film, field_key field)
{
    if (field == TITLE)
        return strcmp(key, film->title);
    else if (field == NAME)
        return strcmp(key, film->name);
    else
        return get_year(key) - film->year;
}

int cmp_struct_by_field(const film_t *f1, const film_t *f2, field_key field)
{
    if (field == TITLE)
        return strcmp(f1->title, f2->title);
    else if (field == NAME)
        return strcmp(f1->name, f2->name);
    else
        return f1->year - f2->year;
}

void print_film(const film_t *film)
{
    printf("%s\n%s\n%ld\n", film->title, film->name, film->year);
}

long get_year(const char *year_str)
{
    for (size_t i = 0; year_str[i]; i++)
        if (!isdigit(year_str[i]))
            return YEAR_ERROR;

    return atol(year_str);
}