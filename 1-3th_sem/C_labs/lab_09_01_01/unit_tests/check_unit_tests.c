#include <check.h>
#include "films.h"


START_TEST(test_insert_film_by_title)
{
    size_t n = 4;
    film_t **films, *new_film, **res;
    int rc;

    films = calloc(n, sizeof(film_t *));
    res = calloc(n, sizeof(film_t *));

    res[0] = create_film("Film_1", "Name_1", 1);
    res[1] = create_film("Film_2", "Name_2", 3);
    res[2] = create_film("Film_3", "Name_3", 4);
    res[3] = create_film("Film_4", "Name_4", 5);

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    new_film = create_film("Film_3", "Name_3", 4);

    insert_film(films, n, n - 1, new_film, TITLE);

    for (size_t i = 0; i < n; i++)
        rc = strcmp((films[i])->title, (res[i])->title) || strcmp((films[i])->name, (res[i])->name) || (films[i])->year != (res[i])->year;

    free_films(films, n);
    free_films(res, n);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_insert_film_by_name)
{
    size_t n = 4;
    film_t **films, *new_film, **res;
    int rc;

    films = calloc(n, sizeof(film_t *));
    res = calloc(n, sizeof(film_t *));

    res[0] = create_film("Film_1", "Name_1", 1);
    res[1] = create_film("Film_2", "Name_2", 3);
    res[2] = create_film("Film_3", "Name_3", 4);
    res[3] = create_film("Film_4", "Name_4", 5);

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    new_film = create_film("Film_3", "Name_3", 4);

    insert_film(films, n, n - 1, new_film, NAME);

    for (size_t i = 0; i < n; i++)
        rc = strcmp((films[i])->title, (res[i])->title) || strcmp((films[i])->name, (res[i])->name) || (films[i])->year != (res[i])->year;

    free_films(films, n);
    free_films(res, n);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_insert_film_by_year)
{
    size_t n = 4;
    film_t **films, *new_film, **res;
    int rc;

    films = calloc(n, sizeof(film_t *));
    res = calloc(n, sizeof(film_t *));

    res[0] = create_film("Film_1", "Name_1", 1);
    res[1] = create_film("Film_2", "Name_2", 3);
    res[2] = create_film("Film_3", "Name_3", 4);
    res[3] = create_film("Film_4", "Name_4", 5);

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    new_film = create_film("Film_3", "Name_3", 4);

    insert_film(films, n, n - 1, new_film, YEAR);

    for (size_t i = 0; i < n; i++)
        rc = strcmp((films[i])->title, (res[i])->title) || strcmp((films[i])->name, (res[i])->name) || (films[i])->year != (res[i])->year;

    free_films(films, n);
    free_films(res, n);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_insert_film_null_ptr)
{
    size_t n = 4;
    film_t **films, *new_film;
    int rc;

    films = calloc(n, sizeof(film_t *));

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    new_film = NULL;

    rc = insert_film(films, n, n - 1, new_film, YEAR);

    free_films(films, n);

    ck_assert_int_eq(rc, INPUT_ERROR);
}
END_TEST

START_TEST(test_insert_film_null_films_ptr)
{
    size_t n = 4;
    film_t **films, *new_film;
    int rc;

    films = NULL;

    new_film = create_film("Film_4", "Name_4", 5);

    rc = insert_film(films, n, n - 1, new_film, YEAR);

    free_film(new_film);

    ck_assert_int_eq(rc, INPUT_ERROR);
}
END_TEST

START_TEST(test_insert_film_out_of_range)
{
    size_t n = 4;
    film_t **films, *new_film;
    int rc;

    films = calloc(n, sizeof(film_t *));

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    new_film = create_film("Film_4", "Name_4", 5);

    rc = insert_film(films, n, n + 1, new_film, YEAR);

    free_films(films, n);
    free_film(new_film);

    ck_assert_int_eq(rc, INPUT_ERROR);
}
END_TEST

START_TEST(test_find_film_by_title)
{
    size_t n = 3;
    film_t **films, *res;
    int rc;
    char *key = "Film_1";

    films = calloc(n, sizeof(film_t *));

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    res = bin_search(films, n, key, TITLE);
    rc = res != NULL;

    free_films(films, n);

    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_find_film_by_name)
{
    size_t n = 3;
    film_t **films, *res;
    int rc;
    char *key = "Name_2";

    films = calloc(n, sizeof(film_t *));

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    res = bin_search(films, n, key, NAME);
    rc = res != NULL;

    free_films(films, n);

    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_find_film_by_year)
{
    size_t n = 3;
    film_t **films, *res;
    int rc;
    char *key = "3";

    films = calloc(n, sizeof(film_t *));

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    res = bin_search(films, n, key, YEAR);
    rc = res != NULL;

    free_films(films, n);

    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_find_film_not_found)
{
    size_t n = 3;
    film_t **films, *res;
    int rc;
    char *key = "7";

    films = calloc(n, sizeof(film_t *));

    films[0] = create_film("Film_1", "Name_1", 1);
    films[1] = create_film("Film_2", "Name_2", 3);
    films[2] = create_film("Film_4", "Name_4", 5);

    res = bin_search(films, n, key, YEAR);
    rc = res != NULL;

    free_films(films, n);

    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *insert_find_suite(void)
{
    Suite *s;
    TCase *tc_insert;
    TCase *tc_find;

    s = suite_create("insert_find");

    tc_insert = tcase_create("insert");

    tcase_add_test(tc_insert, test_insert_film_by_title);
    tcase_add_test(tc_insert, test_insert_film_by_name);
    tcase_add_test(tc_insert, test_insert_film_by_year);
    tcase_add_test(tc_insert, test_insert_film_null_ptr);
    tcase_add_test(tc_insert, test_insert_film_null_films_ptr);
    tcase_add_test(tc_insert, test_insert_film_out_of_range);

    suite_add_tcase(s, tc_insert);

    tc_find = tcase_create("find");

    tcase_add_test(tc_find, test_find_film_by_title);
    tcase_add_test(tc_find, test_find_film_by_name);
    tcase_add_test(tc_find, test_find_film_by_year);
    tcase_add_test(tc_find, test_find_film_not_found);

    suite_add_tcase(s, tc_find);

    return s;
}