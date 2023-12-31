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
    long number;

    struct list_node *next;
    struct list_node *prev;
} list_t;

list_t *push(list_t *head, long data)
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
        printf("%ld ", head->number);
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

    for (list_t *cur = head; cur; cur = cur->next)
        len++;
    
    return len;
}

long dist_to_ten(long num)
{
    if (num == LONG_MIN)
        return 2;

    num = labs(num);
    long mod = num % 10;

    if (mod < 5)
        return mod;
    return 10 - mod;
}

list_t *sort(list_t *head)
{
    list_t *current, *before, *after;
    size_t count;

    count = list_len(head);

    for(size_t i = 0; i < count; i++)
    {
        current = head;
        printf("List: ");
        print_list(head);
        for(size_t j = 0; j < count - 1 - i; j++)
        {
            if(dist_to_ten(current->number) < dist_to_ten(current->next->number))
            {
                before = current->prev;
                after = current->next;
                if(before)
                    before->next = after;
                
                current->next = after->next;
                current->prev = after;
                after->next = current;
                after->prev = before;
            }

            current = current->next;
        }
    }

    return head;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return ARGS_ERROR;

    int rc = OK;
    long val, prev_list_len = 0;
    list_t *list = NULL;
    FILE *f;

    if (!(f = fopen(argv[1], "r")))
        return FILE_ERROR;

    while (!feof(f) && !rc)
    {
        if ((fscanf(f, "%ld", &val)) != 1)
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

    list = sort(list);

    print_list(list);

    free_list(list);
    fclose(f);

    return rc;
}