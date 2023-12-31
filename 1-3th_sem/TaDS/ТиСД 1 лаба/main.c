/*
Малышев Иван Алексеевич ИУ7-31Б
Лабораторная работа №1
Вариант №6

Задача:
Смоделировать операцию деления действительного числа на действительное число в форме +-m.n Е +-K, где
суммарная длина мантиссы (m+n) - до 30 значащих цифр, а величина порядка K - до 5 цифр. Результат выдать в форме
+-0.m1 Е +-K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.
*/

#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NMAX 32 // Максимальная длина мантиссы
#define SRMAX 41 // Максимальная длина строки с информацией о действ. числе
#define MAX_EXP 99999 // Максимальный по модулю порядок

typedef char real_str_t[SRMAX];  // Строка с информацией о действительном числе

typedef struct
{
    char num_sign;
    int mantissa[NMAX];
    size_t mantissa_len; // Количество значащих цифр мантиссы
    long order;
} num_t;


//Функция смещает мантиссу действ. числа вправо
void move_num_end(num_t *data)
{
	size_t i = NMAX - 1;
	size_t j = data->mantissa_len;
	
	while (j > 0)
	{
        data->mantissa[i--] = data->mantissa[j - 1];
		data->mantissa[--j] = 0;
    }
}

//Нормализация действительного числа
void normalize(num_t *data)
{
    while (data->mantissa[0] == 0 && data->mantissa_len > 0)
    {
        for (size_t i = 1; i < data->mantissa_len; i++)
            data->mantissa[i - 1] = data->mantissa[i];
        data->mantissa_len -= 1;
        data->order -= 1;
        data->mantissa[data->mantissa_len] = 0;
    }
}

//Функция считывает в структуру действительного числа данные из строки 
//ввода и в случае неправильного ввода сообщает об ошибке
int is_real(real_str_t string, num_t *real)
{
    int i = 0;
    int digit; // очередная цифра
    int is_int_part_zero; // 1, если 0.123; 0, если 1.23
    long exp_of_int_part = 0; // порядок целой части
    long exp = 0;
    char exp_sign = '+';

    real->mantissa_len = 0;
    real->num_sign = '+';
    real->order = 0;

    if (string[i] == '-' || string[i] == '+')
    {
        if (string[i] == '-')
            real->num_sign = '-';
        i++;
    }
    
    is_int_part_zero = string[i] == '0';

    if (is_int_part_zero)
        real->order = 0;

    // Запись части мантиссы, которая находится до точки
    while (string[i] != '.' && string[i] != '\0' && string[i] != 'E')
    {
        if (isdigit(string[i]))
        {
            digit = string[i] - '0';
            
            if (real->mantissa_len == NMAX - 2)
            {
                printf("\nОШИБКА: Количество цифр мантиссы превышает допустимое. Максимальное количество цифр в мантиссе: %d.", NMAX - 2);
                return EXIT_FAILURE;
            }
            else if (digit == 0 && string[i + 1] != '.' && i == 0) // проверка на строку 00.123
            {
                printf("\nОШИБКА: Действительное число введено неправильно.");
                return EXIT_FAILURE;
            }
            else if (!is_int_part_zero)
            {
                real->mantissa[real->mantissa_len] = digit;
                real->mantissa_len += 1;
                exp_of_int_part += 1; 
            }  
        }
        else
        {
            printf("\nОШИБКА: Действительное число введено неправильно (Использованы недопустимые символы).");
            return EXIT_FAILURE;
        }
        i++;  
    }
    
    if (string[i] == '\0')
    {
        printf("\nОШИБКА: Неправильный ввод действительного числа. Действительное число должно вводиться с точкой.");
        return EXIT_FAILURE;
    }
    if (string[i] == '.')
        i++;


    while (string[i] != 'E' && string[i] != '\0')
    {
        if (isdigit(string[i]))
        {
            digit = string[i] - '0';
            
            if (real->mantissa_len == NMAX - 2)
            {
                printf("\nОШИБКА: Количество цифр мантиссы превышает допустимое. Максимальное количество цифр в мантиссе: 30.");
                return EXIT_FAILURE;
            }
            else
            {
                real->mantissa[real->mantissa_len] = digit;
                real->mantissa_len += 1;
            }
        }
        else
        {
            printf("\nОШИБКА: Действительное число введено неправильно.");
            return EXIT_FAILURE;
        }
        i++;
    }
    
    if (string[i++] != 'E')
    {
        real->order += exp_of_int_part;
        return EXIT_SUCCESS;
    }

    if (string[i] == '-' || string[i] == '+')
    {
        if (string[i] == '-')
            exp_sign = '-';
        i++;
    }

    while (isdigit(string[i]))
    {
        digit = string[i++] - '0';
        exp = exp * 10 + digit;
    }

    if (string[i] != '\0')
    {
        printf("\nОШИБКА: Неправильный порядок действительного числа.");
        return EXIT_FAILURE; 
    }

    real->order = exp_sign == '-' ? -exp : exp;

    if (labs(real->order) > MAX_EXP)
    {
        printf("\nОШИБКА: Количество разрядов порядка действительного числа превышает допустимое. Максимальное количество разрядов в порядке: 5.");
        return EXIT_FAILURE;
    }
    else
        real->order += exp_of_int_part;

    normalize(real);
        
    return EXIT_SUCCESS;
}

