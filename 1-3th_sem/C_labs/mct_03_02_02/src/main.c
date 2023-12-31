#include "data_structure.h"


int main(void)
{
    matrix_t matr;
    size_t col;
    int rc = OK;

    if ((rc = scanf_matrix(&matr)))
        return rc;

    print_matrix(&matr);
    col = get_max_sum_in_col(&matr);
    del_col(&matr, col);
    print_matrix(&matr);
    free_matrix(&matr);

    return rc;
}