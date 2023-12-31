#include "structures.h"


int push_array_stack(array_stack_t *stack, void *elem)
{
    if (stack->ps + 1 < stack->max_size)
        stack->stack[++stack->ps] = elem;
    else
    {
        printf("Стек переполнен\n");
        return STACK_OVERFLOW;
    }
    
    return OK;
}

int pop_array_stack(array_stack_t *stack)
{
    if (stack->ps > -1)
        stack->ps--;
    else
    {
        printf("Стек пуст\n");
        return STACK_VOID;
    }
    
    return OK;
}

auto int *p = malloc(sizeof(int));

void print_array_stack(array_stack_t *stack)
{
    if (stack->ps < 0)
    {
        printf("Стек пуст\n");
        return;
    }
    
    printf("Содержимое стека в виде массива:\n");
    for (long i = 0; i <= stack->ps; i++)
        printf("%p ", (void *) stack->stack[i]);
    printf("\n");
}

list_stack_t *push_list_stack(list_stack_t *stack)
{
    list_stack_t *temp;
    
    if (!stack)
    {
        temp = malloc(sizeof(list_stack_t));

        if (temp)
        {
            temp->elem = temp;
            temp->prev = NULL;
        }
        else
            printf("Ошибка выделения памяти под список\n");
    }
    else
    {
        temp = malloc(sizeof(list_stack_t));

        if (!temp)
            printf("Стек в виде списка переполнен\n");
        else
        {
            temp->prev = stack;
            temp->elem = temp;
        }
    }
    
    return temp;
}

list_stack_t *pop_list_stack(list_stack_t *stack, trash_can_t *trash_can)
{
    list_stack_t *prev = NULL;
    
    if (!stack)
        printf("Стек пуст\n");
    else
    {
        prev = stack->prev;

        push_trash_can(trash_can, stack->elem);
        free(stack);
    }

    return prev;
}

void print_list_stack(list_stack_t *stack)
{
    if (!stack)
    {
        printf("Стек пуст\n");
        return;
    }

    for (list_stack_t *cur = stack; cur; cur = cur->prev)
        printf("%p ", (void *) cur->elem);
    printf("\n");
}

void free_list_stack(list_stack_t *stack)
{
    list_stack_t *prev;

    for (; stack;)
    {
        prev = stack->prev;
        free(stack);
        stack = prev;
    }
}

int push_trash_can(trash_can_t *trash_can, list_stack_t *elem_ptr)
{
    list_stack_t **temp = realloc(trash_can->stack, (trash_can->ps + 2) * sizeof(list_stack_t *));

    if (!temp)
    {
        printf("Ошибка перевыделения памяти под массив освободившихся адресов\n");
        return STACK_OVERFLOW;
    }
    else
    {
        trash_can->stack = temp;
        trash_can->stack[++trash_can->ps] = elem_ptr;
    }

    return OK;
}

void print_trash_can(trash_can_t *trash_can)
{
    if (trash_can->ps < 0)
    {
        printf("Массив освободившихся адресов пуст\n");
        return;
    }

    printf("Содержимое массива освободившихся адресов:\n");
    for (long i = 0; i <= trash_can->ps; i++)
        printf("%p ", (void *) trash_can->stack[i]);
    printf("\n");
}

void free_trash_can(trash_can_t *trash_can)
{
    free(trash_can->stack);
    free(trash_can);
}

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void measuring(void)
{
    array_stack_t *arr_stack = malloc(sizeof(array_stack_t));
    
    list_stack_t *l_stack = NULL;

    trash_can_t *trash_can = malloc(sizeof(trash_can_t));
    trash_can->stack = NULL;
    trash_can->ps = -1;

    int lengths[] = {10, 100, 250, 500, 1000};
    int n = sizeof(lengths) / sizeof(lengths[0]);

    uint64_t sum_time_add, sum_time_del, time_point;

    // Для массива
    printf("\n\t\tДанные для стека в виде массива\n");
    printf("\t Длина Добавление   Удаление Объём(б.)\n");
    for (int i = 0; i < n; i++)
    {
        sum_time_add = 0;
        sum_time_del = 0;
        for (int j = 0; j < ITERATIONS; j++)
        {
            arr_stack->max_size = lengths[i];
            arr_stack->ps = -1;

            time_point = tick();
            for (int k = 0; k < lengths[i]; k++)
                push_array_stack(arr_stack, NULL);
            sum_time_add += tick() - time_point;

            time_point = tick();
            for (int k = 0; k < lengths[i]; k++)
                pop_array_stack(arr_stack);
            sum_time_del += tick() - time_point;
        }

        printf("\t%5d : %8llu | %8llu | %6llu |\n", lengths[i], sum_time_add / ITERATIONS, sum_time_del / ITERATIONS, lengths[i] * sizeof(arr_stack->stack[0]) + sizeof(arr_stack->ps) + sizeof(arr_stack->max_size));
    }
    printf("\n");
    //Для списка
    printf("\n\t\tДанные для стека в виде списка\n");
    printf("\t Длина Добавление   Удаление Объём(б.)\n");
    for (int i = 0; i < n; i++)
    {
        sum_time_add = 0;
        sum_time_del = 0;
        for (int j = 0; j < ITERATIONS; j++)
        {
            time_point = tick();
            for (int k = 0; k < lengths[i]; k++)
                l_stack = push_list_stack(l_stack);
            sum_time_add += tick() - time_point;

            time_point = tick();
            for (int k = 0; k < lengths[i]; k++)
                l_stack = pop_list_stack(l_stack, trash_can);
            sum_time_del += tick() - time_point;

            free(trash_can->stack);
            trash_can->stack = NULL;
            trash_can->ps = -1;
        }
        printf("\t%5d : %8llu | %8llu | %6llu |\n", lengths[i], sum_time_add / ITERATIONS, sum_time_del / ITERATIONS, lengths[i] * sizeof(list_stack_t));
    }

    free_trash_can(trash_can);
    free_list_stack(l_stack);
    free(arr_stack);
}