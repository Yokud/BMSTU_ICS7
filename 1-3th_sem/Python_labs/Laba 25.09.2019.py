# Лабораторная работа: Таблица значений функции

# Назначение программы:
# Расчёт значений функции

# Переменные:
# start, finish, step - начальное, конечное значение и шаг аргумента
# b, d1, d2 - аргумент, первая и вторая функция
# N - количество шагов
# sign, newsign - знак функции d2
# cosign - количество перемен знака функции d2

# Контрольные точки:
# b = 0.20  d1 = -0.23789  d2 = -14.44000
# b = 0.60  d1 = 0.13991   d2 = -8.29600

from math import sqrt
start, finish, step = map(float, input('Введите начальное, конечное значение '\
                                       +'аргумента и шаг через пробел: ').\
                          split())

sign = start**3 + 9.3*start**2 + 7.4*start - 16.3 < 0
cosign = 0

# Начало таблицы
for i in range(36):
    if i == 0:
        print('\u250C', end = '')
    elif i == 35:
        print('\u2510')
    elif i == 11 or i == 23:
        print('\u252C', end = '')
    else:
        print('\u2500', end = '')
print('│{:^10s}│{:^11s}│{:^11s}│'. format('b', 'd1', 'd2'))
for i in range(36):
    if i == 0:
        print('\u251C', end = '')
    elif i == 35:
        print('\u2524')
    elif i == 11 or i == 23:
        print('\u253C', end = '')
    else:
        print('\u2500', end = '')


N = int((finish - start)/step) + 1

# Расчёт значений функции и их печать
for i in range(N):
    b = start + i*step
    if b <= -1: # Если d1 не определена
        d1 = 'Не сущ.'
        d2 = b**3 + 9.3*b*b + 7.4*b - 16.3
        if abs(d2) < 10000:
            print('│{:^10.2f}│{:^11s}│{:^11.5f}│'.format(b, d1, d2))
        else:
            print('│{:^10.2f}│{:^11s}│{:^11.3e}│'.format(b, d1, d2))
        if i < N-1:    # Продолжение таблицы
            for i in range(36):
                if i == 0:
                    print('\u251C', end = '')
                elif i == 35:
                    print('\u2524')
                elif i == 11 or i == 23:
                    print('\u253C', end = '')
                else:
                    print('\u2500', end = '')
        else:    # Конец таблицы
            for i in range(36):
                if i == 0:
                    print('\u2514', end = '')
                elif i == 35:
                    print('\u2518')
                elif i == 11 or i == 23:
                    print('\u2534', end = '')
                else:
                    print('\u2500', end = '')
    else:    # Если d1 определена
        d1 = sqrt(b+1) - 1/(b+1) - 0.5
        d2 = b**3 + 9.3*b*b + 7.4*b - 16.3
        if abs(d2) < 10000:
            print('│{:^10.2f}│{:^11.5f}│{:^11.5f}│'.format(b, d1, d2))
        else:
            print('│{:^10.2f}│{:^11.5f}│{:^11.3e}│'.format(b, d1, d2))
        if i < N-1:    # Продолжение таблицы
            for i in range(36):
                if i == 0:
                    print('\u251C', end = '')
                elif i == 35:
                    print('\u2524')
                elif i == 11 or i == 23:
                    print('\u253C', end = '')
                else:
                    print('\u2500', end = '')
        else:    # Конец таблицы
            for i in range(36):
                if i == 0:
                    print('\u2514', end = '')
                elif i == 35:
                    print('\u2518')
                elif i == 11 or i == 23:
                    print('\u2534', end = '')
                else:
                    print('\u2500', end = '')
    # Проверка знака d2
    newsign = d2 < 0       
    if sign != newsign:
        cosign += 1
        sign = newsign
print('Количество перемен знака функции d2:', cosign)
