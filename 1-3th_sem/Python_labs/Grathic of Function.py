# Лабораторная работа: Построение графика

# Программа предназначенна для изображения графика функции
# d2 = b**3 + 9.3*b*b + 7.4*b - 16.3

# start, finish, step - начальное, конечное значение и шаг аргумента
# Nz - число засечек, N - кол-во значений аргумента, b - текущий аргумент ф-ии
# min_d, max_d - максимальное и минимальное значение ф-ии, d - значение ф-ии
# delta_d - разница между макс. и мин. значением ф-ии
# Zas - длина интервалов на оси Oy
# c, trsltr, p, stick, j, g - вспомогательные переменные

print('Введите начальное, конечное значение и шаг аргумента через пробел: ',
      end='')
start, finish, step = map(float, input().split())
Nz = int(input('Введите количество засечек(от 4 до 8): '))
N = round((finish - start)/step)
min_d = start**3 + 9.3*start*start + 7.4*start - 16.3
max_d = finish**3 + 9.3*finish*finish + 7.4*finish - 16.3

# Нахождение мин. и макс. значения функции
for i in range(N):
    b = start + i*step
    d = b**3 + 9.3*b*b + 7.4*b - 16.3
    min_d = min(min_d, d)
    max_d = max(max_d, d)

delta_d = max_d - min_d
Zas = round(70/(Nz-1))
b = start
c = delta_d/(Nz - 1)

# Ось Y
if abs(min_d) >= 1000 or abs(min_d) <= 0.001:
    trsltr = '{:>8.1e}'
else:
    trsltr = '{:>8.1f}'
print(' '*3, trsltr.format(min_d), sep = '', end = '')
for i in range(1, Nz - 1):
    if abs(min_d + i*c) < 1000 and abs(min_d + i*c) > 0.001:
        trslt = '{:>8.1f}'
    else:
        trsltr = '{:>8.1e}'
    print(' '*(Zas - 7), trsltr.format(min_d + i*c), sep = '', end = '')
if abs(max_d) >= 1000:
    trsltr = '{:>8.1e}'
else:
    trsltr = '{:>8.1f}'
print(' '*(Zas - 8), trsltr.format(max_d), sep = '', end = '')
print('\t')

print(' '*7, '\u2514', sep = '', end = '')
for i in range(Nz - 2):
    print('\u2500'*Zas, '\u2534', sep = '', end = '')
print('\u2500'*Zas, '\u2518 d2', sep = '')

# Ось X
p= Zas*(Nz - 1) + Nz-1
stick = 0
j = 0
if min_d <= 0 and max_d >= 0:
    stick = round(-min_d/delta_d*p)
    j = 1
b = start
for i in range(N + 1):
    if (abs(b) >= 1000 or abs(b) < 0.01) and b != 0:
        trsltr = '{:7.1e}'
    else:
        trsltr = '{:7.2f}'
    print(trsltr.format(b), end = '')
    d = b**3 + 9.3*b*b + 7.4*b - 16.3
    g = round((d - min_d)/delta_d*p)
    if g > stick:
        print(' '*stick, '\u2502'*j, ' '*(g-stick-1), '*', sep='')
    elif g == stick:
        print(' '*g, '*', sep = '')
    else:
        print(' '*g, '*', ' '*(stick - g- 1), '\u2502'*j, sep ='')
    b += step
print(' '*(stick + 6)*j, 'b')
