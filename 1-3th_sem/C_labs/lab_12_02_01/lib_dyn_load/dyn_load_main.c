#include <windows.h>
#include "dyn_arrs.h"
#include "compare.h"

#define ARGS_ERROR -1
#define LOAD_LIB_ERROR -2
#define FILE_ERROR -3
#define FILTER_VOID_ERROR -4

typedef int (__cdecl *fn_get_count_t)(FILE*, long*);
typedef int (__cdecl *fn_read_t)(FILE*, int*, int*);
typedef void (__cdecl *fn_write_t)(FILE*, int*, int*);

typedef void (__cdecl *fn_mysort_t)(void*, size_t, size_t, int (*)(const void*, const void*));
typedef int (__cdecl *fn_key_t)(const int*, const int*, int*, int*);

int main(int argc, char **argv)
{
    HMODULE hlib;
    fn_get_count_t get_count;
    fn_read_t read;
    fn_write_t write;

    fn_mysort_t mysort;
    fn_key_t key;

    FILE *f_in, *f_out;
    long count, new_count;
    int *arr, *arr_end, *new_arr, *new_arr_end;
    int rc = OK;

    arr = NULL;
    arr_end = NULL;
    new_arr = NULL;
    new_arr_end = NULL;



    hlib = LoadLibrary("io_and_proc_data.dll");
    if (!hlib)
        return LOAD_LIB_ERROR;

    get_count = (fn_get_count_t) GetProcAddress(hlib, "get_count");
    if (!get_count)
    {
        FreeLibrary(hlib);
        return LOAD_LIB_ERROR;
    }

    read = (fn_read_t) GetProcAddress(hlib, "read");
    if (!read)
    {
        FreeLibrary(hlib);
        return LOAD_LIB_ERROR;
    }

    write = (fn_write_t) GetProcAddress(hlib, "write");
    if (!write)
    {
        FreeLibrary(hlib);
        return LOAD_LIB_ERROR;
    }

    mysort = (fn_mysort_t) GetProcAddress(hlib, "mysort");
    if (!mysort)
    {
        FreeLibrary(hlib);
        return LOAD_LIB_ERROR;
    }

    key = (fn_key_t) GetProcAddress(hlib, "key");
    if (!key)
    {
        FreeLibrary(hlib);
        return LOAD_LIB_ERROR;
    }


    if (argc < 3)
    {
        FreeLibrary(hlib);
        return ARGS_ERROR;
    }

    if ((f_in = fopen(argv[1], "r")) == NULL)
    {
        FreeLibrary(hlib);
        return FILE_ERROR;
    }

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
                    if (!(rc = create_arr(&new_arr, &new_arr_end, count)))
                    {
                        new_count = key(arr, arr_end, new_arr, new_arr_end);

                        if (new_count > 0)
                        {
                            int *temp = realloc(new_arr, new_count * sizeof(int));

                            if (temp)
                            {
                                new_arr = temp;
                                new_arr_end = new_arr + new_count;
                            }
                            else
                            {
                                free_arr((void *) &new_arr, (void *) &new_arr_end);
                                rc = ALLOC_ERROR;
                            }
                        }
                        else
                        {
                            free_arr((void *) &new_arr, (void *) &new_arr_end);
                            rc = FILTER_VOID_ERROR;
                        }
                    }
                    
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
    FreeLibrary(hlib);

    return rc;
}