//функция двигает данные массива относительно его конца для выравнивания порядков и для возможности произвести операцию вычитания 
void move_digits(num_t *num, int mant_len_max, int offset)
{
    if (offset < 0) // двигает мантиссу порязрядно влево на offset разрядов
    {
        for (int i = 0; i < mant_len_max + offset; i++)
            num->mantissa[i] = num->mantissa[i - offset];
        for (int i = mant_len_max + offset; i < mant_len_max; i++)
            num->mantissa[i] = 0;
    }
    else if (offset > 0) // двигает мантиссу порязрядно вправо на offset разрядов
    {
        for (int i = mant_len_max - 1; i >= offset; i--)
            num->mantissa[i] = num->mantissa[i - offset];
        for (int i = offset - 1; i >= 0; i--)
            num->mantissa[i] = 0;
    }
}

//Функция поразрядного сравнения чисел 
int compare(num_t *real_1, num_t *real_2)
{
    int res = 0;
	for (int i = 0; res == 0 && i < NMAX; i++)
		res = real_1->mantissa[i] - real_2->mantissa[i];

	return res;
}

//Функция округления при нахождении 31 цифры мантиссы
void rounding(num_t *result, size_t size, int last_digit)
{
    if (last_digit >= 5)
    {
        result->mantissa[size - 1]++;
        for (int i = size - 1; i >= 0; i--)
        {
            if (result->mantissa[i] == 10)
            {
                result->mantissa[i] = 0;
                result->mantissa[i - 1]++;
            }
            else
                break;
        }
    }
}

//Функция пораздрядного вычетания цифр массивов
void subtract(num_t *real_1, num_t *real_2, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (real_1->mantissa[i] >= real_2->mantissa[i])
            real_1->mantissa[i] -= real_2->mantissa[i];
        else
        {
            real_1->mantissa[i] = 10 - real_2->mantissa[i] + real_1->mantissa[i];
            for (int j = 1; j <= i; j++)
            {
                if (real_1->mantissa[i - j] == 0)
                    real_1->mantissa[i - j] = 9;
                else
                {
                    real_1->mantissa[i - j]--;
                    break;
                }
                
            }
        }
    }
}

