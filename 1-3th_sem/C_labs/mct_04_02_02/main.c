#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define OK 0
#define ARGS_ERROR -1
#define FILE_ERROR -2
#define INPUT_ERROR -3
#define LIST_ERROR -4

typedef struct list_node
{
    double number;

    struct list_node *next;
    struct list_node *prev;
} list_t;

list_t *push(list_t *head, double data)
{
    list_t *cur = head;

    if (!head)
    {
        cur = malloc(sizeof(list_t));

        if (cur)
        {
            cur->number = data;
            cur->next = NULL;
            cur->prev = NULL;
        }

        return cur;
    }
    else
    {
        for (; cur->next; cur = cur->next)
            ;
        
        cur->next = malloc(sizeof(list_t));

        if (cur->next)
        {
            cur->next->prev = cur;
            cur = cur->next;
            cur->number = data;
            cur->next = NULL;
        }
    }
    
    return head;
}

void print_list(list_t *head)
{
    if (!head)
        return;

    for (; head; head = head->next)
        printf("%lf ", head->number);
    putchar('\n');
}

void free_list(list_t *head)
{
    list_t *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

size_t list_len(list_t *head)
{
    size_t len = 0;

    if (!head)
        return 0;
    else if (head->next == head)
        return 1;

    for (list_t *cur = head; cur && cur->next != head; cur = cur->next)
        len++;
    
    return len;
}

double get_avg(list_t *head)
{
    size_t count = list_len(head);
    list_t *cur = head;

    double sum = 0.0;

    for (size_t i = 0; i < count; i++)
    {
        sum += cur->number;
        cur = cur->next;
    }

    return sum / count;
}

list_t *insert_to_mid(list_t *head)
{
    size_t count = list_len(head) / 2;
    list_t *cur = head;

    double avg = get_avg(head);

    for (size_t i = 0; i < count; i++)
        cur = cur->next;

    cur->next = cur->next->next;
    cur->next->prev = cur;
    cur->next->number = avg;

    return head;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return ARGS_ERROR;

    int rc = OK;
    long prev_list_len = 0;
    double val;
    list_t *list = NULL;
    FILE *f;

    setbuf(stdout, NULL);

    if (!(f = fopen(argv[1], "r")))
        return FILE_ERROR;

    while (!feof(f) && !rc)
    {
        if ((fscanf(f, "%lf", &val)) != 1)
            rc = INPUT_ERROR;
        else
        {
            list = push(list, val);

            if (prev_list_len >= list_len(list))
                rc = LIST_ERROR;
            else
                prev_list_len = list_len(list);
        }
    }

    print_list(list);

    list = insert_to_mid(list);

    print_list(list);

    free_list(list);
    fclose(f);

    return rc;
}