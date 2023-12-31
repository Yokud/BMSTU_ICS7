#include "sort_and_filter.h"
#include "get_and_write_data.h"
#include "compare.h"

#define ARGS_ERROR -1

int main(int argc, char **argv)
{
    FILE *f_in, *f_out;
    long count = 0;
    int *arr, *arr_end, *new_arr, *new_arr_end;
    int rc = OK;

    arr = NULL;
    arr_end = NULL;
    new_arr = NULL;
    new_arr_end = NULL;

    if (argc < 3)
        return ARGS_ERROR;

    if ((f_in = fopen(argv[1], "r")) == NULL)
        return FILE_ERROR;

    if ((rc = get_count(f_in, &count)) == OK)
    {
        rc = create_arr(&arr, &arr_end, count);

        if (rc == OK && (rc = read(f_in, arr, arr_end)) == OK)
        {
            if (argc == 4)
            {
                if (strcmp(argv[3], "f"))
                {
                    free_arr((void *) &arr, (void *) &arr_end);
                    rc = ARGS_ERROR;
                }
                else
                {
                    rc = key(arr, arr_end, &new_arr, &new_arr_end);
                    free_arr((void *) &arr, (void *) &arr_end);
                }
            }

            if (rc == OK)
            {
                f_out = fopen(argv[2], "w");

                if (argc == 4)
                {
                    mysort(new_arr, new_arr_end - new_arr, sizeof(int), cmp_int);
                    write(f_out, new_arr, new_arr_end);
                    free_arr((void *) &new_arr, (void *) &new_arr_end); 
                }
                else
                {
                    mysort(arr, arr_end - arr, sizeof(int), cmp_int);
                    write(f_out, arr, arr_end);
                    free_arr((void *) &arr, (void *) &arr_end);
                }

                fclose(f_out);
            }   
        }
    }

    fclose(f_in);

    return rc;
}