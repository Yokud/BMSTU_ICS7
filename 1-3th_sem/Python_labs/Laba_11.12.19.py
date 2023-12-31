# Лабораторная работа: Сравнение методов по поиску корней

# Назначение программы:
# Печать таблиц корней функции на отрезках, лежащие внутри отрезка [a, b],
# методом половинного деления собственной разработки и взятого из Scipy

# Описание переменных:
# a, b, h - начало и конец отрезка, шаг
# eps, max_iter - точность, максимальное число итераций
# args, res_of_func, time - массив концов отрезков, результат функции, время
# выполнения функции
# iters - реальное число итераций
# start, end, x, num_iter, s, s_eps - вспомогательные переменные

import scipy.optimize as optimize
import numpy as np
import timeit

def f(x):
    return np.sin(x)

def Bisect(f, a, b, eps, maxiter):
    start, end = a, b
    if f(a)*f(b) > 0:
        return None     # Корня нет
    if f(a) == 0:
        return a, 1
    elif f(b) == 0:
        return b, 1
    iters = 0
    x = (start+end)/2
    while iters < maxiter and np.abs(f(x)) > eps:
        x = (start+end)/2
        if f(a)*f(x) < 0:
            end = x
        elif f(b)*f(x) < 0:
            start = x
        iters += 1
    if np.abs(f(x)) > eps:
        return '101' # Превышено число итераций
    else:
        return x, iters

a, b = map(float, input('Границы интервала(через пробел): ').split())
if a == b:
    print('Границы интервала совпадают!')
    raise SystemExit()

h = float(input('Шаг: '))
if h > b-a:
    print('Слишком большой шаг!')
    raise SystemExit()

s_eps = input('Точность: ')
eps = float(s_eps)
max_iter = int(input('Максимальное число итераций: '))
args = np.arange(a, b+h, h)

if args[-1] > b:
    args[-1] = b

print('┌──────────────┐')
print('│Таблица ошибок│')
print('├─────┬────────┴─────────────────┐')
print('│{:^5s}│{:^26s}│'.format('0','Ошибок нет'))
print('├─────┼──────────────────────────┤')
print('│{:^5s}│{:^26s}│'.format('101', 'Превышено число итераций'))
print('└─────┴──────────────────────────┘')


print('\n')
  
print('┌────────────────────────────────────────────────┐')
print('│Метод половинного деления собственной разработки│')
print('├─────┬────────┬────────┬──────────┬────────────┬┴'\
      +'───────┬──────────┬──────────┐')
print('│{:^5s}│{:^8s}│{:^8s}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│{:^10s}│'\
      .format('Номер', 'Начало', 'Конец', 'Значение', 'Значение', 'Реальное',\
              'Время', 'Код'))
print('│{:^5s}│{:^8s}│{:^8s}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│{:^10s}│'\
      .format('корня', 'отрезка', 'отрезка', 'x', 'f(x)', 'число', 'работы',\
              'ошибки'))
print('│{:^5s}│{:^8s}│{:^8s}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│{:^10s}│'\
      .format('', '', '', '', '', 'итераций', 'ф-ии', ''))

for i in range(len(args) - 1):
    res_of_func = Bisect(f, args[i], args[i+1], eps, max_iter)
    try:
        time = timeit.timeit('Bisect(f, args[i], args[i+1], eps, max_iter)',\
              setup = 'from __main__ import Bisect, f, args, eps, max_iter, i',\
              number = 10)
        if f(res_of_func[0]) == 0:
            s = '│{:^5d}│{:^8.6g}│{:^8.6g}│{:^10.7g}│{:^12.0g}│{:^8d}│{:^10.3g'\
                +'}│{:^10s}│'
        else:
            s = '│{:^5d}│{:^8.6g}│{:^8.6g}│{:^10.7g}│{:^12.0e}│{:^8d}│{:^10.3g'\
                +'}│{:^10s}│'
        s = s.format(i+1, args[i], args[i+1], res_of_func[0],\
                       f(res_of_func[0]), res_of_func[1], time, '0')
        print('├─────┼────────┼────────┼──────────┼────────────┼────────┼────'\
          +'──────┼──────────┤')
        print(s)
    except:
        if res_of_func == None:
            continue
        else:
            print('├─────┼────────┼────────┼──────────┼────────────┼────────┼'\
                  +'──────────┼──────────┤')
            s = '│{:^5d}│{:^8.6g}│{:^8.6g}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│'\
                +'{:^10s}│'
            print(s.format(i+1, args[i], args[i+1], '-', '-', '-', '-',\
                           res_of_func))
          
print('└─────┴────────┴────────┴──────────┴────────────┴────────┴──────────┴'\
      +'──────────┘')
print('\n')

print('┌─────────────────────────────────────────────┐')
print('│Метод половинного деления из библиотеки Scipy│')
print('├─────┬──────────┬────────────┬────────┬──────┴───┬──────────┐')
print('│{:^5s}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│{:^10s}│'\
      .format('Номер', 'Значение', 'Значение', 'Реальное',\
              'Время', 'Код'))
print('│{:^5s}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│{:^10s}│'\
      .format('корня', 'x', 'f(x)', 'число', 'работы',\
              'ошибки'))
print('│{:^5s}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│{:^10s}│'\
      .format('', '', '', 'итераций', 'ф-ии', ''))

for i in range(len(args) - 1):
    
    try:
        res_of_func, rootRes = optimize.bisect(f, args[i], args[i+1],\
                                               rtol = eps, maxiter = max_iter,\
                                               full_output = True)
        iters = rootRes.iterations
        time = timeit.timeit('bisect(f, args[i], args[i+1], rtol = eps,'\
                             +' maxiter = max_iter)',\
              setup = 'from scipy.optimize import bisect;'\
                      +' from __main__ import f, args, eps, max_iter, i',\
              number = 10)
        if f(res_of_func) == 0:
            iters = 1
            s = '│{:^5d}│{:^10.7g}│{:^12.0g}│{:^8d}│{:^10.3g}│{:^10s}│'.format(\
                i+1, res_of_func, f(res_of_func), iters, time, '0')
        else:
            s = '│{:^5d}│{:^10.7g}│{:^12.0e}│{:^8d}│{:^10.3g}│{:^10s}│'.format(\
                i+1, res_of_func, f(res_of_func), iters, time, '0')
        print('├─────┼──────────┼────────────┼────────┼──────────┼──────────┤')
        print(s)
    except Exception as e:
        if str(e) == 'f(a) and f(b) must have different signs':
            continue
        elif str(e) == 'rtol too small ('+s_eps+' < 8.88178e-16)' or\
             str(e) == 'Failed to converge after '+str(max_iter)+' iterations.':
            print('├─────┼──────────┼────────────┼────────┼──────────┼────'\
                  +'──────┤')
            s = '│{:^5d}│{:^10s}│{:^12s}│{:^8s}│{:^10s}│{:^10s}│'.format(\
                i+1, '-', '-', '-', '-', '101')
            print(s)
            
        
print('└─────┴──────────┴────────────┴────────┴──────────┴──────────┘')
