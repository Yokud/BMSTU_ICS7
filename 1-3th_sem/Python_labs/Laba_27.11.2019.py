# Лабораторная работа: Шифровальная машина

# Назначение программы:
# Программа формирует матрицу из 0 и 1 случайным образом и потом фромирует
# вектор, состоящий из десятичных записей строк

# Переменные:
# Matrix, N - матрица и её порядок
# Vector - вектор десятичных чисел
# A, S, r1, r2, V, sum_ - вспомогательные переменные

# Тестовый пример:
# N = 3
#
# Matrix = [[1, 0, 1], [0, 1, 1], [1, 0, 0]]
# Vector = [5, 3, 4]

import random

def GenMatrix(N):
    A = [[0]*N for i in range(N)]
    for i in range(N):
        S = A[i]
        r1 = random.randint(1, N)
        while True:
            for j in range(r1):
                r2 = random.randint(0, N - 1)
                S[r2] = 1
            if S in A:
                S = [0] * N
            else:
                break
                
        A[i] = S
    return A

def GenVector(A):
    N = len(A)
    V = [0]*N
    for i in range(N):
        sum_ = 0
        for j in range(N):
            if A[i][j] == 1:
                sum_ += 2**(N - j - 1)
        V[i] = sum_
    return V

N = int(input('Введите порядок матрицы: '))
Matrix = Func1(N)
print('Матрица:')
for m in Matrix:
    print(m)
Vector = Func2(Matrix)
print('\nВектор:')
print(Vector)
