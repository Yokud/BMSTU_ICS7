# Лабораторная работа: Процедура для символьной матрицы

# Программа определяет наличие латинских букв в каждой строке символьной
# матрицы A(N, M) и при их наличие размещает их в начале строки, а все другие -
# в конец. Строки, имеющие гласные буквы, записываются в один файл, а не
# имеющие гласных букв - в другой. Далее печатает исходную и преобразованную
# матрицы и содержимое файлов

# Переменные:
# A, N, M - матрица, число строк и число столбцов
# VOWELS - строка с гласными латинскими буквами
# File_with_v - файл со строками, в которых есть гласные латинские буквы
# File_without_v - файл со строками, в которых нет гласных латинских букв
# si, sj, flag - вспомогательные переменные

def Procedure(A):
    N = len(A)
    M = len(A[0])

    print('Исходная матрица:')
    for i in range(N):
        print(A[i])
    print('\n')

    # Преобразование матрицы
    for i in range(N):
        for j in range(M):
            if ord(A[i][j]) >= 65 and ord(A[i][j]) <= 122:
                A[i].insert(0, A[i][j])
                del A[i][j+1]
    
    print('Преобразованная матрица:')
    for i in range(N):
        print(A[i])
    print('\n')

    VOWELS = 'aeiouy'
    File_with_v = open('With_Vowels.txt', 'w+')
    File_without_v = open('Without_Vowels.txt', 'w+')

    # Фильтрация строк по наличию гласных и их запись в соответствующие файлы
    for i in A:
        flag = 0
        for j in i:
            if j in VOWELS or j in VOWELS.upper():
                flag += 1
        if flag:
            File_with_v.write(''.join(i) + '\n')
        else:
            File_without_v.write(''.join(i) + '\n')
                
    File_with_v = open('With_Vowels.txt', 'w+')
    File_without_v = open('Without_Vowels.txt', 'w+')
    
    print('Строки с гласными:')
    for line in File_with_v:
        if line == '':
            print('Файл пуст')
            break
        else:
            print(line, end = '')
    print('\n')
    
    print('Строки без гласных:')
    for line in File_without_v:
        if line == '':
            print('Файл пуст')
            break
        else:
            print(line, end = '')

    File_with_v.close()
    File_without_v.close()

    

print('Введите символьную матрицу. Количество столбцов в матрице определяет'\
      +'ся количеством введёных элементов с новой строки в строку матрицы, '\
      +'но их должно быть одинаковое количество в каждой строке матрицы и не'\
      +' более 7. Количество строк в матрице определяется количеством введён'\
      +'ных строк до ввода пустой строки, но их должно быть не более 10.\n')

A = []
for i in range(10):
    print('Введите {:d} строку матрицы: '.format(i+1))
    si = False
    flag = False
    A.append([])
    for j in range(7):
        sj = input()
        if sj == '':
            if j == 0:
                si = True
            elif len(A[i]) != len(A[0]):
                    A.clear()
                    flag = True
            break
        else:
            A[i].append(sj)

    if si:
        del A[i]
        break
    
    if flag:
        break

try:
    Procedure(A)
except:
    print('Ошибка!')

