#include "structures.h"


int input_matrix(matrix_t *matrix)
{
    printf("Введите размер матрицы в формате \"n m\": ");
    while (scanf("%d %d", &(matrix->n), &(matrix->m)) != 2 || matrix->n <= 0 || matrix->m <= 0)
    {
        printf("Ошибка ввода размера матрицы. Попробуйте снова: ");
        fflush(stdin);
    }

    printf("Введите количество ненулевых элементов: ");
    while (scanf("%d", &(matrix->nz_elems)) != 1 || matrix->nz_elems <= 0 || matrix->nz_elems > matrix->n * matrix->m)
    {
        printf("Ошибка ввода количества ненулевых элементов. Попробуйте снова: ");
        fflush(stdin);
    }

    matrix->values = malloc(matrix->nz_elems * sizeof(double));
    matrix->ja = malloc(matrix->nz_elems * sizeof(int));
    matrix->ia = malloc((matrix->n + 1) * sizeof(int));

    if (matrix->values == NULL || matrix->ja == NULL || matrix->ia == NULL)
    {
        free_matrix(matrix);
        printf("Ошибка выделения памяти\n");
        return ALLOC_ERROR;
    }

    double *def_matrix = calloc(matrix->n * matrix->m, sizeof(double));
    int i, j;
    
    for (int k = 0; k < matrix->nz_elems; k++)
    {
        double val;

        printf("\nВведите %d-й ненулевой элемент:\n", k + 1);

        printf("Номер строки и столбца (с нуля) в формате \"i j\": ");
        while (scanf("%d %d", &i, &j) != 2 || i < 0 || i >= matrix->n || j < 0 || j >= matrix->m)
        {
            printf("Введены некорректные индексы. Попробуйте снова: ");
            fflush(stdin);
        }

        printf("Ненулевое значение: ");
        while (scanf("%lf", &val) != 1 || is_zero(val))
        {
            printf("Введён некорректный элемент. Попробуйте снова: ");
            fflush(stdin);
        }

        def_matrix[i * matrix->m + j] = val;
    }

    matrix->ia[0] = 0;
    int k, count;

    k = 0;

    for (i = 0; i < matrix->n; i++)
    {
        count = 0;
        for (j = 0; j < matrix->m; j++)
            if (!is_zero(def_matrix[i * matrix->m + j]))
            {
                matrix->values[k] = def_matrix[i * matrix->m + j];
                matrix->ja[k] = j;
                k++, count++;
            }
        matrix->ia[i + 1] = matrix->ia[i] + count;
    }

    free(def_matrix);

    return OK;
}

int fread_matrix(matrix_t *matrix)
{
    FILE *f;
    char name[FILE_NAME_MAX];

    printf("ПРЕДУПРЕЖДЕНИЕ:\n"
            "Разреженная матрица в разреженном строчном формате должна храниться в файле следующим образом:\n\t"
            "n m - размер матрицы;\n\t"
            "nz_elems - количество ненулевых элементов;\n\t"
            "A[0] A[1] ... A[nz_elems - 1] - ненулевые элементы матрицы;\n\t"
            "JA[0] A[1] ... JA[nz_elems - 1] - номера столбцов ненулевых элементов (индексация начинается с нуля);\n\t"
            "IA[0] IA[1] ... IA[n] - номера элементов массивов A и JA, с которых начинается описание очередной строки;\n"
            "Ответственность за валидность формата данных лежит на пользователе\n\n");

    input_string("Введите имя файла:\n", name, FILE_NAME_MAX);

    f = fopen(name, "r");

    if (f == NULL)
        return INPUT_ERROR;

    if (fscanf(f, "%d %d\n", &matrix->n, &matrix->m) != 2 || matrix->n <= 0 || matrix->m <= 0)
        goto END;

    if (fscanf(f, "%d\n", &(matrix->nz_elems)) != 1 || matrix->nz_elems <= 0 || matrix->nz_elems > matrix->n * matrix->m)
        goto END;

    matrix->values = malloc(matrix->nz_elems * sizeof(double));
    matrix->ja = malloc(matrix->nz_elems * sizeof(int));
    matrix->ia = malloc((matrix->n + 1) * sizeof(int));

    if (matrix->values == NULL || matrix->ja == NULL || matrix->ia == NULL)
    {
        free_matrix(matrix);
        fclose(f);
        printf("Ошибка выделения памяти\n");
        return ALLOC_ERROR;
    }

    for (int i = 0; i < matrix->nz_elems; i++)
        if (fscanf(f, "%lf", &matrix->values[i]) != 1)
            goto END;

    for (int i = 0; i < matrix->nz_elems; i++)
        if (fscanf(f, "%d", &matrix->ja[i]) != 1)
            goto END;

    for (int i = 0; i < matrix->n + 1; i++)
        if (fscanf(f, "%d", &matrix->ia[i]) != 1)
            goto END;

    fclose(f);

    return OK;

    END:
        free_matrix(matrix);
        fclose(f);
        return INPUT_ERROR;
}

