// Целочисленный тип данных: int
// Алгоритм сортировки: Метод пузырька
// "Направление" упорядочивания: по возрастанию
// Создание файла: app.exe c file number
// number - это кол-во случайных чисел в файле
// Конвертирование текстового файла в бинарный: app.exe conv txt_file

#include "files.h"
#include "txt_to_bin.h"

int main(int argc, char **argv)
{
    FILE *f;
    int rc = 0;

    if (argc < 3)
        rc = ARGS_INPUT_ERROR;
    else
    {
        if (!strcmp(argv[1], "c"))
            if (argc != 4)
                rc = ARGS_INPUT_ERROR;
            else
            {
                f = fopen(argv[2], "wb");
                if (f)
                {
                    create_bin_file(f, argv[3]);
                    fclose(f);
                }
                else
                    rc = FILE_ERROR;
            }
        else if (!strcmp(argv[1], "p"))
        {
            f = fopen(argv[2], "rb");
            if (f_has_only_numbers(f) == OK)
            {
                rc = print_bin_file(f);
                fclose(f);
            }
            else
                rc = FILE_ERROR;
        }
        else if (!strcmp(argv[1], "s"))
        {
            f = fopen(argv[2], "rb+");
            if (f_has_only_numbers(f) == OK)
            {
                rc = sort_file(f);
                fclose(f);
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
        else
            rc = ARGS_INPUT_ERROR;
    }

    return rc;
}