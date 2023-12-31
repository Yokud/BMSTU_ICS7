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
    int num;
    size_t wrote;
    int rc = 0;

    delete_txt_extention(name, txt_name);
    strcat(name, ".bin");

    bin = fopen(name, "wb");
    if (fscanf(txt, "%d", &num) == 1)
    {
        fwrite(&num, sizeof(int), 1, bin);
        while (!rc && fscanf(txt, "%d", &num) == 1)
        {
            wrote = fwrite(&num, sizeof(int), 1, bin);
            rc = (wrote != 1);
        }

        if (!feof(txt))
            rc = -1;
    }
    else
        rc = -2;
    
    return rc;
}