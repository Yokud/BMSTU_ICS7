#include <check.h>
#include "list_type.h"
#include "rectangles.h"


START_TEST(test_pop_front_usual)
{
    node_t *list_rects = NULL;
    rect_t rect_1, rect_2, rect_3;
    void *ans = &rect_1;

    rect_1.width = 5.0, rect_1.height = 10.5;
    rect_2.width = 6.0, rect_2.height = 14.0;
    rect_3.width = 2.0, rect_3.height = 15.0;

    list_rects = push_back(list_rects, &rect_1);
    list_rects = push_back(list_rects, &rect_2);
    list_rects = push_back(list_rects, &rect_3);

    void *res = pop_front(&list_rects);
    free_list(list_rects);

    ck_assert_int_eq(res == ans, 1);
}
END_TEST

START_TEST(test_pop_front_void_list)
{
    node_t *list_rects = NULL;
    void *res = pop_front(&list_rects);

    ck_assert_int_eq(res == NULL, 1);
}
END_TEST

START_TEST(test_pop_front_null_ptr)
{
    void *res = pop_front(NULL);

    ck_assert_int_eq(res == NULL, 1);
}
END_TEST

START_TEST(test_pop_back_usual)
{
    node_t *list_rects = NULL;
    rect_t rect_1, rect_2, rect_3;
    void *ans = &rect_3;

    rect_1.width = 5.0, rect_1.height = 10.5;
    rect_2.width = 6.0, rect_2.height = 14.0;
    rect_3.width = 2.0, rect_3.height = 15.0;

    list_rects = push_back(list_rects, &rect_1);
    list_rects = push_back(list_rects, &rect_2);
    list_rects = push_back(list_rects, &rect_3);

    void *res = pop_back(&list_rects);
    free_list(list_rects);

    ck_assert_int_eq(res == ans, 1);
}
END_TEST

START_TEST(test_pop_back_void_list)
{
    node_t *list_rects = NULL;
    void *res = pop_back(&list_rects);

    ck_assert_int_eq(res == NULL, 1);
}
END_TEST

START_TEST(test_pop_back_null_ptr)
{
    void *res = pop_back(NULL);

    ck_assert_int_eq(res == NULL, 1);
}
END_TEST

START_TEST(test_append_usual)
{
    node_t *list_rects_a = NULL, *list_rects_b = NULL, *list_ans = NULL;
    rect_t rect_1, rect_2, rect_3, rect_4;
    int rc;

    rect_1.width = 5.0, rect_1.height = 10.5;
    rect_2.width = 6.0, rect_2.height = 14.0;
    rect_3.width = 2.0, rect_3.height = 15.0;
    rect_4.width = 4.5, rect_4.height = 3.7;

    list_rects_a = push_back(list_rects_a, &rect_1);
    list_rects_a = push_back(list_rects_a, &rect_2);
    list_rects_b = push_back(list_rects_b, &rect_3);
    list_rects_b = push_back(list_rects_b, &rect_4);
    list_ans = push_back(list_ans, &rect_1);
    list_ans = push_back(list_ans, &rect_2);
    list_ans = push_back(list_ans, &rect_3);
    list_ans = push_back(list_ans, &rect_4);

    append(&list_rects_a, &list_rects_b);

    rc = lists_cmp(list_rects_a, list_ans, rects_equal);
    free_list(list_rects_a);
    free_list(list_ans);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_append_first_list_void)
{
    node_t *list_rects_a = NULL, *list_rects_b = NULL, *list_ans = NULL;
    rect_t rect_1, rect_2;
    int rc;

    rect_1.width = 5.0, rect_1.height = 10.5;
    rect_2.width = 6.0, rect_2.height = 14.0;

    list_rects_b = push_back(list_rects_b, &rect_1);
    list_rects_b = push_back(list_rects_b, &rect_2);
    list_ans = push_back(list_ans, &rect_1);
    list_ans = push_back(list_ans, &rect_2);

    append(&list_rects_a, &list_rects_b);

    rc = lists_cmp(list_rects_a, list_ans, rects_equal);
    free_list(list_rects_a);
    free_list(list_ans);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_append_second_list_void)
{
    node_t *list_rects_a = NULL, *list_rects_b = NULL, *list_ans = NULL;
    rect_t rect_1, rect_2;
    int rc;

    rect_1.width = 5.0, rect_1.height = 10.5;
    rect_2.width = 6.0, rect_2.height = 14.0;

    list_rects_a = push_back(list_rects_a, &rect_1);
    list_rects_a = push_back(list_rects_a, &rect_2);
    list_ans = push_back(list_ans, &rect_1);
    list_ans = push_back(list_ans, &rect_2);

    append(&list_rects_a, &list_rects_b);

    rc = lists_cmp(list_rects_a, list_ans, rects_equal);
    free_list(list_rects_a);
    free_list(list_ans);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_reverse_usual)
{
    node_t *list_rects = NULL, *list_ans = NULL;
    rect_t rect_1, rect_2;
    int rc;

    rect_1.width = 5.0, rect_1.height = 10.5;
    rect_2.width = 6.0, rect_2.height = 14.0;

    list_rects = push_back(list_rects, &rect_1);
    list_rects = push_back(list_rects, &rect_2);
    list_ans = push_back(list_ans, &rect_2);
    list_ans = push_back(list_ans, &rect_1);

    list_rects = reverse(list_rects);

    rc = lists_cmp(list_rects, list_ans, rects_equal);
    free_list(list_rects);
    free_list(list_ans);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_reverse_void_list)
{
    node_t *list_rects = NULL;

    list_rects = reverse(list_rects);

    ck_assert_int_eq(list_rects == NULL, 1);
}
END_TEST

Suite *list_funcs_suite(void)
{
    Suite *s;
    TCase *tc_pop_front;
    TCase *tc_pop_back;
    TCase *tc_append;
    TCase *tc_reverse;

    s = suite_create("list_funcs");


    tc_pop_front = tcase_create("pop_front");

    tcase_add_test(tc_pop_front, test_pop_front_usual);
    tcase_add_test(tc_pop_front, test_pop_front_void_list);
    tcase_add_test(tc_pop_front, test_pop_front_null_ptr);

    suite_add_tcase(s, tc_pop_front);


    tc_pop_back = tcase_create("pop_back");

    tcase_add_test(tc_pop_back, test_pop_back_usual);
    tcase_add_test(tc_pop_back, test_pop_back_void_list);
    tcase_add_test(tc_pop_back, test_pop_back_null_ptr);

    suite_add_tcase(s, tc_pop_back);


    tc_append = tcase_create("append");

    tcase_add_test(tc_append, test_append_usual);
    tcase_add_test(tc_append, test_append_first_list_void);
    tcase_add_test(tc_append, test_append_second_list_void);

    suite_add_tcase(s, tc_append);


    tc_reverse = tcase_create("reverse");

    tcase_add_test(tc_reverse, test_reverse_usual);
    tcase_add_test(tc_reverse, test_reverse_void_list);

    suite_add_tcase(s, tc_reverse);

    return s;
}