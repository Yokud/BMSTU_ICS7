#include "sort.h"


// Сравнение времени сортировок
void measure_sorting_time(void)
{
    char str[FILE_NAME_LEN];
    struct TheatreTable tmp_table = {NULL, 0, 0};
    struct KeyTable tmp_key_table = {NULL, 0};
    unsigned long long tm, tms;

    input_string("Введите имя файла:\n", str, FILE_NAME_LEN + 1);

    FILE *in = fopen(str, "r");

    if (load_table(in, &tmp_table) == 0)
        printf("\nЗагружено\n");
    else
    {
        printf("\nОшибка загрузки!\n");
        return;
    }
    printf("\n                   Таблица           Ключи\n\n");

    printf("QSORT   :");
    //qsort table
    tms = 0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        tm = tick();
        sort_theatre_table(&tmp_table);
        tm = tick() - tm;
        tms += tm;
        in = fopen(str, "r");
        load_table(in, &tmp_table);
        fclose(in);
    }
    printf("%15lld", tms/ITERATIONS);

    //qsort key table
    tms = 0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        create_key_table(&tmp_table, &tmp_key_table);
        tm = tick();
        sort_key_table(&tmp_key_table);
        tm = tick() - tm;
        tms += tm;
    }
    printf("%15lld", tms/ITERATIONS);

    printf("\nMYSORT  :");
    tms = 0;
    // mysort table
    for (int i = 0; i < ITERATIONS; i++)
    {
        tm = tick();
        mysort_thtr(tmp_table.ptr_first, tmp_table.size);
        tm = tick() - tm;
        tms += tm;
        in = fopen(str, "r");
        load_table(in, &tmp_table);
        fclose(in);
    }
    printf("%15lld", tms/ITERATIONS);

    // mysort key table
    tms = 0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        create_key_table(&tmp_table, &tmp_key_table);
        tm = tick();
        mysort_keys(tmp_key_table.ptr_first, tmp_key_table.n);
        tm = tick() - tm;
        tms += tm;
    }

    printf("%15lld\n", tms/ITERATIONS);

    printf("\nРазмер  : %14lld Б", sizeof(struct Theatre) * tmp_table.size);
    printf("%13lld Б\n", sizeof(struct Key) * tmp_key_table.n);
    fclose(in);
}


void swap_theatres(struct Theatre *a, struct Theatre *b)
{
    struct Theatre tmp = *a;
    *a = *b;
    *b = tmp;
}


void mysort_thtr(struct Theatre *base, int nitems)
{
    struct Theatre *pb = (struct Theatre *)base;
    struct Theatre *pe = pb + nitems;

    for (int i = 0; i < nitems; i++)
    {
        for (int j = 0; j < (pe - pb) - 1; j++)
            if (cmp_low_price((void*)(pb + j), (void*)(pb + j+1)) >= 0)
            {
                swap_theatres((pb + j), (pb + j+1));
            }
        pe--;
    }
}


void swap_keys(struct Key *a, struct Key *b)
{
    struct Key tmp = *a;
    *a = *b;
    *b = tmp;
}

void mysort_keys(struct Key *base, size_t nitems)
{
    struct Key *pb = (struct Key *)base;
    struct Key *pe = pb + nitems;

    for (size_t i = 0; i < nitems; i++)
    {
        for (int j = 0; j < (pe - pb) - 1; j++)
            if (cmp_key((void*)(pb + j), (void*)(pb + j+1)) > 0)
            {
                swap_keys((pb + j), (pb + j+1));
            }
        pe--;
    }
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}