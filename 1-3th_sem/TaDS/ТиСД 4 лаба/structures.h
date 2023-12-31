#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAXVAL 1000
#define ITERATIONS 100

#define OK 0
#define INPUT_ERROR -1
#define STACK_OVERFLOW -2
#define STACK_VOID -3

typedef struct
{
    void *stack[MAXVAL]; // статический массив (Макс. размер - 1000 элементов)
    long ps; // указатель на текущий элемент стека
    long max_size; // максимальный размер стека
} array_stack_t;

int push_array_stack(array_stack_t *stack, void *elem);
int pop_array_stack(array_stack_t *stack);
void print_array_stack(array_stack_t *stack);


typedef struct list_stack
{
    struct list_stack *elem; // Указатель на текущий узел

    struct list_stack *prev; // Указатель на предыдущий узел
} list_stack_t;

typedef struct 
{
    list_stack_t **stack; // вектор свободных областей
    long ps; // указатель на текущий элемент вектора
} trash_can_t;

list_stack_t *push_list_stack(list_stack_t *stack);
list_stack_t *pop_list_stack(list_stack_t *stack, trash_can_t *trash_can);
void print_list_stack(list_stack_t *stack);
void free_list_stack(list_stack_t *stack);


int push_trash_can(trash_can_t *trash_can, struct list_stack *elem_ptr);
void print_trash_can(trash_can_t *trash_can);
void free_trash_can(trash_can_t *trash_can);

void measuring(void);
uint64_t tick(void);

#endif