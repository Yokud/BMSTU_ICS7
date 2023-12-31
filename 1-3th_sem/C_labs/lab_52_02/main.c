#include "files.h"
#include "txt_to_bin.h"
#include "products.h"

int main(int argc, char **argv)
{
    int rc = 0;
    FILE *f_in, *f_out;
    if (argc < 3)
        rc = ARGS_INPUT_ERROR;
    else
    {
        if (!strcmp(argv[1], "sb"))
        {
            if (argc != 4)
                rc = ARGS_INPUT_ERROR;
            else 
            {
                f_in = fopen(argv[2], "rb+");
                f_out = fopen(argv[3], "wb");
                if (f_in)
                {
                    rc = sort_products(f_in);
                    fclose(f_in);
                    if (!rc)
                    {
                        f_in = fopen(argv[2], "rb");
                        write_result(f_in, f_out);
                        fclose(f_in);
                        fclose(f_out);
                    }
                    else
                        rc = FILE_ERROR;
                }
                else
                    rc = FILE_ERROR;
            }
        }
        else if (!strcmp(argv[1], "fb"))
        {
            if (argc != 4)
                rc = ARGS_INPUT_ERROR;
            else
            {
                f_in = fopen(argv[2], "rb");
                if (f_in)
                {
                    rc = print_prods_by_substr(f_in, argv[3]);
                    fclose(f_in);
                }
                else
                    rc = FILE_ERROR;
            }
        }
        else if (!strcmp(argv[1], "ab"))
        {
            f_in = fopen(argv[2], "rb+");
            if (f_in)
            {
                rc = add_product(f_in);
                fclose(f_in);
            }
            else
                rc = FILE_ERROR;
        }
        else if (!strcmp(argv[1], "conv"))
        {
            FILE *txt, *bin = NULL;

            txt = fopen(argv[2], "r");
            if (txt)
            {
                rc = txt_to_bin(txt, argv[2], bin);
                fclose(txt);
                fclose(bin);
            }
            else
                rc = FILE_ERROR;
        }
        else if (!strcmp(argv[1], "pb"))
        {
            FILE *f;
            f = fopen(argv[2], "rb");
            rc = print_prods_from_bin_file(f);
            fclose(f);
        }
        else
            rc = ARGS_INPUT_ERROR;
    }

    return rc;
}