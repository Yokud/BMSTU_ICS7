#include "structures.h"


void input_theatre(struct Theatre *thtr)
{
    input_string("Введите название театра ", thtr->t_name, LEN_NAME + 1);
    input_string("Введите название спектакля ", thtr->p_name, LEN_NAME + 1);
    input_string("Введите фамилию режисера ", thtr->d_name, LEN_NAME + 1);
    input_number("Введите нижний диапазон цены ", &(thtr->low_price), 1, 80000);
    input_number("Введите верхний диапазон цены ", &(thtr->top_price), thtr->low_price, 100000);
    input_type("Введите тип спектакля (0-детский, 1-взрослый, 2-музыкальный): ", &(thtr->p_type));

    if (thtr->p_type == 0)
    {
        input_number("Введите рекомендованный возраст посещения ", &(thtr->property.child.age), 0, CHILD_AGE);
        input_bool("Введите тип детского спектакля (0-сказка, 1-пьеса): ", &(thtr->property.child.type));
    }
    else if (thtr->p_type == 1)
    {
        input_type("Введите тип взрослого спектакля (0-пьеса, 1-драма, 2-комедия): ", &(thtr->property.adult.type));
    }
    else
    {
        input_string("Введите фамилию композитора ", thtr->property.musical.composer, LEN_NAME + 1);
        input_string("Введите название страны ", thtr->property.musical.country, LEN_NAME + 1);
        input_number("Введите минимальный возраст посещения ", &(thtr->property.musical.age), 1, 100);
        input_dur("Введите время продолжительности спектакля ", &(thtr->property.musical.duration), 1.0, 10.0);
    }
}

// Загрузка поля таблицы из файла
struct Theatre *input_theatre_file(FILE *f)
{
    int rc = 0;

    struct Theatre *thtr = (struct Theatre*)malloc(sizeof(struct Theatre));

    if (thtr == NULL)
        return NULL;

    rc += fread_line(f, thtr->t_name, LEN_NAME + 1) != 0;
    rc += fread_line(f, thtr->p_name, LEN_NAME + 1) != 0;
    rc += fread_line(f, thtr->d_name, LEN_NAME + 1) != 0;
    rc += fscanf(f, "%d\n", &thtr->low_price) != 1;
    rc += fscanf(f, "%d\n", &thtr->top_price) != 1;
    rc += fscanf(f, "%d\n", &thtr->p_type) != 1;
    
    if (rc)
        return NULL;

    if (thtr->p_type == 0)
    {
        rc += fscanf(f, "%d\n", &thtr->property.child.age) != 1;
        rc += fscanf(f, "%d\n", &thtr->property.child.type) != 1;
    }
    else if (thtr->p_type == 1)
    {
        rc += fscanf(f, "%d\n", &thtr->property.adult.type) != 1;
    }
    else if (thtr->p_type == 2)
    {
        rc += fread_line(f, thtr->property.musical.composer, LEN_NAME + 1) != 0;
        rc += fread_line(f, thtr->property.musical.country, LEN_NAME + 1) != 0;
        rc += fscanf(f, "%d\n", &(thtr->property.musical.age)) != 1;
        rc += fscanf(f, "%lf\n", &(thtr->property.musical.duration)) != 1;
    }
    else
        return NULL;

    if (rc)
        return NULL;

    return thtr;
}

void output_theatre_console(struct Theatre thtr)
{
    printf("%-20s %-20s %-15s %-5d- %-7d ", thtr.t_name, thtr.p_name, thtr.d_name, thtr.low_price, thtr.top_price);

    if (thtr.p_type == 0)
        printf("%-15s  ", "детский");
    else if(thtr.p_type == 1)
        printf("%-15s  ", "взрослый");
    else
        printf("%-15s  ", "музыкальный");

    if (thtr.p_type == 0)
    {
        printf("%7d  ", thtr.property.child.age);
        if (thtr.property.child.type)
            printf("%16s", "пьеса");
        else
            printf("%18s", "сказка");
    }
    else if(thtr.p_type == 1)
    {
        printf("%11s  %12s  ", "", "");
        if (thtr.property.adult.type == 0)
            printf("%-10s  ", "пьеса");
        else if (thtr.property.adult.type == 1)
            printf("%-10s  ", "драма");
        else
            printf("%-10s  ", "комедия");
    }
    else
    {
        printf("%10s  %10s  %10s  ", "", "", "");
        printf("%-20s ", thtr.property.musical.composer);
        printf("%-8s  ", thtr.property.musical.country);
        printf("%-7d ", thtr.property.musical.age);
        printf("%-8.1lf ", thtr.property.musical.duration);
    }
}


