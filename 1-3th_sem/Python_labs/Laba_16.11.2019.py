# Лабораторная работа: Процедуры для типизированного файла

# Программа имеет процедуры для сортировки целых чисел Sorting в файле и
# добавления новых чисел Data, а также процедуру для вывода содержимого Pokaz

def Sorting(P_way):
    P = open(P_way)
    count = 0
    f1 = open('f1.txt', 'w')
    for line in P:
        f1.write(line)
        count += 1
    P.close()
    f1.close()
    key = 0
    for r in range(count-1):
        if r % 2 == 0:
            f1 = open('f1.txt')
            f2 = open('f2.txt','w')
            for n in range(count-r-1):
                if n == 0:
                    a = int(f1.readline())
                    b = int(f1.readline())
                elif n % 2 == 0:
                    b = int(f1.readline())
                else:
                    a = int(f1.readline())
                if a < b:
                    f2.write(str(a)+'\n')
                    if n % 2 != 0 and n != count-r-2:
                        a = b
                else:
                    f2.write(str(b)+'\n')
                    if n % 2 == 0 and n != count-r-2:
                        b = a
    
                if n == count-r-2:
                    f2.write(str(max(a, b)))
            for p in range(r):
                x = int(f1.readline())
                f2.write('\n' + str(x))
            key = 1
            f1.close()
            f2.close()
        else:
            f1 = open('f1.txt','w')
            f2 = open('f2.txt')
            for n in range(count-r-1):
                if n == 0:
                    a = int(f2.readline())
                    b = int(f2.readline())
                elif n % 2 == 0:
                    b = int(f2.readline())
                else:
                    a = int(f2.readline())
                if a < b:
                    f1.write(str(a)+'\n')
                    if n % 2 != 0 and n != count-r-2:
                        a = b
                else:
                    f1.write(str(b)+'\n')
                    if n % 2 == 0 and n != count-r-2:
                        b = a
                    
                if n == count-r-2:
                    f1.write(str(max(a, b)))

            for p in range(r):
                x = int(f2.readline())
                f1.write('\n' + str(x))
            key = 2
            f1.close()
            f2.close()
    P = open(P_way,'w')
    f1 = open('f1.txt')
    f2 = open('f2.txt')
    if key == 1:
        for line in f2:
            P.write(line)
    elif key == 2:
        for line in f1:
            P.write(line)
    f1.close()
    f2.close()
    P.close()
        

def Data(P_way):
    P = open(P_way, 'w')
    L = int(input('Введите количество элементов в файлe(не более 6): '))
    if L > 6:
        print('Избыток элементов')
    else:
        for i in range(L):
            if i != L - 1:
                P.write(input('Введите '+ str(i+1) + ' элемент: ') + '\n')
            else:
                P.write(input('Введите '+ str(i+1) + ' элемент: '))
        P.close()


def Pokaz(P_way):
    P = open(P_way)
    try:
        print('Содержимое файла:')
        for line in P:
            print(line, end = '')
    except:
        print('Возникла проблема с чтением файла')
    P.close()

Z_name = input('Введите название файла: ')
if Z_name == 'f1' or Z_name == 'f2':
    Z_name += '+'
Z_way = Z_name + '.txt'

Data(Z_way)
Sorting(Z_way)
Pokaz(Z_way)

