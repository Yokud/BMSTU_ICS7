// Допускается, что значения полей структуры в текстовом файле
// расположены на каждой строке

#include "txt_to_bin.h"

void delete_txt_extention(filename name, char *txt_name)
{
    size_t i;

    for (i = 0; txt_name[i] != '.'; i++)
    {
        name[i + 1] = '\0';
        name[i] = txt_name[i];
    }
}

int txt_to_bin(FILE *txt, char *txt_name, FILE *bin)
{
    filename name;
    product prod;
    size_t n;
    int rc = 1;

    delete_txt_extention(name, txt_name);
    strcat(name, ".bin");
    memset(&prod, 0, sizeof(product));

    bin = fopen(name, "wb");
    if (bin)
    {
        n = count_of_prods_in_txt(txt);
        for (size_t i = 0; i < n; i++)
        {
            fscan_prod(txt, &prod);
            fwrite(&prod, sizeof(product), 1, bin);
        }
    }
    else
        rc = -2;

    fclose(bin);
    
    return rc;
}

void fscan_prod(FILE *f, product *prod)
{
    fread_line(f, prod->name, NAME_LEN_MAX);
    fread_line(f, prod->manufacturer, MANUFACTURER_LEN_MAX);
    fscanf(f, "%u\n%u\n", &(prod->price), &(prod->count));
}

int fread_line(FILE *f, char *s, size_t n)
{
    int ch;
    size_t i = 0;
    while ((ch = fgetc(f)) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
        else
            return -1;
        
    s[i] = '\0';
    if (!i)
        return -2;

    return 0;
}

size_t count_of_prods_in_txt(FILE *txt)
{
    size_t count = 0;
    int ch;

    while ((ch = fgetc(txt)) != EOF)
        if (ch == '\n')
            count++;
    
    fseek(txt, 0, SEEK_SET);
    return (count + 1) / 4; // 4 - это кол-во полей в структуре product
}