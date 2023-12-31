#include "sparse_matrices.h"


command_t get_command(char *s)
{
    if (!strcmp(s, "out"))
        return OUT;
    else if (!strcmp(s, "add"))
        return ADD;
    else if (!strcmp(s, "mul"))
        return MUL;
    else if (!strcmp(s, "lin"))
        return LIN;

    return UNKNOWN_COMMAND;  
}

int create_matrix(sparse_matrix_t **matr_a)
{
    long n, m, elem;
    sparse_matrix_t *cur;

    if (scanf("%ld %ld", &n, &m) != 2 || n <= 0 || m <= 0)
        return INPUT_ERROR;

    *matr_a = malloc(sizeof(sparse_matrix_t));

    if (!*matr_a)
        return ALLOC_ERROR;

    cur = *matr_a;
    cur->next = cur;

    for (long i = 0; i < n; i++)
        for (long j = 0; j < m; j++)
            if (scanf("%ld", &elem) != 1)
            {
                free(cur->next);
                cur->next = NULL;

                free_matrix(*matr_a);
                *matr_a = NULL;

                return INPUT_ERROR;
            }
            else if (elem)
            {
                cur = cur->next;

                cur->row = i;
                cur->col = j;
                cur->elem = elem;

                cur->next = malloc(sizeof(sparse_matrix_t));
                if (!cur->next)
                {
                    free_matrix(*matr_a);
                    *matr_a = NULL;
                    return ALLOC_ERROR;
                }
            }

    free(cur->next);
    cur->next = NULL;

    return OK;    
}

void print_matrix(sparse_matrix_t *matr_a)
{
    if (!matr_a)
        return;

    for (sparse_matrix_t *cur = matr_a; cur; cur = cur->next)
        printf("%ld %ld %ld ", cur->row, cur->col, cur->elem);
    printf("\n");
}

void free_matrix(sparse_matrix_t *matr_a)
{
    sparse_matrix_t *next;

    for (; matr_a; matr_a = next)
    {
        next = matr_a->next;
        free(matr_a);
    }
}

sparse_matrix_t *add_matrices(sparse_matrix_t *matr_a, sparse_matrix_t *matr_b)
{
    if (!matr_a || !matr_b)
        return NULL;

    sparse_matrix_t *cur_a, *cur_b, *cur_res, *res;
    long sum;

    res = malloc(sizeof(sparse_matrix_t));

    if (!res)
        return NULL;

    cur_res = res;
    cur_res->next = cur_res;
    for (cur_a = matr_a, cur_b = matr_b; cur_a && cur_b;)
    {
        if (cur_a->row == cur_b->row && cur_a->col == cur_b->col)
        {
            sum = cur_a->elem + cur_b->elem;

            if (sum)
            {
                cur_res = cur_res->next;

                cur_res->row = cur_a->row;
                cur_res->col = cur_a->col;
                cur_res->elem = sum;
                cur_res->next = malloc(sizeof(sparse_matrix_t));
                if (!cur_res->next)
                {
                    free_matrix(res);
                    return NULL;
                }
            }

            cur_a = cur_a->next;
            cur_b = cur_b->next;
        }
        else
        {
            cur_res = cur_res->next;

            if (cur_a->row > cur_b->row)
            {
                cur_res->row = cur_b->row;
                cur_res->col = cur_b->col;
                cur_res->elem = cur_b->elem;

                cur_b = cur_b->next;
            }
            else if (cur_a->row < cur_b->row)
            {
                cur_res->row = cur_a->row;
                cur_res->col = cur_a->col;
                cur_res->elem = cur_a->elem;

                cur_a = cur_a->next;
            }
            else if (cur_a->col > cur_b->col)
            {
                cur_res->row = cur_b->row;
                cur_res->col = cur_b->col;
                cur_res->elem = cur_b->elem;

                cur_b = cur_b->next;
            }
            else if (cur_a->col < cur_b->col)
            {
                cur_res->row = cur_a->row;
                cur_res->col = cur_a->col;
                cur_res->elem = cur_a->elem;

                cur_a = cur_a->next;
            }

            cur_res->next = malloc(sizeof(sparse_matrix_t));
            if (!cur_res->next)
            {
                free_matrix(res);
                return NULL;
            }
        }
    }
    
    while (cur_a)
    {
        cur_res = cur_res->next;

        cur_res->row = cur_a->row;
        cur_res->col = cur_a->col;
        cur_res->elem = cur_a->elem;
        cur_res->next = malloc(sizeof(sparse_matrix_t));
        if (!cur_res->next)
        {
            free_matrix(res);
            return NULL;
        }

        cur_a = cur_a->next;
    }

    while (cur_b)
    {
        cur_res = cur_res->next;

        cur_res->row = cur_b->row;
        cur_res->col = cur_b->col;
        cur_res->elem = cur_b->elem;
        cur_res->next = malloc(sizeof(sparse_matrix_t));
        if (!cur_res->next)
        {
            free_matrix(res);
            return NULL;
        }

        cur_b = cur_b->next;
    }
    
    free(cur_res->next);
    cur_res->next = NULL;

    return res;
}

