#include "sparse_matrices.h"
#include "alloc_strings.h"


int main(void)
{
    sparse_matrix_t *matr_a = NULL, *matr_b = NULL, *res = NULL;
    char *command_str;
    size_t command_str_len;
    command_t command;
    int rc = OK;

    if ((rc = getline(&command_str, &command_str_len, stdin)))
    {
        free(command_str);
        return rc;
    }

    command = get_command(command_str);
    free(command_str);

    switch (command)
    {
        case OUT:
            if (!(rc = create_matrix(&matr_a)))
                print_matrix(matr_a);
            break;
        case ADD:
            if (!(rc = create_matrix(&matr_a)))
            {
                if (!(rc = create_matrix(&matr_b)))
                {
                    if ((res = add_matrices(matr_a, matr_b)))
                        print_matrix(res);
                    else
                        rc = ALLOC_ERROR;
                }
            }
            break;
        case MUL:
            if (!(rc = create_matrix(&matr_a)))
            {
                if (!(rc = create_matrix(&matr_b)))
                {
                    if ((res = mult_matrices(matr_a, matr_b)))
                        print_matrix(res);
                    else
                        rc = ALLOC_ERROR;
                }
            }
            break;
        case LIN:
            if (!(rc = create_matrix(&matr_a)))
                if (!(rc = del_row_by_max_elem(&matr_a)))
                    print_matrix(matr_a);
            break;
        case UNKNOWN_COMMAND:
            return INPUT_ERROR;
    }

    free_matrix(matr_a);
    free_matrix(matr_b);
    free_matrix(res);

    return rc;
}