// ------------- Table
// Загрузка таблицы из файла
int load_table(FILE *f, struct  TheatreTable *tbl)
{
    int size, rc = 0;
    struct Theatre *temp;

    if (!f)
        return -1;

    clear_table(tbl);

    if (fscanf(f, "%d\n\n", &size) != 1)
        return -2;

    for (int i = 0; !rc && i < size; i++)
    {
        fscanf(f, "\n");
        if ((temp = input_theatre_file(f)) != NULL)
            add_to_table(tbl, temp);
        else
            rc = -3;
    }
    fclose(f);

    return rc;
}


void output_thTable_console(struct  TheatreTable *tbl)
{
    struct Theatre *ptr_cur = tbl->ptr_first;
    printf("\nТаблица:\n");

    if (!tbl->size)
        puts("Таблица пустая!");
    else
    {
        printf("      Театр                Спектакль            Режиссёр        Диапазон цены  Тип спектакля  Рекоменд. Тип дет-го  Тип взр-го  Фамилия композитора  Название  Мин.    Продолжительность\n");
        printf("                                                                                              возраст   спектакля   спекталя                         страны   возраст \n");
        for (int i = 0; i < tbl->size; i++)
        {
            printf("%-5d ", i + 1);
            output_theatre_console(*ptr_cur);
            printf("\n");
            ptr_cur++;
        }
    }
}


int add_to_table(struct  TheatreTable *tbl, const struct Theatre *stud)
{

    if (tbl->size >= tbl->size_max)
    {
        struct Theatre *ptr_free = tbl->ptr_first;
        struct Theatre *ptr_tmp = tbl->ptr_first;

        tbl->size_max += MALLOC_STEP;

        struct Theatre *ptr_new = (struct Theatre*) malloc(tbl->size_max * sizeof(struct Theatre));

        if (!ptr_new)
            return -1;

        tbl->ptr_first = ptr_new;

        for (int i = 0; i < tbl->size; i++)
        {
            *ptr_new = *ptr_tmp;
            ptr_tmp++;
            ptr_new++;
        }
        free(ptr_free);
    }

    tbl->size++;
    tbl->ptr_first[tbl->size - 1] = *stud;

    return 0;
}


int remove_from_table(struct TheatreTable *tbl, int i)
{
    if (i > 0 && i <= tbl->size)
    {
        tbl->ptr_first[i-1] = tbl->ptr_first[tbl->size-1];
        tbl->size--;
        return 0;
    }
    else
        return -1;
}


void clear_table(struct TheatreTable *tbl)
{
    tbl->size = 0;
    tbl->size_max = 0;

    if (tbl->ptr_first)
    {
        free(tbl->ptr_first);
        tbl->ptr_first = NULL;
    }
}

void save_theatre_table(const char *file_name, struct TheatreTable *tbl)
{
    struct Theatre *pa = tbl->ptr_first;

    FILE *f_out = fopen(file_name, "w");

    fprintf(f_out, "%d\n", tbl->size);

    for (int i = 0; i < tbl->size; i++)
    {
        fprintf(f_out, "\n%s\n%s\n%s\n%d\n%d\n%d\n", pa->t_name, pa->p_name, pa->d_name, pa->low_price, pa->top_price, pa->p_type);

        switch (pa->p_type)
        {
            case 0:
                fprintf(f_out, "%d\n%d\n", pa->property.child.age, pa->property.child.type);
                break;
            case 1:
                fprintf(f_out, "%d\n", pa->property.adult.type);
                break;
            case 2:
                fprintf(f_out, "%s\n%s\n%d\n%lf\n", pa->property.musical.composer, pa->property.musical.country,
                                                    pa->property.musical.age, pa->property.musical.duration);
                break;
        }
        pa++;
    }

    fclose(f_out);
}

int cmp_low_price(const void *a, const void *b)
{
    return ((struct Theatre*) a)->low_price - ((struct Theatre*) b)->low_price;
}

void sort_theatre_table(struct TheatreTable *tbl)
{
    qsort(tbl->ptr_first, tbl->size, sizeof(struct Theatre), cmp_low_price);
}