void output_matrix(const matrix_t *matrix)
{
    if (matrix->nz_elems == 0)
    {
        printf("Матрица пуста\n");
        return;
    }

    printf("\n A: ");
    for (int i = 0; i < matrix->nz_elems; i++)
        printf("%3.3g ", matrix->values[i]);
    printf("\n");

    printf("JA: ");
    for (int i = 0; i < matrix->nz_elems; i++)
        printf("%3d ", matrix->ja[i]);
    printf("\n");

    printf("IA: ");
    for (int i = 0; i < matrix->n + 1; i++)
        printf("%3d ", matrix->ia[i]);
    printf("\n");

    if (matrix->m > MAX_COLS || matrix->n > MAX_ROWS)
        printf("\nРазреженная матрица слишком велика, чтобы её вывести в привычном виде\n");
    else
    {
        printf("\nМатрица:\n");
        for (int i = 0; i < matrix->n; i++)
        {
            printf("| ");
            for (int j = 0; j < matrix->m; j++)
            {
                int k_res = -1;
                for (int k = matrix->ia[i]; k < matrix->ia[i + 1]; k++)
                    if (matrix->ja[k] == j)
                    {
                        k_res = k;
                        break;
                    }
                
                printf("%3.3g ", k_res != -1 ? matrix->values[k_res] : 0.0);
            }
            printf("|\n");
        }
    }
}

void generate_matrix(matrix_t *matrix, double persent)
{
    matrix->nz_elems = matrix->m * matrix->n * persent;

    matrix->values = malloc(matrix->nz_elems * sizeof(double));
    matrix->ja = malloc(matrix->nz_elems * sizeof(int));
    matrix->ia = malloc((matrix->n + 1) * sizeof(int));

    if (matrix->values == NULL || matrix->ja == NULL || matrix->ia == NULL)
    {
        free_matrix(matrix);
        printf("Ошибка выделения памяти\n");
        return;
    }

    int i, j;
    double *def_matrix = calloc(matrix->n * matrix->m, sizeof(double));

    if (def_matrix == NULL)
    {
        free_matrix(matrix);
        printf("Ошибка выделения памяти\n");
        return;
    }

    for (int el = 0; el < matrix->nz_elems;)
    {
        i = rand() % matrix->n;
        j = rand() % matrix->m;
        if (is_zero(def_matrix[i * matrix->m + j]))
        {
            def_matrix[i * matrix->m + j] = rand() % 100 + 1;
            el++;
        }
    }

    matrix->ia[0] = 0;
    int k, count;

    k = 0;

    for (i = 0; i < matrix->n; i++)
    {
        count = 0;
        for (j = 0; j < matrix->m; j++)
            if (!is_zero(def_matrix[i * matrix->m + j]))
            {
                matrix->values[k] = def_matrix[i * matrix->m + j];
                matrix->ja[k] = j;
                k++, count++;
            }
        matrix->ia[i + 1] = matrix->ia[i] + count;
    }

    free(def_matrix);
}

int add_matrixes(matrix_t *m1, matrix_t *m2, matrix_t *res)
{
    if (m1->m != m2->m || m1->n != m2->n)
    {
        printf("Размеры матриц не совпадают\n");
        return DIM_ERROR;
    }

    for (int i = 0; i < m1->n; i++)
    {
        res->ia[i] = res->nz_elems;
        int k1, k2;

        for (k1 = m1->ia[i], k2 = m2->ia[i]; k1 < m1->ia[i + 1] && k2 < m2->ia[i + 1]; )
        {
            if (m1->ja[k1] == m2->ja[k2])
            {
                double sum = m1->values[k1] + m2->values[k2];
                if (!is_zero(sum))
                {
                    res->values[res->nz_elems] = sum;
                    res->ja[res->nz_elems] = m1->ja[k1];
                    res->nz_elems++;
                }
                k1++, k2++;
            }
            else if (m1->ja[k1] > m2->ja[k2])
            {
                res->values[res->nz_elems] = m2->values[k2];
                res->ja[res->nz_elems] = m2->ja[k2];
                res->nz_elems++, k2++;
            }
            else
            {
                res->values[res->nz_elems] = m1->values[k1];
                res->ja[res->nz_elems] = m1->ja[k1];
                res->nz_elems++, k1++;
            }
        }

        while (k1 < m1->ia[i + 1])
        {
            res->values[res->nz_elems] = m1->values[k1];
            res->ja[res->nz_elems] = m1->ja[k1];
            res->nz_elems++, k1++;
        }

        while (k2 < m2->ia[i + 1])
        {
            res->values[res->nz_elems] = m2->values[k2];
            res->ja[res->nz_elems] = m2->ja[k2];
            res->nz_elems++, k2++;
        }
    }

    res->ia[m1->n] = res->nz_elems;
    
    return OK;
}

