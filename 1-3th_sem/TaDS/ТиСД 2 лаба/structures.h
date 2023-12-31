#ifndef OPERATIONS_H
#define OPERATIONS_H

#define CHILD_AGE 17
#define LEN_NAME 40
#define MALLOC_STEP 10

#include <stdlib.h>
#include "input.h"

struct Theatre
{
    char t_name[LEN_NAME + 1]; // название театра
    char p_name[LEN_NAME + 1]; // название спекталя
    char d_name[LEN_NAME + 1]; // фамилия режиссёра
    int low_price; // минимальная стоимость билета
    int top_price; // максимальная стоимость билета
    int p_type; // тип спектакля

    union
    {
        // детский
        struct
        {
            int age; // возраст
            int type; // 0 - сказка, 1 - пьеса
        } child;

        // Взрослый
        struct
        {
            int type; // 0 - пьеса, 1 - драма, 2 - комедия
        } adult;

        // Музыкальный
        struct
        {
            char composer[LEN_NAME + 1]; // фамилия композитора
            char country[LEN_NAME + 1]; // название страны
            int age; // минимальный возраст
            double duration; // продолжительность
        } musical;
    } property;
};

void input_theatre(struct Theatre *thtr);
void output_theatre_console(struct Theatre thtr);

struct TheatreTable
{
    struct Theatre *ptr_first;
    int size;
    int size_max;
};

int load_table(FILE *f, struct TheatreTable *tbl);
void save_theatre_table(const char *file_name, struct TheatreTable *tbl);
int add_to_table(struct TheatreTable *tbl, const struct Theatre *thtr);
int remove_from_table(struct TheatreTable *tbl, int i);
void clear_table(struct TheatreTable *tbl);
void output_thTable_console(struct  TheatreTable *tbl);
int cmp_low_price(const void *a, const void *b);
void sort_theatre_table(struct TheatreTable *tbl);


struct Key
{
    int key;
    int id;
};

struct KeyTable
{
    struct Key* ptr_first;
    int n;
};

int create_key_table(struct TheatreTable* thtr_stud, struct KeyTable* arr_keys);
void clear_key_table(struct KeyTable* arr_keys);
void sort_key_table(struct KeyTable* arr_keys);
void print_key_table(const struct KeyTable* arr_keys);
int print_theatre_table_by_key(const struct TheatreTable* arr_thtr, const struct KeyTable* arr_keys);
int cmp_key(const void *key1, const void *key2);
int check_keyTbl(const struct TheatreTable* arr_thtr, const struct KeyTable* arr_keys);

void search(struct TheatreTable *tbl);
#endif
