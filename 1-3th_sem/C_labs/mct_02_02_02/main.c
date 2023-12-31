#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define SURNAME_MAX 32

typedef struct
{
    char surname[SURNAME_MAX + 1];
    double height;
} student;

// Функция получает массив, длину и позицию сдвига.
// Сдвигает элементы массива с индексом от n - 1 до pos + 1 на один вправо.
void shift_elems(long a[], size_t n, size_t pos)
{
    for (size_t i = pos; i < n - 1; i++)
        a[i] = a[i + 1];
}

// Функция получает массив и его длину.
// Удаляет из массива чётные элементы и изменяет длину массива.
void sort_array(long a[], size_t *n)
{
    for (size_t i = 0; i < *n; i++)
    {
        if (a[i] % 2 == 0)
        {
            shift_elems(a, *n, i);
            (*n)--;
        }
    }
}

size_t file_size(FILE *f, size_t *size)
{
    long sz;
    if (fseek(f, 0L, SEEK_END))
        return -1;

    sz = ftell(f);
    if (sz < 0)
        return -1;
    
    *size = sz;
    return fseek(f, 0L, SEEK_SET);
}

void get_student_by_pos(FILE *f, student *stud, size_t pos)
{
    fseek(f, pos * sizeof(student), SEEK_SET);
    fread(stud, sizeof(student), 1, f);
}

void put_student_by_pos(FILE *f, student stud, size_t pos)
{
    fseek(f, pos * sizeof(student), SEEK_SET);
    fwrite(&stud, sizeof(student), 1, f);
}

void shift_students(FILE *f, size_t count, size_t pos)
{
    student stud;

    for (size_t i = pos; i < count - 1; i++)
    {
        get_student_by_pos(f, &stud, i + 1);
        put_student_by_pos(f, stud, i);
    }
}

void delete_tall_students(FILE *f)
{
    size_t size, n, deleted;
    student stud, del_stud;

    file_size(f, &size);

    n = size / sizeof(student);
    deleted = 0;

    for (size_t i = 0; i < n; i++)
    {
        get_student_by_pos(f, &stud, i);

        if (stud.height > 2.0)
        {
            deleted++;
            del_stud = stud;
            shift_students(f, n, i);
            put_student_by_pos(f, del_stud, n - 1);
        }
    }

    if (deleted)
    {
        get_student_by_pos(f, &stud, n - deleted);
        stud.height = -1.0;
        put_student_by_pos(f, stud, n - deleted);
    }
}

int main(void)
{
    FILE *students = stdin;

    delete_tall_students(students);

    return EXIT_FAILURE;
}