# Лабораторная работа: Матрица W

# Назначение программы: Формирование матрицы на основе массива d и формирование
# массива B для хранения элементов с мин. и макс. произведением элементов
# в столбце

# Описание переменных:
# W - матрица, d - массив, M - число строк, N - число столбцов
# B - массив для хранения элементов, дающие мин. и макс. произведение в столбце
# Min_k, Max_k, mult - вспомогательные переменные

# Тестовый пример:
# 2 2
# 1 2
#
#  0.4288  0.4797 
# -0.3303 -0.3695 
#
# 0.4797 -0.3695 0.4288 -0.3303

from math import cos
M, N = map(int, input('Введите число строк(не более 13) и столбцов(не более 7)'\
           ' для матрицы через пробел: ').split())
if M > 13 or N > 7:
    print('Неверные входные данные!')
else:
    W = [0]*M
    for j in range(M):
        W[j] = [0]*N
    d = list(map(float, input('Введите элементы массива d('+ str(M) +')'\
                              +' через пробел: ').split()))
    print()
    if len(d) != M:
        print('Неверные входные данные!')
    else:
        for j in range(M):
            for k in range(N):
                x = 0.5 + 0.2*k
                W[j][k] = cos(d[j])*x**(1/3)
        for j in range(M):
            for k in range(N):
                print('{:7.4f} '.format(W[j][k]), end = '')
            print()
            
        B = [0]*2*M

        # Поиск номеров столбцов с минимальным и максимальным произведением
        # элементов в столбце
        mult = [1]*N
        for k in range(N):
            for j in range(M):
                mult[k] *= W[j][k]
        Min_k, Max_k = mult.index(min(mult)), mult.index(max(mult))
        
        for i in range(2*M):
            if i < M:
                B[i] = W[i][Min_k]
            else:
                B[i] = W[i-M][Max_k]
        print()
        for b in B:
            print('{:.4f}'.format(b), end = ' ')