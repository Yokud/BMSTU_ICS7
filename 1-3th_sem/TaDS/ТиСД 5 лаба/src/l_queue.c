#include "l_queue.h"

node_t *_log_addr = NULL;

node_t *create_node(size_t elem_size)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;

    node->data = malloc(elem_size);
    if (!node->data)
    {
        free(node);
        return NULL;
    }

    return node;
}

void free_node(node_t *node)
{
    if (node)
        free(node->data);
    free(node);
}


l_queue *l_create(size_t elem_size)
{
    l_queue *queue = malloc(sizeof(l_queue));
    if (!queue)
        return NULL;

    queue->elem_size = elem_size;
    queue->queue_size = 0;

    queue->head = queue->tail = NULL;

    return queue;
}

void l_destroy(l_queue *queue)
{
    node_t *temp;
    while (queue->head)
    {
        temp = queue->head->next;
        free_node(queue->head);
        queue->head = temp;
    }
    free(queue);
    free_addr_list(_log_addr);
    _log_addr = NULL;
}

int l_push(void *queue, void *src)
{
    l_queue *que = (l_queue *)queue;

    node_t *temp = create_node(que->elem_size);
    if (!temp)
        return QUEUE_OVERFLOW;

    temp->next = NULL;
    memcpy(temp->data, src, que->elem_size);

    if (que->head)
        que->tail = que->tail->next = temp; 
    else
        que->head = que->tail = temp;

    que->queue_size++;

    return EXIT_SUCCESS;
}

int l_pop(void *queue, void *dst)
{
    l_queue *que = (l_queue *)queue;   
    if (l_is_empty(que))
        return QUEUE_UNDERFLOW;

    memcpy(dst, que->head->data, que->elem_size);
    _log_addr = push_addr_list(_log_addr, que->head);

    node_t *temp = que->head->next;
    free_node(que->head);
    que->head = temp;

    if (!que->head)
        que->tail = NULL;

    que->queue_size--;

    return EXIT_SUCCESS;
}

bool l_is_empty(void *queue)
{
    return ((l_queue *)queue)->queue_size == 0;
}

bool l_is_full(void *queue)
{
    return 0;
}


node_t *push_addr_list(node_t *head, void *addr)
{
    node_t *temp = malloc(sizeof(node_t));
    if (!temp)
        return head;
    
    temp->data = addr;
    temp->next = head;
    return temp;
}

void free_addr_list(node_t *head)
{
    node_t *temp;

    while (head)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
}

void print_addr_list(void)
{
    node_t *temp = _log_addr;
    while (temp)
    {
        printf("%p\n", (void *) temp);
        temp = temp->next;
    }
}