#include <check.h>
#include "sparse_matrices.h"


#define IS_EQUAL 1

static int matrices_equal(sparse_matrix_t *matr_a, sparse_matrix_t *matr_b);


START_TEST(test_add_usual)
{
    sparse_matrix_t *matr_a = malloc(sizeof(sparse_matrix_t));
    sparse_matrix_t *matr_b = malloc(sizeof(sparse_matrix_t));
    sparse_matrix_t *ans = malloc(sizeof(sparse_matrix_t));
    sparse_matrix_t *cur_a = matr_a, *cur_b = matr_b, *cur_ans = ans;
    long n, m, elem;
    int rc;

    n = 2;
    m = 2;
    elem = 1;
    cur_a->next = cur_a;
    cur_b->next = cur_b;
    cur_ans->next = cur_ans;

    for (long i = 0; i < n; i++)
        for (long j = 0; j < m; j++)
        {
            cur_a = cur_a->next;
            cur_b = cur_b->next;
            cur_ans = cur_ans->next;

            cur_a->row = i;
            cur_a->col = j;
            cur_a->elem = elem;

            cur_b->row = i;
            cur_b->col = j;
            cur_b->elem = elem;

            cur_ans->row = i;
            cur_ans->col = j;
            cur_ans->elem = 2 * elem++;

            cur_a->next = malloc(sizeof(sparse_matrix_t));
            cur_b->next = malloc(sizeof(sparse_matrix_t));
            cur_ans->next = malloc(sizeof(sparse_matrix_t));
        }
    
    free(cur_a->next);
    cur_a->next = NULL;
    free(cur_b->next);
    cur_b->next = NULL;
    free(cur_ans->next);
    cur_ans->next = NULL;

    sparse_matrix_t *res = add_matrices(matr_a, matr_b);

    rc = matrices_equal(res, ans);
    free_matrix(matr_a);
    free_matrix(matr_b);
    free_matrix(ans);
    free_matrix(res);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_add_null_ptrs)
{
    sparse_matrix_t *res = add_matrices(NULL, NULL);
    sparse_matrix_t *ans = NULL;
    int rc;

    rc = matrices_equal(res, ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_mul_usual)
{
    sparse_matrix_t *matr_a = malloc(sizeof(sparse_matrix_t));
    sparse_matrix_t *matr_b = malloc(sizeof(sparse_matrix_t));
    sparse_matrix_t *ans = malloc(sizeof(sparse_matrix_t));
    sparse_matrix_t *cur_a = matr_a, *cur_b = matr_b, *cur_ans = ans;
    long n, m, elem;
    int rc;

    n = 2;
    m = 2;
    elem = 1;
    cur_a->next = cur_a;
    cur_ans->next = cur_ans;

    for (long i = 0; i < n; i++)
        for (long j = 0; j < m; j++)
        {
            cur_a = cur_a->next;
            cur_ans = cur_ans->next;

            cur_a->row = i;
            cur_a->col = j;
            cur_a->elem = elem;

            cur_ans->row = i;
            cur_ans->col = j;
            cur_ans->elem = elem++;

            cur_a->next = malloc(sizeof(sparse_matrix_t));
            cur_ans->next = malloc(sizeof(sparse_matrix_t));
        }
    
    free(cur_a->next);
    cur_a->next = NULL;
    free(cur_ans->next);
    cur_ans->next = NULL;

    cur_b->row = 0;
    cur_b->col = 0;
    cur_b->elem = 1;
    cur_b->next = malloc(sizeof(sparse_matrix_t));
    cur_b = cur_b->next;
    cur_b->row = 1;
    cur_b->col = 1;
    cur_b->elem = 1;
    cur_b->next = NULL;

    sparse_matrix_t *res = mult_matrices(matr_a, matr_b);

    rc = matrices_equal(res, ans);
    free_matrix(matr_a);
    free_matrix(matr_b);
    free_matrix(ans);
    free_matrix(res);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_mul_null_ptrs)
{
    sparse_matrix_t *res = mult_matrices(NULL, NULL);
    sparse_matrix_t *ans = NULL;
    int rc;

    rc = matrices_equal(res, ans);

    ck_assert_int_eq(rc, IS_EQUAL);
}
END_TEST

START_TEST(test_lin_usual)
{
    sparse_matrix_t *matr_a = malloc(sizeof(sparse_matrix_t));
    sparse_matrix_t *cur_a = matr_a;
    long n, m, elem;
    int rc;

    n = 2;
    m = 2;
    elem = 1;
    cur_a->next = cur_a;

    for (long i = 0; i < n; i++)
        for (long j = 0; j < m; j++)
        {
            cur_a = cur_a->next;

            cur_a->row = i;
            cur_a->col = j;
            cur_a->elem = elem++;

            cur_a->next = malloc(sizeof(sparse_matrix_t));
        }
    
    free(cur_a->next);
    cur_a->next = NULL;

    rc = del_row_by_max_elem(&matr_a);
    free_matrix(matr_a);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_lin_null_ptr)
{
    int rc = del_row_by_max_elem(NULL);

    ck_assert_int_eq(rc, INPUT_ERROR);
}
END_TEST

Suite *matrix_funcs_suite(void)
{
    Suite *s;
    TCase *tc_add, *tc_mul, *tc_lin;

    s = suite_create("matrix_funcs");

    tc_add = tcase_create("tests_add");

    tcase_add_test(tc_add, test_add_usual);
    tcase_add_test(tc_add, test_add_null_ptrs);

    suite_add_tcase(s, tc_add);


    tc_mul = tcase_create("tests_mul");

    tcase_add_test(tc_mul, test_mul_usual);
    tcase_add_test(tc_mul, test_mul_null_ptrs);

    suite_add_tcase(s, tc_mul);


    tc_lin = tcase_create("tests_lin");

    tcase_add_test(tc_lin, test_lin_usual);
    tcase_add_test(tc_lin, test_lin_null_ptr);

    suite_add_tcase(s, tc_lin);

    return s;
}

static int matrices_equal(sparse_matrix_t *matr_a, sparse_matrix_t *matr_b)
{
    if (!matr_a && !matr_b)
        return 1;
    else if (!matr_a || !matr_b)
        return 0;

    sparse_matrix_t *cur_a, *cur_b;
    for (cur_a = matr_a, cur_b = matr_b; cur_a && cur_b; cur_a = cur_a->next, cur_b = cur_b->next)
        if (cur_a->row != cur_b->row || cur_a->col != cur_b->col || cur_a->elem != cur_b->elem)
            return 0;
    
    return !cur_a && !cur_b;
}