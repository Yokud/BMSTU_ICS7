#include "my_snprintf.h"
#include <stdio.h>
#include <string.h>
#include <check.h>

#define IS_EQUAL 1

START_TEST(test_d_usual)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n, "Some numbers: %d %d", 15, -3);
    ans_value = snprintf(ans, n, "Some numbers: %d %d", 15, -3);

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_d_string_overflow)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n, "Some numbers: %d %d %d %d", 9999, 9999, 9999, 9999);
    ans_value = snprintf(ans, n, "Some numbers: %d %d %d %d", 9999, 9999, 9999, 9999);

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_c_usual)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n, "Some char: %c", 'a');
    ans_value = snprintf(ans, n, "Some char: %c", 'a');

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_c_make_word)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n, "%c%c%c%c", 'I', 'v', 'a', 'n');
    ans_value = snprintf(ans, n, "%c%c%c%c", 'I', 'v', 'a', 'n');

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_s_usual)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n, "Some word: %s", "word");
    ans_value = snprintf(ans, n, "Some word: %s", "word");

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_ld_usual)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n, "Some numbers: %ld %ld", 15L, -3L);
    ans_value = snprintf(ans, n, "Some numbers: %ld %ld", 15L, -3L);

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_ld_void_str)
{
    size_t n = 32;
    size_t n1 = 1;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n1, "Some numbers: %ld %ld", 15L, -3L);
    ans_value = snprintf(ans, n1, "Some numbers: %ld %ld", 15L, -3L);

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_hd_usual)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    char *ans = malloc(n * sizeof(char));
    int rc;
    int res_value, ans_value;

    res_value = my_snprintf(s, n, "Some numbers: %hd %hd", (short) 15, (short) -3);
    ans_value = snprintf(ans, n, "Some numbers: %hd %hd", (short) 15, (short) -3);

    rc = !strcmp(s, ans) && res_value == ans_value;
    free(s);
    free(ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_s_null_arg)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    int rc;

    rc = my_snprintf(s, n, "Some word: %s", NULL);
    free(s);

    ck_assert_int_eq(rc, NULL_ERROR);
}
END_TEST

START_TEST(test_wrong_spec)
{
    size_t n = 32;
    char *s = malloc(n * sizeof(char));
    int rc;

    rc = my_snprintf(s, n, "Some word: %r", 123);
    free(s);

    ck_assert_int_eq(rc, ARG_ERROR);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_pos_tests, *tc_neg_tests;

    s = suite_create("test_my_snprintf");

    tc_pos_tests = tcase_create("pos_tests");
    tcase_add_test(tc_pos_tests, test_d_usual);
    tcase_add_test(tc_pos_tests, test_c_usual);
    tcase_add_test(tc_pos_tests, test_s_usual);
    tcase_add_test(tc_pos_tests, test_ld_usual);
    tcase_add_test(tc_pos_tests, test_hd_usual);
    tcase_add_test(tc_pos_tests, test_d_string_overflow);
    tcase_add_test(tc_pos_tests, test_c_make_word);
    tcase_add_test(tc_pos_tests, test_ld_void_str);
    suite_add_tcase(s, tc_pos_tests);
    
    tc_neg_tests = tcase_create("neg_tests");
    tcase_add_test(tc_neg_tests, test_s_null_arg);
    tcase_add_test(tc_neg_tests, test_wrong_spec);
    suite_add_tcase(s, tc_neg_tests);

    return s;
}