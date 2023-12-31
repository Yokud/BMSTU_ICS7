#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    setbuf(stdout, NULL);

    printf("Программа производит операцию сложения двух разреженных матриц и выдаёт на выходе матрицу того же формата."
            "Таже программа позволяет сравнить время выполнения операций и объем памяти при использовании 2-х различных алгоритмов"
            " сложения матриц при различном проценте их заполнения.\nМатрица хранит вещественные числа.\n\n");

    int op, is_exit = 0;
    matrix_t matr_1, matr_2, matr_res;
    double percent;
    
    while (!is_exit)
    {
        printf("\nВыберите действие:\n\t"
            "1 - Ввести с клавиатуры и сложить две разреженные матрицы\n\t"
            "2 - Сгенерировать и сложить две разреженные матрицы\n\t"
            "3 - Считать две разреженные матрицы из файлов и сложить их\n\t"
            "4 - Сравнить время выполнения операций и объем памяти\n\t"
            "0 - Выход\n\t");
        printf("\nВаше действие: ");

        fflush(stdin);
        if (scanf("%d", &op) != 1)
        {
            printf("Неизвестная операция!\n");
            continue;
        }

        switch (op)
        {
            case 0:
                printf("Завершение работы\n");

                // Освобождение памяти
                free_matrix(&matr_1);
                free_matrix(&matr_2);
                free_matrix(&matr_res);

                is_exit = 1;
                break;

            case 1:
                printf("Первая матрица\n");
                if (input_matrix(&matr_1))
                {
                    printf("Ошибка загрузки\n");
                    break;
                }
                
                printf("\nВторая матрица\n");
                if (input_matrix(&matr_2))
                {
                    printf("Ошибка загрузки\n");
                    break;
                }

                printf("\nПервая введённая матрица:");
                output_matrix(&matr_1);
                printf("\n\nВторая введённая матрица:");
                output_matrix(&matr_2);

                matr_res.m = matr_1.m;
                matr_res.n = matr_1.n;
                matr_res.ia = malloc((matr_1.n + 1) * sizeof(int));
                matr_res.values = malloc(matr_1.m * matr_1.n * sizeof(double));
                matr_res.ja = malloc(matr_1.m * matr_1.n * sizeof(double));;
                matr_res.nz_elems = 0;

                if (!add_matrixes(&matr_1, &matr_2, &matr_res))
                {
                    printf("\n\nРезультат:\n");
                    matr_res.ja = realloc(matr_res.ja, matr_res.nz_elems * sizeof(int));
                    matr_res.values = realloc(matr_res.values, matr_res.nz_elems * sizeof(double));
                    output_matrix(&matr_res);
                }
                else
                    printf("Не удалось сложить матрицы\n");
                    
                break;

            case 2:
                printf("Введите размер матриц в формате \"n m\": ");
                if (scanf("%d %d", &matr_1.n, &matr_1.m) != 2 || matr_1.n <= 0 || matr_1.m <= 0)
                {
                    printf("Ошибка загрузки\n");
                    break;
                }

                matr_2.n = matr_1.n;
                matr_2.m = matr_1.m;
                
                printf("Введите процент заполненности матриц (0, 1]: ");
                if (scanf("%lf", &percent) != 1 || percent < 0 || percent > 1 || is_zero(percent))
                {
                    printf("Ошибка загрузки\n");
                    break;
                }

                generate_matrix(&matr_1, percent);
                generate_matrix(&matr_2, percent);

                printf("\nПервая сгенерированная матрица:");
                output_matrix(&matr_1);
                printf("\n\nВторая сгенерированная матрица:");
                output_matrix(&matr_2);

                matr_res.m = matr_1.m;
                matr_res.n = matr_1.n;
                matr_res.ia = malloc((matr_1.n + 1) * sizeof(int));
                matr_res.values = malloc(matr_1.m * matr_1.n * sizeof(double));
                matr_res.ja = malloc(matr_1.m * matr_1.n * sizeof(double));;
                matr_res.nz_elems = 0;

                if (!add_matrixes(&matr_1, &matr_2, &matr_res))
                {
                    printf("Результат:\n");
                    matr_res.ja = realloc(matr_res.ja, matr_res.nz_elems * sizeof(int));
                    matr_res.values = realloc(matr_res.values, matr_res.nz_elems * sizeof(double));
                    output_matrix(&matr_res);
                }
                else
                    printf("Не удалось сложить матрицы\n");
                break;

            case 3:
                printf("Первая матрица:\n");
                if (fread_matrix(&matr_1))
                {
                    printf("Ошибка загрузки\n");
                    break;
                }

                printf("\nВторая матрица:\n");
                if (fread_matrix(&matr_2))
                {
                    printf("Ошибка загрузки\n");
                    break;
                }

                printf("\nПервая введённая матрица:");
                output_matrix(&matr_1);
                printf("\n\nВторая введённая матрица:");
                output_matrix(&matr_2);

                matr_res.m = matr_1.m;
                matr_res.n = matr_1.n;
                matr_res.ia = malloc((matr_1.n + 1) * sizeof(int));
                matr_res.values = malloc(matr_1.m * matr_1.n * sizeof(double));
                matr_res.ja = malloc(matr_1.m * matr_1.n * sizeof(double));;
                matr_res.nz_elems = 0;

                if (!add_matrixes(&matr_1, &matr_2, &matr_res))
                {
                    printf("Результат:\n");
                    matr_res.ja = realloc(matr_res.ja, matr_res.nz_elems * sizeof(int));
                    matr_res.values = realloc(matr_res.values, matr_res.nz_elems * sizeof(double));
                    output_matrix(&matr_res);
                }
                else
                    printf("Не удалось сложить матрицы\n");
                    
                break;

            case 4:
                measuring_algorithms_time();
                break;
            
            default:
                printf("Неизвестная операция!\n");
                break;
        }
    }

    return OK;
}