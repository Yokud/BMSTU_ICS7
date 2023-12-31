from math import sin

print('Введите начальное, конечное значение и шаг аргумента через пробел: ',
      end='')
start, finish, step = map(float, input().split())
N = round((finish - start)/step)
f_min = sin(start)
f_max = sin(finish)
for i in range(N):
    x = start + i*step
    f = sin(x)
    f_min = min(f_min, f)
    f_max = max(f_max, f)
delta_f = f_max - f_min
print('{:>6.2g}'.format(f_min), ' '*64, '{:>6.2g}'.format(f_max), \
      sep = '')
print(' '*5, '\u2514', '\u2500'*69, '\u2534\u2500> f(x)', sep = '')
stick = 0
j = 0
if f_min <= 0 and f_max >= 0:
    stick = round(-f_min/delta_f*70)
    j = 1
x = start
for i in range(N + 1):
    print('{:5.2g}'.format(x), end = '')
    f = sin(x)
    g = round((f - f_min)/delta_f*70)
    if g > stick:
        print(' '*stick, '\u2502'*j, ' '*(g-stick-1), '*', sep='')
    elif g == stick:
        print(' '*g, '*', sep = '')
    else:
        print(' '*g, '*', ' '*(stick - g- 1), '\u2502'*j, sep ='')
    x += step
print(' '*(stick + 4)*j, 'V')
print(' '*(stick + 4)*j, 'x')
