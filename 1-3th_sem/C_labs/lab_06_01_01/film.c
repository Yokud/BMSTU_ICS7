#include "film.h"

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