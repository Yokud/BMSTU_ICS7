#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 0

#define N 16
#define M 16
#define NUMBERS 10

/*!
    \fn void mtr_input(long a[N][M], size_t *n, size_t *m)
    \brief Функция ввода матрицы
    \param[in] a - матрица
    \param[out] *n - указатель на число элементов в строке матрицы
    \param[out] *m - указатель на число элементов в столбце матрицы

    Функция получает размер и элементы матрицы
*/
void mtr_input(long a[N][M], size_t *n, size_t *m)
{
    assert(scanf("%zu%zu", n, m) == 2);
    assert((*n > 0 && *n <= N) && (*m > 0 && *m <= M));
    
    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
            assert(scanf("%ld", &a[i][j]) == 1);
}

/*!
    \fn long frq_of_digit(long a[N][M], size_t n, size_t m, long src_digit)
    \brief Функция получения частоты встречаемости цифры
    \param[in] a - матрица
    \param[in] n - число элементов в строке матрицы
    \param[in] m - число элементов в столбце матрицы
    \param[in] src_digit - цифра
    \return frq - количество встреч

    Функция вычисляет частоту встречаемости цифры среди элементов матрицы
*/
long frq_of_digit(long a[N][M], size_t n, size_t m, long src_digit)
{
    long frq = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            long el = labs(a[i][j]);
            while (el)
            {
                if (el % 10 == src_digit)
                    frq += 1;
                el /= 10;
            }
        }

    return frq;
}

/*!
    \fn long max_frq_digit(long a[N][M], size_t n, size_t m)
    \brief Функция получения цифры с максимальной частотой встречаемости
    \param[in] a - матрица
    \param[in] n - число элементов в строке матрицы
    \param[in] m - число элементов в столбце матрицы
    \return digit - цифра с максимальной частотой

    Функция находит цифру с максимальной частотой встречаемости
*/
long max_frq_digit(long a[N][M], size_t n, size_t m)
{
    long digit = 0;
    long max_frq = 0;

    for (size_t i = 0; i < NUMBERS; i++)
    {
        long frq = frq_of_digit(a, n, m, i);
        if (frq > max_frq)
        {
            max_frq = frq;
            digit = i;
        }
    }

    return digit;
}

/*!
    \fn void output_max_frq_digit(long a[N][M], size_t n, size_t m)
    \brief Функция вывода результата
    \param[in] a - матрица
    \param[in] n - число элементов в строке матрицы
    \param[in] m - число элементов в столбце матрицы

    Функция выводит цифру с максимальной частотой встречаемости
*/
void output_max_frq_digit(long a[N][M], size_t n, size_t m)
{
    long result = max_frq_digit(a, n, m);
    if (result >= 0)
        printf("%ld", result);
}

int main(void)
{
    size_t n, m;
    long a[N][M];

    mtr_input(a, &n, &m);
    output_max_frq_digit(a, n, m);

    return EXIT_SUCCESS;    
}