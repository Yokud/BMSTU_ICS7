#ifndef A_QUEUE_H
#define A_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_OVERFLOW 1
#define QUEUE_UNDERFLOW 2

typedef struct
{
    size_t head, tail;
    size_t queue_size, elem_size, capacity;
    void *data;
} a_queue;

a_queue *a_create(size_t queue_size, size_t elem_size);

void a_destroy(a_queue *queue);

int a_push(void *queue, void *src);

int a_pop(void *queue, void *dst);

bool a_is_empty(void *queue);

bool a_is_full(void *queue);

#endif
