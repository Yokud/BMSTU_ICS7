#include "films.h"

#define ARGS_ERROR -1

int main(int argc, char *argv[])
{
    int rc = OK;
    FILE *f;
    film_t films[FILMS_MAX];
    film_t *sought_film; // Искомый фильм
    size_t f_count;
    field_key field;

    if (argc < 3 || argc > 4)
        return ARGS_ERROR;

    f = fopen(argv[1], "r");

    if (f == NULL)
        return INPUT_ERROR;

    if ((field = key_value(argv[2])) == KEY_ERR)
        return KEY_ERROR;
            
    if ((rc = read_films(f, films, &f_count, field)) == OK)
    {
        if (argc == 4)
        {
            if (field == YEAR && get_year(argv[3]) == YEAR_ERROR)
                rc = YEAR_ERROR;
            else
            {
                sought_film = bin_search(films, f_count, argv[3], field);

                if (sought_film != NULL)
                    print_film(sought_film);
                else
                    printf("Not found\n");
            }
        }
        else
            print_films(films, f_count);
    }
    else
        rc = INPUT_ERROR;

    fclose(f);
    
    return rc;
}