sparse_matrix_t *mult_matrices(sparse_matrix_t *matr_a, sparse_matrix_t *matr_b)
{
    if (!matr_a || !matr_b)
        return NULL;

    sparse_matrix_t *matr_b_tr, *res;
    sparse_matrix_t *cur_b_tr, *cur_res;
    long sum;
    long prev_row;

    matr_b_tr = malloc(sizeof(sparse_matrix_t));

    if (!matr_b_tr)
        return NULL;

    cur_b_tr = matr_b_tr; // Создаём транспонированную копию второй матрицы для удобного скалярного умножения векторов
    cur_b_tr->next = cur_b_tr;
    for (sparse_matrix_t *cur_b = matr_b; cur_b; cur_b = cur_b->next)
    {
        cur_b_tr = cur_b_tr->next;

        cur_b_tr->row = cur_b->col;
        cur_b_tr->col = cur_b->row;
        cur_b_tr->elem = cur_b->elem;
        cur_b_tr->next = malloc(sizeof(sparse_matrix_t));
        if (!cur_b_tr->next)
        {
            free_matrix(matr_b_tr);
            return NULL;
        }
    }

    free(cur_b_tr->next);
    cur_b_tr->next = NULL;

    res = malloc(sizeof(sparse_matrix_t));

    if (!res)
        return NULL;

    cur_res = res;
    cur_res->next = cur_res;
    for (sparse_matrix_t *cur_a_i = matr_a; cur_a_i;)
    {
        for (sparse_matrix_t *cur_b_tr_i = matr_b_tr; cur_b_tr_i;)
        {
            sum = 0;
            
            for (sparse_matrix_t *cur_a_j = cur_a_i, *cur_b_tr_j = cur_b_tr_i; cur_a_j && cur_b_tr_j && cur_a_j->row == cur_a_i->row && cur_b_tr_j->row == cur_b_tr_i->row;)
            {
                if (cur_a_j->col < cur_b_tr_j->col)
                    cur_a_j = cur_a_j->next;
                else if (cur_a_j->col > cur_b_tr_j->col)
                    cur_b_tr_j = cur_b_tr_j->next;
                else
                {
                    sum += cur_a_j->elem * cur_b_tr_j->elem;
                    cur_a_j = cur_a_j->next;
                    cur_b_tr_j = cur_b_tr_j->next;
                }
            }

            if (sum)
            {
                cur_res = cur_res->next;

                cur_res->elem = sum;
                cur_res->row = cur_a_i->row;
                cur_res->col = cur_b_tr_i->row;

                cur_res->next = malloc(sizeof(sparse_matrix_t));
                if (!cur_res->next)
                {
                    free_matrix(res);
                    free_matrix(matr_b_tr);
                    return NULL;
                } 
            }

            do
            {
                prev_row = cur_b_tr_i->row;
                cur_b_tr_i = cur_b_tr_i->next;
            } while (cur_b_tr_i && prev_row == cur_b_tr_i->row);
        }

        do
        {
            prev_row = cur_a_i->row;
            cur_a_i = cur_a_i->next;
        } while (cur_a_i && prev_row == cur_a_i->row);
    }
    
    free_matrix(matr_b_tr);
    free(cur_res->next);
    cur_res->next = NULL;

    return res;
}

int del_row_by_max_elem(sparse_matrix_t **matr_a)
{
    if (!matr_a || !*matr_a)
        return INPUT_ERROR;

    long row_max, max_elem;
    sparse_matrix_t *cur, *prev = NULL;

    row_max = 0;
    max_elem = (*matr_a)->elem;

    for (cur = *matr_a; cur; cur = cur->next)
        if (cur->elem > max_elem)
        {
            max_elem = cur->elem;
            row_max = cur->row;
        }
    
    for (cur = *matr_a; cur && cur->row <= row_max; cur = cur->next)
    {
        if (cur->row == row_max)
        {
            // обратное м. б. только в том случае, если удаляется нулевая строка
            if (prev)
                prev->next = cur->next;
            else
                (*matr_a)->next = cur->next;

            free(cur);
            cur = prev ? prev : *matr_a;
        }
        prev = cur;
    }

    return OK;
}