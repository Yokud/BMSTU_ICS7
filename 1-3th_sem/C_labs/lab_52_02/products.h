#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "files.h"
#include <stdint.h>
#include <unistd.h>

#define TRUNC_ERROR -1
#define SIZE_ERROR -2
#define INPUT_ERROR -3
#define READ_ERROR -4
#define PUT_ERROR -5
#define NO_PRODS -6

#define NAME_LEN_MAX 30
#define MANUFACTURER_LEN_MAX 15

typedef struct
{
    char name[NAME_LEN_MAX + 1];
    char manufacturer[MANUFACTURER_LEN_MAX + 1];
    uint32_t price;
    uint32_t count;
} product;

void print_prod(product prod);
int get_product_by_pos(FILE *f, product *prod, size_t pos);
int put_product_by_pos(FILE *f, product prod, size_t pos);
int print_prods_by_substr(FILE *f, char *substr);
int has_name_substr(char name[NAME_LEN_MAX + 1], char *substr);
int sort_products(FILE *f);
int swap_products(FILE *f, product prod1, size_t prod1_pos, product prod2, size_t prod2_pos);
int add_product(FILE *f);
int enter_prod(product *prod);
void insert_new_prod(FILE *f, size_t prodc, product new_prod, size_t pos);
void write_result(FILE *f, FILE *result);
int print_prods_from_bin_file(FILE *f);

#endif