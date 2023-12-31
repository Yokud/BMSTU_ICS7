#include "products.h"

void print_prod(product prod)
{
    printf("%s\n", prod.name);
    printf("%s\n", prod.manufacturer);
    printf("%u\n", prod.price);
    printf("%u\n", prod.count);
}

int get_product_by_pos(FILE *f, product *prod, size_t pos)
{
    int rc = 0;

    if (fseek(f, pos * sizeof(product), SEEK_SET))
        rc = -1;
    else
    {
        if (fread(prod, sizeof(product), 1, f) != 1)
            rc = -1;
    }

    return rc;
}

int put_product_by_pos(FILE *f, product prod, size_t pos)
{
    int rc = 0;

    if (fseek(f, pos * sizeof(product), SEEK_SET))
        rc = -1;
    else
    {
        if (fwrite(&prod, sizeof(product), 1, f) != 1)
            rc = -1;
    }

    return rc;
}

void write_result(FILE *f, FILE *result)
{
    product prod;
    int rc;
    size_t size;

    memset(&prod, 0, sizeof(product));

    rc = file_size(f, &size);

    if (!rc && size)
    {
        size_t n = size / sizeof(product);
        for (size_t i = 0; i < n; i++)
        {
            fread(&prod, sizeof(product), 1, f);
            fwrite(&prod, sizeof(product), 1, result);
        }
    }
}

int sort_products(FILE *f)
{
    int rc = 0;
    size_t size;
    product prod1, prod2;

    memset(&prod1, 0, sizeof(product));
    memset(&prod2, 0, sizeof(product));

    rc = file_size(f, &size);

    if (!rc && size)
    {
        size_t n = size / sizeof(product);
        for (size_t i = 0; !rc && i < n - 1; i++)
            for (size_t j = 0; !rc && j < n - 1 - i; j++)
            {
                if (!(rc = get_product_by_pos(f, &prod1, j)))
                    rc = get_product_by_pos(f, &prod2, j + 1);

                if (!rc && (prod1.price < prod2.price ||
                    (prod1.count < prod2.count && prod1.price == prod2.price)))
                    rc = swap_products(f, prod1, j, prod2, j + 1);
            }
    }
    else
        rc = SIZE_ERROR;

    return rc;
}

int swap_products(FILE *f, product prod1, size_t prod1_pos, product prod2, size_t prod2_pos)
{
    int rc = put_product_by_pos(f, prod1, prod2_pos);

    if (!rc)
        rc = put_product_by_pos(f, prod2, prod1_pos);
    
    return rc;
}

int print_prods_by_substr(FILE *f, char *substr)
{
    int rc;
    product prod;
    size_t size;

    memset(&prod, 0, sizeof(product));

    rc = file_size(f, &size);

    if (!rc && size)
    {
        rc = NO_PRODS;
        size_t n = size / sizeof(product);
        
        for (size_t i = 0; i < n; i++)
        {
            fread(&prod, sizeof(product), 1, f);
            if (has_name_substr(prod.name, substr))
            {
                print_prod(prod);
                rc = 0;
            }
        }
    }
    else
        rc = SIZE_ERROR;
    
    return rc;
}

int has_name_substr(char name[NAME_LEN_MAX + 1], char *substr)
{
    int name_len = strlen(name);
    int substr_len = strlen(substr);

    if (substr_len > name_len)
        return 0;

    int is_the_same_chrs = 1;

    for (int i = name_len, j = substr_len; 
        is_the_same_chrs && j > -1; i--, j--)
        is_the_same_chrs = name[i] == substr[j];

    return is_the_same_chrs;
}

int add_product(FILE *f)
{
    int rc = 0;
    product new_prod, prod;
    size_t size;

    memset(&new_prod, 0, sizeof(product));
    memset(&prod, 0, sizeof(product));

    rc = file_size(f, &size);

    if (!rc && size)
    {
        if (!enter_prod(&new_prod))
        {
            size_t n = size / sizeof(product);

            if (!ftruncate(fileno(f), size + sizeof(product)))
            {
                size_t i;
                int is_inserted = 0;

                for (i = 0; !rc && !is_inserted && i < n; i++)
                    if (!(rc = get_product_by_pos(f, &prod, i)))
                    {
                        if (!rc && (new_prod.price > prod.price || (new_prod.count > prod.count && new_prod.price == prod.price)))
                        {
                            insert_new_prod(f, n, new_prod, i);
                            is_inserted = 1;
                        }
                    }
                    else
                        rc = READ_ERROR;

                if (!rc && !is_inserted)
                    insert_new_prod(f, n, new_prod, i);
            }
            else
                rc = TRUNC_ERROR;
        }
        else
            rc = INPUT_ERROR;
    }
    else
        rc = SIZE_ERROR;

    return rc;
}

void insert_new_prod(FILE *f, size_t prodc, product new_prod, size_t pos)
{
    product prod;

    memset(&prod, 0, sizeof(product));

    for (size_t j = prodc; j > pos; j--)
    {
        get_product_by_pos(f, &prod, j - 1);
        put_product_by_pos(f, prod, j);
    }

    put_product_by_pos(f, new_prod, pos);
}

int enter_prod(product *prod)
{
    int rc = 0;

    rc = read_line(prod->name, NAME_LEN_MAX + 1);
    if (!rc)
    {
        rc = read_line(prod->manufacturer, MANUFACTURER_LEN_MAX + 1);
        if (!rc)
        {
            if (scanf("%u", &(prod->price)) == 1)
            {
                if (scanf("%u", &(prod->count)) != 1)
                    rc = INPUT_ERROR;
            }
            else
                rc = INPUT_ERROR;
        }
    }
    else
        rc = INPUT_ERROR;

    return rc;
}

int print_prods_from_bin_file(FILE *bin)
{
    size_t size;
    int rc;
    product prod;

    rc = file_size(bin, &size);

    if (!rc && size)
    {
        size_t n = size / sizeof(product);
        for (size_t i = 0; !rc && i < n; i++)
        {
            rc = get_product_by_pos(bin, &prod, i);

            if (!rc)
                print_prod(prod);
            else
                rc = INPUT_ERROR;
        }
    }
    else
        rc = SIZE_ERROR;
    
    return rc;
}