#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc_strings.h"

#define OK 0
#define INPUT_ERROR -1
#define ALLOC_ERROR -2

typedef struct hash_node
{
    char *value;
    struct hash_node *next_elem;
} hash_node_t;

typedef struct
{
    hash_node_t *table_ptr;
    size_t size;
} hash_table_t;

typedef size_t (*hash_func)(char *, size_t);

int insert_to_hash_table(hash_table_t *table, char *word, hash_func hash, size_t *cmps);
hash_table_t *create_hash_table(FILE *f, size_t size, hash_func hash);
hash_node_t *search_in_hash_table(hash_table_t *table, char *word, hash_func hash);
void print_hash_table(hash_table_t *table);
void free_table(hash_table_t *table);
size_t hash_table_count(hash_table_t *table);

size_t hash_by_mod(char *word, size_t m);
size_t hash_by_ring_polynom(char *word, size_t m);

#endif