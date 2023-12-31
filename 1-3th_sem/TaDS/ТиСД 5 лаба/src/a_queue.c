#include "a_queue.h"

a_queue *a_create(size_t queue_size, size_t elem_size)
{
    a_queue *queue = malloc(sizeof(a_queue));
    if (!queue)
        return NULL;

    queue->data = malloc(queue_size * elem_size);
    if (!queue->data)
    {
        free(queue);
        return NULL;
    }

    queue->queue_size = 0;
    queue->elem_size = elem_size;
    queue->capacity = queue_size;

    queue->head = queue->tail = queue_size - 1;

    return queue;
}

void a_destroy(a_queue *queue)
{
    free(queue->data);
    free(queue);
}

int a_push(void *queue, void *src)
{
    a_queue *que = (a_queue *)queue;
    if (a_is_full(que))
        return QUEUE_OVERFLOW;

    size_t byte = que->elem_size * que->tail;
    memcpy((char *)(que->data) + byte, src, que->elem_size);

    if (que->tail)
        que->tail--;
    else
        que->tail = que->capacity - 1;
    que->queue_size++;
    
    return EXIT_SUCCESS;
}

int a_pop(void *queue, void *dst)
{
    a_queue *que = (a_queue *)queue;
    if (a_is_empty(queue))
        return QUEUE_UNDERFLOW;

    size_t byte = que->elem_size * que->head;
    memcpy(dst, (char *)(que->data) + byte, que->elem_size);

    if (que->head)
        que->head--;
    else
        que->head = que->capacity - 1;
    que->queue_size--;

    return EXIT_SUCCESS;
}

bool a_is_empty(void *queue)
{
    return ((a_queue *)queue)->queue_size == 0;
}

bool a_is_full(void *queue)
{
    return ((a_queue *)queue)->queue_size == ((a_queue *)queue)->capacity;
}