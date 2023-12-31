#include <stdio.h>
#include <stdlib.h>
#define NMAX 100


size_t input(long a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
    	printf("(Сортировка массива)Введите %zu-й элемент массива: ", i + 1);
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

size_t bubble_sort(long a[], size_t n)
{
    long r;

    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
            {
                r = a[j + 1];
                a[j + 1] = a[j];
                a[j] = r;
            }

    return EXIT_SUCCESS;
}

int main(void)
{
    size_t n;
    long a[NMAX];

    printf("(Сортировка массива)Введите длину массива: ");
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
        printf("(Сортировка массива)Исходный массив: ");
        output(a, n);

        bubble_sort(a, n);

        printf("Отсортированный массив: ");
        output(a, n);
        
        return EXIT_SUCCESS;
    }
}
