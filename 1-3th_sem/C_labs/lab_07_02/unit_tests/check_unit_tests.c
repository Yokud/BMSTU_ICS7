#include <check.h>
#include "sort_and_filter.h"
#include "compare.h"


START_TEST(test_sort_int_arr)
{
    int a[6] = {3, 4, -5, 8, 15, 1};
    int res[6] = {-5, 1, 3, 4, 8, 15};

    mysort(a, 6, sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_arr(a, res, 6, sizeof(int), cmp_int), 0);
}
END_TEST

START_TEST(test_sort_double_arr)
{
    double a[6] = {3.14, 2.71, 1.6, 15.1, 8.5, 1.1};
    double res[6] = {1.1, 1.6, 2.71, 3.14, 8.5, 15.1};

    mysort(a, 6, sizeof(double), cmp_double);
    ck_assert_int_eq(cmp_arr(a, res, 6, sizeof(double), cmp_double), 0);
}
END_TEST

START_TEST(test_sort_char_arr)
{
    char a[7] = {'b', 'a', 'n', 'a', 'n', 'a', '\0'};
    char res[7] = {'a', 'a', 'a', 'b', 'n', 'n', '\0'};

    mysort(a, 6, sizeof(char), cmp_chr);
    ck_assert_int_eq(cmp_arr(a, res, 6, sizeof(char), cmp_chr), 0);
}
END_TEST

START_TEST(test_sort_null)
{
    void *a = NULL;
    void *res = NULL;

    mysort(a, 5, sizeof(int), cmp_int);
    ck_assert_int_eq(cmp_arr(a, res, 5, sizeof(void *), cmp_int), 0);
}
END_TEST


START_TEST(test_key_usual)
{
    int rc;
    int a[6] = {1, 2, -3, 4, 5, 6};
    int *pb_a = malloc(6 * sizeof(int));
    int *pe_a = pb_a + 6;
    for (int i = 0; i < 6; i++)
        pb_a[i] = a[i];
    int *pb_dst = NULL, *pe_dst = NULL;

    rc = key(pb_a, pe_a, &pb_dst, &pe_dst);
    free_arr((void *) &pb_a, (void *) &pe_a);
    free_arr((void *) &pb_dst, (void *) &pe_dst);
    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_key_no_neg)
{
    int rc;
    int a[6] = {1, 2, 3, 4, 5, 6};
    int *pb_a = malloc(6 * sizeof(int));
    int *pe_a = pb_a + 6;
    for (int i = 0; i < 6; i++)
        pb_a[i] = a[i];
    int *pb_dst = NULL, *pe_dst = NULL;

    rc = key(pb_a, pe_a, &pb_dst, &pe_dst);
    free_arr((void *) &pb_a, (void *) &pe_a);
    free_arr((void *) &pb_dst, (void *) &pe_dst);
    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_key_first_neg)
{
    int rc;
    int a[6] = {-1, 2, 3, 4, 5, 6};
    int *pb_a = malloc(6 * sizeof(int));
    int *pe_a = pb_a + 6;
    for (int i = 0; i < 6; i++)
        pb_a[i] = a[i];
    int *pb_dst = NULL, *pe_dst = NULL;

    rc = key(pb_a, pe_a, &pb_dst, &pe_dst);
    free_arr((void *) &pb_a, (void *) &pe_a);
    ck_assert_int_eq(rc, FILTER_VOID_ERROR);
}
END_TEST

START_TEST(test_key_null)
{
    int rc;
    int *pb_a = NULL;
    int *pe_a = NULL;
    int *pb_dst, *pe_dst;

    rc = key(pb_a, pe_a, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, DATA_ERROR);
}
END_TEST

START_TEST(test_key_dst_null)
{
    int rc;
    int *pb_a = malloc(6 * sizeof(int));
    int *pe_a = pb_a + 6;

    rc = key(pb_a, pe_a, NULL, NULL);
    free_arr((void *) &pb_a, (void *) &pe_a);
    ck_assert_int_eq(rc, DATA_ERROR);
}
END_TEST

Suite* sort_and_key_suite(void)
{
    Suite *s;
    TCase *tc_sort;
    TCase *tc_key;

    s = suite_create("sort_and_key");

    tc_sort = tcase_create("sort");

    tcase_add_test(tc_sort, test_sort_int_arr);
    tcase_add_test(tc_sort, test_sort_double_arr);
    tcase_add_test(tc_sort, test_sort_char_arr);
    tcase_add_test(tc_sort, test_sort_null);

    suite_add_tcase(s, tc_sort);

    tc_key = tcase_create("key");

    tcase_add_test(tc_key, test_key_usual);
    tcase_add_test(tc_key, test_key_no_neg);
    tcase_add_test(tc_key, test_key_first_neg);
    tcase_add_test(tc_key, test_key_null);
    tcase_add_test(tc_key, test_key_dst_null);

    suite_add_tcase(s, tc_key);

    return s;
}