// Инициализация таблицы ключей
int create_key_table(struct TheatreTable* arr_thtr, struct KeyTable* arr_keys)
{
    struct Theatre *ptr_s;
    struct Key *ptr_key;

    clear_key_table(arr_keys);

    arr_keys->n = arr_thtr->size;

    arr_keys->ptr_first = (struct Key*) malloc(sizeof(struct Key) * arr_keys->n);

    if (arr_keys->ptr_first == NULL)
        return -1;
    ptr_s = arr_thtr->ptr_first;
    ptr_key = arr_keys->ptr_first;
    for (int i = 0; i < arr_keys->n; i++)
    {
        ptr_key->id = i;
        ptr_key->key = ptr_s->low_price;
        ptr_key++;
        ptr_s++;
    }

    return 0;
}

void clear_key_table(struct KeyTable* arr_keys)
{
    if (arr_keys->ptr_first != NULL)
    {
        free(arr_keys->ptr_first);
        arr_keys->ptr_first = NULL;
    }
    arr_keys->n = 0;
}

void print_key_table(const struct KeyTable* arr_keys)
{
    printf("\nТаблица ключей:\n");

    if (arr_keys->n <= 0)
        printf("Таблица ключей пуста.\n");
    else
    {
        struct Key* ptr_key = arr_keys->ptr_first;

        printf("Индекс  Ключ\n");
        for (int i = 0; i < arr_keys->n; i++)
        {
            printf("%-7d %-7d\n", ptr_key->id + 1, ptr_key->key);

            ptr_key++;
        }
    }

}

int check_keyTbl(const struct TheatreTable* arr_thtr, const struct KeyTable* arr_keys)
{
    struct Key* ptr_key = arr_keys->ptr_first;

    for (int i = 0; i < arr_thtr->size; i++, ptr_key++)
        if (arr_thtr->ptr_first[ptr_key->id].low_price != ptr_key->key)
            return -1;

    return 0;
}

// Печать по ключу
int print_theatre_table_by_key(const struct TheatreTable* arr_thtr, const struct KeyTable* arr_keys)
{
    struct Key* ptr_key = arr_keys->ptr_first;

    if (arr_keys->n != arr_thtr->size)
    {
        printf("ОШИБКА!\nРазмеры таблиц отключаются. Попробуйте создать таблицу ключей заново.\n");
        return -1;
    }

    printf("\nТаблица через ключи:\n");

    if (arr_thtr->size == 0)
                printf("ОШИБКА:\nТаблица пустая!.\n");
    else
    {
        printf("      Театр                Спектакль            Режиссёр        Диапазон цены  Тип спектакля  Рекоменд. Тип дет-го  Тип взр-го  Фамилия композитора  Название  Мин.    Продолжительность\n");
        printf("                                                                                              возраст   спектакля   спекталя                         страны   возраст \n");

        for (int i = 0; i < arr_keys->n; i++)
        {
            if (ptr_key->id < 0 || ptr_key->id > (arr_thtr->size - 1))
                return -2;

            printf("%5d ", i + 1);
            output_theatre_console(arr_thtr->ptr_first[ptr_key->id]);
            printf("\n");

            ptr_key++;
            }
    }

    return 0;
}

int cmp_key(const void *key1, const void  *key2)
{
    return ((struct Key*) key1)->key - ((struct Key*) key2)->key;
}

// Сортировка таблицы
void sort_key_table(struct KeyTable *arr_keys)
{
    qsort(arr_keys->ptr_first, arr_keys->n, sizeof(struct Key), cmp_key);
}

void search(struct TheatreTable *tbl)
{
    int count = 0;
    int find_age;
    double dur;

    struct Theatre *ptr = tbl->ptr_first;
    printf("Поиск музыкального спектакля для детей.\n");
    input_number("*Введите возраст ребёнка ", &find_age, 0, CHILD_AGE);
    input_dur("*Введите максимальную желаемую продожлительность спектакля ", &dur, 1.0, 10.0);
    printf("\n");
    for (int i = 0; i < tbl->size; i++)
    {
        if (ptr->p_type == 2 && ptr->property.musical.age >= find_age && ptr->property.musical.duration < dur)
        {
            count++;
            printf("[ Театр %d ]\n", (i + 1));
            output_theatre_console(*ptr);
            printf("--------------------------------------------\n");
        }
        ptr++;
    }

    if (count == 0)
        printf("  Ничего не найдено.\n");

}
