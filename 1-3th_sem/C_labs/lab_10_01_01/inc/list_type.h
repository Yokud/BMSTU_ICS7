#ifndef LIST_TYPE_H
#define LIST_TYPE_H

#include <stdlib.h>

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

node_t *push_back(node_t *head, void *data);
void print_list(node_t *head, void (*print_data)(void *data));
void free_list(node_t *head);
int lists_cmp(node_t *head_a, node_t *head_b, int (*cmp)(void *, void *));

void *pop_front(node_t **head);
void *pop_back(node_t **head);
void append(node_t **head_a, node_t **head_b);
node_t *reverse(node_t *head); // recursive

#endif