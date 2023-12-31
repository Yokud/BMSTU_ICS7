#include "utils.h"

int max_j(int *j, int begin, int end)
{
    int max = j[begin];

    for (int i = begin; i < end; i++)
        if (j[i] > max)
            max = j[i];
    
    return max;
}

int is_zero(double d)
{
    double eps = 1e-6;

    return fabs(d) < eps;
}

void swap(char *a, char *b, size_t size)
{
    for (; size > 0; size--)
    {
        char temp = *a;
        *a++ = *b;
        *b++ = temp;
    }
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

void input_string(char *msg, char *str, int max_len)
{
    char c;
    int ended = 0;

    fflush(stdin);
    while (1)
    {
        printf("%s", msg);
        printf("(Максимум %d символов):\n", max_len - 1);

        printf("|");
        for (int i = 0; i < max_len - 3; i++)
            printf("-");
        printf("|\n");

        for (int i = 0; i < max_len; i++)
        {
            if (scanf("%c", &c) == 1)
            {
                if (c != '\n')
                    str[i] = c;
                else
                {
                    str[i] = 0;
                    ended = 1;
                    break;
                }
            }
            else
            {
                str[i] = 0;
                ended = 1;
                break;
            }
        }

        fflush(stdin);
        if (!ended)
            printf("ОШИБКА: Слишком много символов. Попробуйте ещё раз.\n");
        else if (!str[0])
        {
            printf("ОШИБКА: Пустой ввод. Попробуйте ещё раз.\n\n");
            ended = 0;
        }
        else
            return;
    }

}