void free_matrix(matrix_t *matrix)
{
    free(matrix->values);
    free(matrix->ja);
    free(matrix->ia);

    matrix->values = NULL;
    matrix->ja = NULL;
    matrix->ia = NULL;
}


default_matrix_t *add_matrixes_default(default_matrix_t *m1, default_matrix_t *m2)
{
    default_matrix_t *res = malloc(sizeof(default_matrix_t));

    if (m1->m != m2->m || m1->n != m2->n)
        return NULL;

    res->m = m1->m;
    res->n = m1->n;

    if (create_default_matrix(res))
        return NULL;

    for (int i = 0; i < m1->n; i++)
        for (int j = 0; j < m1->m; j++)
            res->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
    
    return res;
}

int create_default_matrix(default_matrix_t *dm)
{
    if ((dm->matrix = calloc(dm->n, sizeof(double *))) == NULL)
        return ALLOC_ERROR;
    
    for (int i = 0; i < dm->n; i++)
    {
        if ((dm->matrix[i] = calloc(dm->m, sizeof(double))) == NULL)
        {
            free_default_matrix(dm);
            return ALLOC_ERROR;
        }
    }

    return OK;
}

void free_default_matrix(default_matrix_t *matrix)
{
    for (int i = 0; i < matrix->n; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
}

void generate_default_matrix(default_matrix_t *matrix, double persent)
{
    size_t elems = matrix->m * matrix->n * persent;

    //srand(time(NULL));
    for (size_t el = 0; el < elems; el++)
        matrix->matrix[rand() % matrix->n][rand() % matrix->m] = rand() % 100 + 1; // [1, 100]
}

void measuring_algorithms_time(void)
{
    matrix_t matr_1, matr_2, matr_res;
    default_matrix_t def_matr_1, def_matr_2, *def_matr_res;
    double percent;
    uint64_t tm, tms;

    printf("Введите размер матриц в формате \"n m\": ");
    if (scanf("%d %d", &matr_1.n, &matr_1.m) != 2 || matr_1.n <= 0 || matr_1.m <= 0)
    {
        printf("Ошибка загрузки\n");
        return;
    }

    matr_2.n = matr_1.n;
    matr_2.m = matr_1.m;
    def_matr_1.m = matr_1.m;
    def_matr_1.n = matr_1.n;
    def_matr_2.m = matr_1.m;
    def_matr_2.n = matr_1.n;

    matr_res.m = matr_1.m;
    matr_res.n = matr_1.n;
    matr_res.ia = malloc((matr_1.n + 1) * sizeof(int));
                
    printf("Введите процент заполненности матриц (0, 1]: ");
    if (scanf("%lf", &percent) != 1 || percent < 0 || percent > 1 || is_zero(percent))
    {
        printf("Ошибка загрузки\n");
        return;
    }

    create_default_matrix(&def_matr_1);
    create_default_matrix(&def_matr_2);

    printf("\n\t\t\tВремя(в тактах)\t\tРазмер результирующей матрицы\n");

    printf("Разреженная матрица: ");

    tms = 0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        matr_res.values = realloc(matr_res.values, matr_1.m * matr_1.n * sizeof(double));
        matr_res.ja = realloc(matr_res.ja, matr_1.m * matr_1.n * sizeof(double));;
        matr_res.nz_elems = 0;
        generate_matrix(&matr_1, percent);
        generate_matrix(&matr_2, percent);
        tm = tick();
        add_matrixes(&matr_1, &matr_2, &matr_res);
        tm = tick() - tm;
        tms += tm;
    }

    uint64_t matr_res_size = sizeof(matr_res) + (sizeof(int) + sizeof(double)) * matr_res.nz_elems + sizeof(int) * (matr_res.n + 1);
    printf("\t%8lld\t\t%10lldБ\n", tms / ITERATIONS, matr_res_size);
    free_matrix(&matr_res);

    printf("Стандартная матрица: ");

    tms = 0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        generate_default_matrix(&def_matr_1, percent);
        generate_default_matrix(&def_matr_2, percent);
        tm = tick();
        def_matr_res = add_matrixes_default(&def_matr_1, &def_matr_2);
        tm = tick() - tm;
        tms += tm;
    }
    printf("\t%8lld\t\t%10lldБ\n", tms / ITERATIONS, sizeof(def_matr_res) + sizeof(double) * def_matr_res->m * def_matr_res->n);
}