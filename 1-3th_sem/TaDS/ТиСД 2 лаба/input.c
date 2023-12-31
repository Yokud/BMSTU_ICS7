#include "input.h"


void input_bool(char *msg, int *num)
{
    *num = -7;
    printf("%s", msg);
    while (scanf("%d", num) == 0 || !(*num == 0 || *num == 1))
    {
        printf("ОШИБКА. Неправильный ввод. Попробуйте ещё раз: ");
        fflush(stdin);
    }
}

void input_type (char *msg, int *num)
{
    *num = -7;
    printf("%s", msg);

    while (scanf("%d", num) == 0 || !(*num == 0 || *num == 1 || *num == 2))
    {
        printf("ОШИБКА. Неправильный ввод. Попробуйте ещё раз: ");
        fflush(stdin);
    }
}

void input_number(char *msg, int *num, int beg, int end)
{
    *num = -8;
    printf("%s(диапазон [%d; %d]): ", msg, beg, end);
    while (scanf("%d", num) == 0 || !(*num <= end && *num >= beg))
    {
        printf("ОШИБКА. Неправильный ввод. Попробуйте ещё раз: ");
        fflush(stdin);
    }
}

// Ввод продолжительности
void input_dur (char *msg, double *num, double beg, double end)
{
    printf("%s(диапазон [%.1lf; %.1lf]): ", msg, beg, end);
    while (scanf("%lf", num) == 0 || !(*num <= end && *num >= beg))
    {
        printf("ОШИБКА. Неправильный ввод. Попробуйте ещё раз: ");
        fflush(stdin);
    }
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

// Чтение строки из файла
int fread_line(FILE *f, char s[], size_t n)
{
    int ch;
    size_t i = 0;
    while ((ch = fgetc(f)) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
        else
            return -1;

    s[i] = '\0';

    if (!i)
        return -1;

    return 0;
}