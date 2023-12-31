#include "sort.h"

#define EXIT -1

struct TheatreTable thTbl = {NULL, 0, 0};
struct KeyTable keyTbl ={NULL, 0};

int menu()
{
    int operation = 0;
    int tmp;
    char name[LEN_NAME + 1];

    struct Theatre tmp_theatre;

    printf("\nМЕНЮ (Выберите операцию):\n\t"
           "1 - Загрузка таблицы из файла\n\t"
           "2 - Сортировка таблицы\n\t"
           "3 - Сортировка таблицы по ключу\n\t"
           "4 - Добавление записи в таблицу\n\t"
           "5 - Удаление записи из таблицы\n\t"
           "6 - Создание таблицы по ключу\n\t"
           "7 - Вывод таблицы по ключу\n\t"
           "8 - Вывод списка ключей\n\t"
           "9 - Вывод таблицы\n\t"
           "10 - Поиск\n\t"
           "11 - Сравнение времени сортировки\n\t"
           "0 - Выход из программы\n");

    printf("Ваша операция: ");
    fflush(stdin);

    if (scanf("%d", &operation) == 1)
    {
        if (operation == 0)
        {
            if (thTbl.ptr_first != NULL)
                save_theatre_table(name, &thTbl);
            clear_table(&thTbl);
            return EXIT;
        }
        else if (operation == 1)
        {
            puts("Загрузка из файла.");
            input_string("Введите имя файла ", name, LEN_NAME + 1);
            FILE *in = fopen(name, "r");
            if (load_table(in, &thTbl) != 0)
                printf("ОШИБКА ЗАГРУЗКИ.\n");
            else
                printf("Загружено.\n");
        }
        else if (operation == 2)
        {
            if (thTbl.ptr_first != NULL && thTbl.size != 0)
            {
                sort_theatre_table(&thTbl);
                printf("Таблица репертуаров успешно отсортирована\n");
            }
            else
                printf("Таблица пуста или ещё не загружена\n");
        }
        else if (operation == 3)
        {
            if (keyTbl.ptr_first != NULL && keyTbl.n != 0)
            {
                sort_key_table(&keyTbl);
                printf("Таблица ключей успешно отсортирована\n");
            }
            else
                printf("Таблица ключей пуста или ещё не создана\n");
        }
        else if (operation == 4)
        {
            if (thTbl.ptr_first != NULL)
            {
                input_theatre(&tmp_theatre);
                add_to_table(&thTbl, &tmp_theatre);
                printf("Элемент добавлен в таблицу\n");
            }
            else
                printf("Таблица репертуаров ещё не создана\n");
        }
        else if (operation == 5)
        {
            if (thTbl.ptr_first != NULL && thTbl.size != 0)
            {
                input_number("Введите индекс театра, информацию о котором вы желаете удалить: ", &tmp, 1, thTbl.size);
                if (remove_from_table(&thTbl, tmp))
                    printf("Нет информации о театре по заданному индексу\n");
                else
                    printf("Элемент таблицы успешно удалён\n");
            }
            else
                printf("Таблица пуста или ещё не загружена\n");
        }
        else if (operation == 6)
        {
            if (thTbl.ptr_first != NULL && thTbl.size != 0)
            {
                create_key_table(&thTbl, &keyTbl);
                printf("Таблица по ключу создана успешно\n");
            }
            else
                printf("Таблица пуста или ещё не создана\n");
        }
        else if (operation == 7)
        {
            if (keyTbl.ptr_first != NULL && keyTbl.n != 0)
            {
                if (!check_keyTbl(&thTbl, &keyTbl))
                    print_theatre_table_by_key(&thTbl, &keyTbl);
                else
                    printf("Таблица ключей неактуальна\n");
            }
            else
                printf("Таблица ключей пуста или ещё не создана\n");
        }
        else if (operation == 8)
        {
            if (keyTbl.ptr_first != NULL && keyTbl.n != 0)
            {
                if (!check_keyTbl(&thTbl, &keyTbl))
                    print_key_table(&keyTbl);
                else
                    printf("Таблица ключей неактуальна\n");
            }
            else
                printf("Таблица ключей пуста или ещё не создана\n");
        }
        else if (operation == 9)
        {
            output_thTable_console(&thTbl);
        }
        else if (operation == 10)
        {
            search(&thTbl);
        }
        else if (operation == 11)
        {
            measure_sorting_time();
        }
        else
        {
            printf("Некорректный ввод.\n");
        }
    }
    else
    {
        printf("\nНекорректный ввод.\n");
    }
    return 0;
}


int main(void)
{
    setbuf(stdout, NULL);
    while (menu() == 0);

    return 0;
}