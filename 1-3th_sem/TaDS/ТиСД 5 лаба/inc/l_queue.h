#ifndef L_QUEUE_H
#define L_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define QUEUE_OVERFLOW 1
#define QUEUE_UNDERFLOW 2
#define BAD_ALLOC 3

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

node_t *create_node(size_t elem_size);

void free_node(node_t *node);


typedef struct
{
    node_t *head, *tail;
    size_t queue_size, elem_size;
} l_queue;


l_queue *l_create(size_t elem_size);

void l_destroy(l_queue *queue);

int l_push(void *queue, void *src);

int l_pop(void *queue, void *dst);

bool l_is_empty(void *queue);

bool l_is_full(void *queue);


node_t *push_addr_list(node_t *head, void *addr);

void free_addr_list(node_t *head);

void print_addr_list(void);

#endif
