#include "structures.h"

#define MAX_LIST_LEN 5

int main(void)
{
    int com = -1, l_count = 0;
    void *elem;

    array_stack_t *arr_stack = malloc(sizeof(array_stack_t));
    arr_stack->ps = -1;
    arr_stack->max_size = 5;

    list_stack_t *l_stack = NULL, *prev_list_state = NULL;
    trash_can_t *trash_can = malloc(sizeof(trash_can_t));
    trash_can->stack = NULL;
    trash_can->ps = -1;

    setbuf(stdout, NULL);

    printf("Программа предназначена для работы со стеками в виде массива и списка. Элементами стеков являются адреса памяти. "
            "Элементы стека в виде массива добавляются с клавиатуры. Элементом стека в виде списка является адрес текущего узла списка. "
            "Элементы, удалённые из стека в виде списка, помещаются в вектор свободных областей.\n");

    while (com)
    {
        printf("\nВыберите действие:\n\t"
            "1 - Добавить элемент в стек в виде массива\n\t"
            "2 - Удалить элемент из стека в виде массива\n\t"
            "3 - Вывести стек в виде массива\n\n\t"
            "4 - Добавить элемент в стек в виде списка\n\t"
            "5 - Удалить элемент из стека в виде списка\n\t"
            "6 - Вывести стек в виде списка\n\n\t"
            "7 - Вывести вектор свободных областей\n\t"
            "8 - Сравнить время работы и объём требуемой памяти стеков\n\t"
            "0 - Выход\n\t");
        printf("\nВаше действие: ");

        fflush(stdin);
        if (scanf("%d", &com) != 1)
        {
            printf("Неизвестная команда!\n");
            continue;
        }

        switch (com)
        {
            case 0:
                printf("Завершение работы\n");
                free(arr_stack);
                free_list_stack(l_stack);
                free_trash_can(trash_can);
                break;

            case 1:
                printf("Введите элемент: ");
                if (scanf("%p", &elem) == 1)
                {
                    if (!push_array_stack(arr_stack, elem))
                        printf("Элемент в стек в виде массива успешно добавлен\n");
                }
                else
                    printf("Ошибка ввода элемента\n");
               break;

            case 2:
                if (!pop_array_stack(arr_stack))
                    printf("Элемент из стека в виде массива успешно удалён\n");
                break;
            
            case 3:
                print_array_stack(arr_stack);
                break;

            case 4:
                if (l_count >= MAX_LIST_LEN)
                    printf("Стек в виде списка переполнен\n");
                else if ((l_stack = push_list_stack(l_stack)))
                {
                    printf("Элемент в стек в виде списка успешно добавлен\n");
                    l_count++;
                }
                break;

            case 5:
                if ((l_stack = pop_list_stack(l_stack, trash_can)) != prev_list_state)
                {
                    printf("Элемент из стека в виде списка успешно удалён\n");
                    prev_list_state = l_stack;
                    l_count--;
                }
                break;

            case 6:
                print_list_stack(l_stack);
                break;

            case 7:
                print_trash_can(trash_can);
                break;

            case 8:
                measuring();
                break;
            
            default:
                printf("Неизвестная команда!\n");
                break;
        }
    }

    return 0;
}