#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structure.h"

#define ARGS_ERROR 1

int main(int argc, char **argv)
{
    FILE *mtr_1, *mtr_2, *res;
    matrix_t mtr_a, mtr_b, mtr_c;
    int rc = OK;

    if (argc < 4)
        return ARGS_ERROR;

    if (!strcmp(argv[1], "a") || !strcmp(argv[1], "m"))
    {
        if (argc < 5)
            return ARGS_ERROR;

        mtr_1 = fopen(argv[2], "r");
        if (!mtr_1)
            return INPUT_ERROR;
        mtr_2 = fopen(argv[3], "r");
        if (!mtr_2)
        {
            fclose(mtr_1);
            return INPUT_ERROR;
        }

        if (!(rc = fscanf_matrix(mtr_1, &mtr_a)))
        {
            if (!(rc = fscanf_matrix(mtr_2, &mtr_b)))
            {
                if (!strcmp(argv[1], "a"))
                    rc = matrix_add(&mtr_a, &mtr_b, &mtr_c);
                else if (!strcmp(argv[1], "m"))
                    rc = matrix_mult(&mtr_a, &mtr_b, &mtr_c);

                if (!rc)
                {
                    res = fopen(argv[4], "w");
                    if (res)
                    {
                        fprint_matrix(res, &mtr_c);
                        fclose(res);
                    }
                    else
                        rc = INPUT_ERROR;
                    free_matrix(&mtr_c);
                }
                free_matrix(&mtr_a);
                free_matrix(&mtr_b);
            }
            else
                free_matrix(&mtr_a);
        }

        fclose(mtr_1);
        fclose(mtr_2);
    }
    else if (!strcmp(argv[1], "o"))
    {
        mtr_1 = fopen(argv[2], "r");
        if (!mtr_1)
            return INPUT_ERROR;

        if (!(rc = fscanf_matrix(mtr_1, &mtr_a)))
        {
            double det;

            rc = matrix_det(&mtr_a, &det);
            if (!rc)
            {
                res = fopen(argv[3], "w");
                fprintf(res, "%.6lf", det);
                fclose(res);
            }
            free_matrix(&mtr_a);
        }

        fclose(mtr_1);
    }
    else
        return ARGS_ERROR;

    return rc;
}
