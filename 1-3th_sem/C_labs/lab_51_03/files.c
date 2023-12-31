#include "files.h"

int f_has_only_numbers(FILE *f)
{
    int num;
    int rc = 0;

    if (f == NULL)
        rc = FILE_ERROR;

    if (!rc && fread(&num, sizeof(int), 1, f) == 1)
    {
        while (fread(&num, sizeof(int), 1, f) == 1);

        if (!feof(f))
            rc = INPUT_ERROR;
    }
    else
        rc = FILE_ERROR;
    
    return rc;
}

void print_file(FILE *f)
{
    char str[16];
    while (fgets(str, sizeof(str), f))
        printf("%s", str);
}

size_t file_size(FILE *f, size_t *size)
{
    long sz;
    if (fseek(f, 0L, SEEK_END))
        return FILE_ERROR;

    sz = ftell(f);
    if (sz < 0)
        return FILE_ERROR;
    
    *size = sz;
    return fseek(f, 0L, SEEK_SET);
}

size_t str_to_pos_int(char *s)
{
    size_t number = 0;

    for (size_t i = 0; s[i] != '\0'; i++)
        if (s[i] >= '0' && s[i] <= '9')
            number = 10 * number + (s[i] - '0');
        else
            return 0;

    return number;
}

void create_bin_file(FILE *f, char *number)
{
    size_t count;
    count = str_to_pos_int(number);

    for (size_t i = 0; i < count; i++)
    {
        int rand_num = rand();
        fwrite(&rand_num, sizeof(int), 1, f);
    }
}

int print_bin_file(FILE *f)
{
    size_t size;
    int num, rc;
    size_t read;

    rc = file_size(f, &size);

    if (rc == 0 && size)
    {
        for (size_t i = 0; !rc && i < size / sizeof(int); i++)
        {
            read = fread(&num, sizeof(int), 1, f);

            if (read == 1)
                printf("%d ", num);
            else
                rc = INPUT_ERROR;
        }
    }
    else
        rc = FILE_ERROR;
    
    return rc;
}

int sort_file(FILE *f)
{
    size_t size;
    size_t n;
    int num1, num2, rc;

    rc = file_size(f, &size);
    if (rc == 0 && size)
    {
        n = size / sizeof(int);
        for (size_t i = 0; !rc && i < n - 1; i++)
            for (size_t j = 0; !rc && j < n - 1 - i; j++)
                if (!get_number_by_pos(f, &num1, j))
                {
                    if (!get_number_by_pos(f, &num2, j + 1))
                    {
                        if (num1 > num2)
                        {
                            if (!put_number_by_pos(f, num1, j + 1))
                            {
                                if (put_number_by_pos(f, num2, j))
                                    rc = PUT_ERROR;
                            }
                            else 
                                rc = PUT_ERROR; 
                        }
                    }
                    else
                        rc = READ_ERROR;
                }
                else
                    rc = READ_ERROR;          
    }
    else
        rc = FILE_ERROR;
    
    return rc;
}

int get_number_by_pos(FILE *f, int *num, size_t pos)
{
    int rc = 0;

    if (fseek(f, pos * sizeof(int), SEEK_SET))
        rc = -1;
    else
    {
        if (fread(num, sizeof(int), 1, f) != 1)
            rc = -1;
    }

    return rc;
}

int put_number_by_pos(FILE *f, int num, size_t pos)
{
    int rc = 0;

    if (fseek(f, pos * sizeof(int), SEEK_SET))
        rc = -1;
    else
    {
        if (fwrite(&num, sizeof(int), 1, f) != 1)
            rc = -1;
    }

    return rc;
}