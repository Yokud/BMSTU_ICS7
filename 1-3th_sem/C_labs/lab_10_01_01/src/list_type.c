#include "list_type.h"


node_t *push_back(node_t *head, void *data)
{
    node_t *cur = head;

    if (!head)
    {
        cur = malloc(sizeof(node_t));

        if (cur)
        {
            cur->data = data;
            cur->next = NULL;
        }

        return cur;
    }
    else
    {
        for (; cur->next; cur = cur->next);
        
        cur->next = malloc(sizeof(node_t));

        if (cur->next)
        {
            cur = cur->next;
            cur->data = data;
            cur->next = NULL;
        }
    }
    
    return head;
}

void print_list(node_t *head, void (*print_data)(void *data))
{
    if (!head)
        return;

    for (; head; head = head->next)
        print_data(head->data);
}

void free_list(node_t *head)
{
    node_t *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

int lists_cmp(node_t *head_a, node_t *head_b, int (*cmp)(void *, void *))
{
    if (!head_a && !head_b)
        return 0;

    if (!head_a || !head_b)
        return 1;

    node_t *cur_a, *cur_b;

    for (cur_a = head_a, cur_b = head_b; cur_a && cur_b; cur_a = cur_a->next, cur_b = cur_b->next)
        if (cmp(cur_a->data, cur_b->data))
            return 1;
    
    if (cur_a != cur_b)
        return 1;

    return 0;
}

void *pop_front(node_t **head)
{
    if (!head || !*head)
        return NULL;

    node_t *prev_head = *head;
    void *data = (*head)->data;

    *head = (*head)->next;
    free(prev_head);
    return data;
}

void *pop_back(node_t **head)
{
    if (!head || !*head)
        return NULL;
    
    node_t *cur, *prev = NULL;
    void *data;

    for (cur = *head; cur->next; cur = cur->next)
        prev = cur;
    
    data = cur->data;
    free(cur);
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;
    
    return data;
}

void append(node_t **head_a, node_t **head_b)
{
    if (!head_a || !head_b || !*head_b)
        return;

    if (!*head_a)
    {
        *head_a = *head_b;
        *head_b = NULL;
        return;
    }

    node_t *cur;

    for (cur = *head_a; cur->next; cur = cur->next);
    
    cur->next = *head_b;
    *head_b = NULL;
}

node_t *reverse(node_t *head)
{
    if (!head || !head->next)
        return head;
    
    node_t *new_head = reverse(head->next);

    if (head->next)
        head->next->next = head;
    head->next = NULL;

    return new_head;
}