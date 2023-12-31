#include <stdio.h>
#include <stdlib.h>
#define NMAX 100


size_t input(long a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("(Среднее арифметическое)Введите %zu-й элемент массива: ", i + 1);
        if (scanf("%ld", &a[i]) != 1)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

size_t output(long a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%ld ", a[i]);
    
    printf("\n");

    return EXIT_SUCCESS;
}

double avg_of_array(long a[], size_t n)
{
    double sum = 0;

    for (size_t i = 0; i < n; i++)
        sum += a[i];

    return sum / n;
}

int main(void)
{
    size_t n;
    long a[NMAX];

    printf("(Среднее арифметическое)Введите длину массива: ");
    if (scanf("%zu", &n) != 1 || n > NMAX || n == 0)
    {
        printf("Ошибка ввода длины массива!\n");
        return EXIT_FAILURE;
    }

    if (input(a, n) == EXIT_FAILURE)
    {
        printf("Ошибка ввода элементов массива!\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("(Среднее арифметическое)Исходный массив: ");
        output(a, n);

        printf("Среднее арифметическое элементов массива: %lf\n", avg_of_array(a, n));
        
        return EXIT_SUCCESS;
    }
}