//Функция, обЪединяющая в себе логику деления
int division(num_t *real_1, num_t *real_2, num_t *result, int mant_len_max)
{
    size_t current_pos = 0;
    int attitude; // Отношение мантисс
    int are_not_equal;
	int count_of_subtracts = 0;
    int flag_zero = 0;

    move_num_end(real_1);
    move_num_end(real_2);

    result->num_sign = real_1->num_sign == real_2->num_sign ? '+' : '-';
    result->order = real_1->order - real_2->order;
        
    if (labs(result->order) > MAX_EXP)
    {
        printf("\nОШИБКА: Выход за пределы допустимого порядка результирующего числа.");
        return EXIT_FAILURE;
    }

    // Выравнивание мантисс
    int diff = real_1->mantissa_len - real_2->mantissa_len;

    if (diff > 0)
        move_digits(real_2, NMAX, -diff);
    else if (diff < 0)
        move_digits(real_1, NMAX, diff - 1);

    // Основная часть деления
    while (current_pos < NMAX)
    {
        if ((attitude = compare(real_1, real_2)) == 0)
        {
            result->mantissa[current_pos] = 1;
            result->order++;
            break;
        }
        else if (attitude > 0) // Цикличное вычитание мантиссы 2-го числа из 1-го
        {
            flag_zero = 0;
            count_of_subtracts = 0;
            
            while ((are_not_equal = compare(real_1, real_2)) >= 0)
            {
                if (are_not_equal == 0) // Если мантиссы равны
                {
                    count_of_subtracts++;
                    break;
                }
                subtract(real_1, real_2, mant_len_max);
                count_of_subtracts++;
            }

            if (current_pos == NMAX - 2)
            {
                rounding(result, NMAX - 2, count_of_subtracts);
                break;
            }
            else
            {
                result->mantissa[current_pos++] = count_of_subtracts;

                if (!are_not_equal)
                    break;
            }
        }
        else // дописывается ноль в результирующую мантиссу
        {
            if (flag_zero)
                    result->mantissa[current_pos++] = 0;
            flag_zero = 1;
            move_digits(real_1, mant_len_max, -1);
            
        }
    }

    // Вычисление длины результирующей мантиссы
    for (size_t k = 0; k < NMAX; k++)
        {
            if (result->mantissa[k])
                result->mantissa_len = k + 1;
        }
        
        if (result->mantissa[result->mantissa_len] != 0)
            result->mantissa_len++;

    return EXIT_SUCCESS;
}

//Функция проверки ввода действительного числа
int read_real(real_str_t s)
{
    int ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < SRMAX)
            s[i++] = ch;
        else
        {
            printf("\nОШИБКА: Введенные данные действительного числа слишком длинные.");
            return EXIT_FAILURE;
        }
    }
    s[i] = '\0';
    return EXIT_SUCCESS;
}

//Функция зануляет мантиссу
void cover_to_zeros_mant(num_t *num)
{
	for (int i = 0; i < NMAX; i++)
		num->mantissa[i] = 0;
}

// Приглашение на ввод действительного числа
void entrance(int i)
{
    printf("Введите %s действительное число в формате: +-m.nE+-k, где m+n <= 30, k - порядок числа, который меньше по модулю 100000.\n", i == 1 ? "первое" : "второе");
    printf("Корректный ввод: 0.125  125. 125.521E5 12E5 +25.000E-80\n");
    printf("Число вводится без пробелов.\n");
    printf("      +---------|---------|---------|E+-----\n");
    printf("Ввод: ");
}

int main(void)
{
    real_str_t real_1_s, real_2_s;
    num_t real_1, real_2, result;
	
    setbuf(stdout, NULL);

	cover_to_zeros_mant(&real_1);
	cover_to_zeros_mant(&real_2);
    cover_to_zeros_mant(&result);

    printf("Программа предназначена для деления действительного числа на действительное.\n\n");

    entrance(1);
    if (read_real(real_1_s) != 0)
        return EXIT_FAILURE;
    
    if (is_real(real_1_s, &real_1) != 0)
        return EXIT_FAILURE;

    entrance(2);
    if (read_real(real_2_s) != 0)
        return EXIT_FAILURE;
    
    if (is_real(real_2_s, &real_2) != 0)
        return EXIT_FAILURE;

    if (real_1.mantissa[0] == 0)
    {
        if (real_2.mantissa[0] == 0)
        {
            printf("\nОШИБКА: Результат не может быть получен (деление на ноль).");
            return EXIT_FAILURE;
        }
        else
        {
            printf("\n\nОтвет: 0.0E0");
            return EXIT_SUCCESS;
        }
    }

    if (real_2.mantissa[0] == 0)
    {
        printf("\nОШИБКА: Результат не может быть получен (деление на ноль).");
        return EXIT_FAILURE;
    }

    if (division(&real_1, &real_2, &result, NMAX) == EXIT_SUCCESS)
    {
        printf("\nОтвет: %c0.", result.num_sign);
        
        for (size_t k = 0; k < result.mantissa_len; k++)
            printf("%d", result.mantissa[k]);
        
        printf("E%ld", result.order);
    }
    else
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}