#include <check.h>
#include <math.h>
#include "data_structure.h"


START_TEST(test_add_matrs)
{
    matrix_t a, b, c, ans;
    long n = 2;
    long m = 3;
    int rc;
    create_matrix(&a, n, m);
    create_matrix(&b, n, m);
    create_matrix(&ans, n, m);
    
    for (long i = 0; i < n; i++)
        for (long j = 0; j < m; j++)
        {
            a.matrix[i][j] = i + j;
            b.matrix[i][j] = i - j;
            ans.matrix[i][j] = 2 * i;
        }
    
    matrix_add(&a, &b, &c);
    rc = matrix_cmp(&c, &ans);
    free_matrix(&a);
    free_matrix(&b);
    free_matrix(&c);
    free_matrix(&ans);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_add_dif_dim_matrs)
{
    matrix_t a, b, c;
    int rc;
    create_matrix(&a, 2, 3);
    create_matrix(&b, 3, 3);

    for (long i = 0; i < 2; i++)
        for (long j = 0; j < 3; j++)
            a.matrix[i][j] = i + j;

    for (long i = 0; i < 3; i++)
        for (long j = 0; j < 3; j++)
            b.matrix[i][j] = i + j;

    rc = matrix_add(&a, &b, &c);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, DIM_ERROR);
}
END_TEST

START_TEST(test_mult_matrs)
{
    matrix_t a, b, c, ans;
    int rc;

    create_matrix(&a, 2, 3);
    create_matrix(&b, 3, 2);
    create_matrix(&ans, 2, 2);
    
    for (long i = 0; i < 2; i++)
        for (long j = 0; j < 3; j++)
            a.matrix[i][j] = i + j;

    for (long i = 0; i < 3; i++)
        for (long j = 0; j < 2; j++)
            b.matrix[i][j] = i + j;

    ans.matrix[0][0] = 5;
    ans.matrix[0][1] = 8;
    ans.matrix[1][0] = 8;
    ans.matrix[1][1] = 14;
    
    matrix_mult(&a, &b, &c);

    FILE *f = fopen("res.txt", "w");
    fprint_matrix(f, &c);
    fclose(f);

    rc = matrix_cmp(&c, &ans);
    free_matrix(&a);
    free_matrix(&b);
    free_matrix(&c);
    free_matrix(&ans);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_mult_dif_dir_matrs)
{
    matrix_t a, b, c;
    int rc;

    create_matrix(&a, 2, 3);
    create_matrix(&b, 2, 2);
    
    for (long i = 0; i < 2; i++)
        for (long j = 0; j < 3; j++)
            a.matrix[i][j] = i + j;

    for (long i = 0; i < 2; i++)
        for (long j = 0; j < 2; j++)
            b.matrix[i][j] = i + j;
    
    rc = matrix_mult(&a, &b, &c);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, DIM_ERROR);
}
END_TEST

START_TEST(test_det_2_order_matr)
{
    matrix_t a;
    int rc;
    long n = 2;
    double det, eps, ans;

    eps = 1e-6;
    ans = -2.0;
    create_matrix(&a, n, n);
    int el = 1;
    for (long i = 0; i < n; i++)
        for (long j = 0; j < n; j++)
            a.matrix[i][j] = el++;

    matrix_det(&a, &det);
    rc = fabs(det - ans) < eps ? 1 : 0;
    free_matrix(&a);
    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_det_n_order_matr)
{
    matrix_t a;
    int rc;
    long n = 3;
    double det, eps, ans;

    eps = 1e-6;
    ans = 0.0;
    create_matrix(&a, n, n);
    int el = 1;
    for (long i = 0; i < n; i++)
        for (long j = 0; j < n; j++)
            a.matrix[i][j] = el++;

    matrix_det(&a, &det);
    printf("%g\n", det);
    rc = fabs(det - ans) < eps ? 1 : 0;
    free_matrix(&a);
    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(test_det_not_quadr_matr)
{
    matrix_t a;
    int rc;
    double det;

    create_matrix(&a, 2, 3);
    int el = 1;
    for (long i = 0; i < 2; i++)
        for (long j = 0; j < 3; j++)
            a.matrix[i][j] = el++;

    rc = matrix_det(&a, &det);
    free_matrix(&a);
    ck_assert_int_eq(rc, DIM_ERROR);
}
END_TEST

Suite* add_mult_det_suite(void)
{
    Suite *s;
    TCase *tc_add;
    TCase *tc_mult;
    TCase *tc_det;

    s = suite_create("add_mult_det");

    tc_add = tcase_create("add");

    tcase_add_test(tc_add, test_add_matrs);
    tcase_add_test(tc_add, test_add_dif_dim_matrs);

    suite_add_tcase(s, tc_add);
    
    tc_mult = tcase_create("mult");

    tcase_add_test(tc_mult, test_mult_matrs);
    tcase_add_test(tc_mult, test_mult_dif_dir_matrs);

    suite_add_tcase(s, tc_mult);
    
    tc_det = tcase_create("det");

    tcase_add_test(tc_det, test_det_2_order_matr);
    tcase_add_test(tc_det, test_det_n_order_matr);
    tcase_add_test(tc_det, test_det_not_quadr_matr);

    suite_add_tcase(s, tc_det);
    
    return s;
}
