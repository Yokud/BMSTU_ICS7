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
import matplotlib.pyplot as plt
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox as mb
import timeit
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg


def getData():
    if float(a_field.get()) >= float(b_field.get()) or float(h_field.get())\
            > float(b_field.get()) - float(a_field.get()) or\
            float(h_field.get()) <= 0 or float(eps_field.get()) <= 0 or\
            int(max_iter_field.get()) <= 0:
        mb.showerror('Ошибка', 'Неверные данные!')
        a_field.delete(0, tk.END)
        b_field.delete(0, tk.END)
        h_field.delete(0, tk.END)
        eps_field.delete(0, tk.END)
        max_iter_field.delete(0, tk.END)
    else:
        a = float(a_field.get())
        b = float(b_field.get())
        h = float(h_field.get())
        global eps
        eps = float(eps_field.get())
        global max_iter
        max_iter = int(max_iter_field.get())
        pointnum = 10*int(b-a) + 10

        Data_window = tk.Tk()
        Data_window.geometry('1250x650')
        Data_window.title('Данные')

        # Таблица ошибок
        Errors_frame = tk.Frame(Data_window)
        Errors_frame.place(x=5, y=5)
        Errors_label = tk.Label(Errors_frame, text='Таблица ошибок',
                                bg='white', borderwidth=1,
                                relief='solid').pack(expand=1, anchor=tk.NW,
                                                     fill=tk.X)
        Errors_tree = ttk.Treeview(Errors_frame)
        Errors_tree['columns'] = ('#1')
        Errors_tree.column('#0', width=75, stretch=tk.NO, anchor=tk.CENTER)
        Errors_tree.column('#1', width=200, stretch=tk.NO, anchor=tk.CENTER)

        Errors_tree.heading('#0', text='Код ошибки', anchor=tk.CENTER)
        Errors_tree.heading('#1', text='Расшифровка', anchor=tk.CENTER)

        Errors_tree.insert('', 1, text='0', values=('Ошибок нет',))
        Errors_tree.insert('', 2, text='101',
                           values=('Превышено число итераций',))

        Errors_tree.config(height=2)
        Errors_tree.pack(side=tk.TOP, fill=tk.X)
        ###

        # Таблица с корнями метода половинного деления собственной разработки
        My_bisect_frame = tk.Frame(Data_window)
        My_bisect_frame.place(x=5, y=100)
        My_bisect_label = tk.Label(My_bisect_frame,
                        text='Метод половинного деления собственной разработки',
                        bg='white', borderwidth=1,
                        relief='solid').pack(expand=1, anchor=tk.NW, fill=tk.X)
        My_bisect_tree = ttk.Treeview(My_bisect_frame)
        My_bisect_tree['columns'] = ('#1', '#2', '#3', '#4', '#5', '#6')
        My_bisect_tree.column('#0', width=40, stretch=tk.NO, anchor=tk.CENTER)
        My_bisect_tree.column('#1', width=80, stretch=tk.NO, anchor=tk.CENTER)
        My_bisect_tree.column('#2', width=80, stretch=tk.NO, anchor=tk.CENTER)
        My_bisect_tree.column('#3', width=80, stretch=tk.NO, anchor=tk.CENTER)
        My_bisect_tree.column('#4', width=65, stretch=tk.NO, anchor=tk.CENTER)
        My_bisect_tree.column('#5', width=65, stretch=tk.NO, anchor=tk.CENTER)
        My_bisect_tree.column('#6', width=60, stretch=tk.NO, anchor=tk.CENTER)

        My_bisect_tree.heading('#0', text='№', anchor=tk.CENTER)
        My_bisect_tree.heading('#1', text='Отрезок', anchor=tk.CENTER)
        My_bisect_tree.heading('#2', text='Корень x', anchor=tk.CENTER)
        My_bisect_tree.heading('#3', text='Значение f(x)', anchor=tk.CENTER)
        My_bisect_tree.heading('#4', text='Итерации', anchor=tk.CENTER)
        My_bisect_tree.heading('#5', text='Время',
                               anchor=tk.CENTER)
        My_bisect_tree.heading('#6', text='Код', anchor=tk.CENTER)

        global args
        args = np.arange(a, b+h, h)

        if args[-1] > b:
            args[-1] = b

        Roots1 = list()
        Zeros1 = list()
        global i
        rows_column = 0
        for i in range(len(args) - 1):
            res_of_func = bisect(f, args[i], args[i+1], eps, max_iter)
            section = '[' + str(args[i]) + '; ' + str(args[i + 1]) + ']'

            try:
                root = '{:.7g}'.format(res_of_func[0])
                zero = '{:.0e}'.format(f(res_of_func[0])) if f(res_of_func[0])\
                       != 0 else '0'
                Roots1.append(res_of_func[0])
                Zeros1.append(f(res_of_func[0]))
                iters = res_of_func[1]
                code = res_of_func[2]
                time = timeit.timeit('bisect(f, args[i], args[i+1], eps,'+
                                     ' max_iter)',
                                     setup='from __main__ import bisect, f,'+
                                     ' args, eps, max_iter, i', number=1)
                timef = '{:.3g}'.format(time)
                My_bisect_tree.insert('', i+1, text=str(i+1),
                                      values=(section,root, zero,iters, timef,
                                              code))
                rows_column += 1
            except:
                if res_of_func is None:
                    continue
                else:
                    My_bisect_tree.insert('', 'end', text=str(i + 1),
                                          values=(section, '-', '-', '-',
                                                  '-', res_of_func))
                    rows_column += 1

        if rows_column >= 10:
            scrollbar1 = tk.Scrollbar(My_bisect_frame)
            scrollbar1.pack(side=tk.RIGHT, fill=tk.Y)
            scrollbar1.config(command=My_bisect_tree.yview)
            My_bisect_tree.config(height=10, yscrollcommand=scrollbar1.set)
        else:
            My_bisect_tree.config(height=rows_column)

        My_bisect_tree.pack(side=tk.TOP, fill=tk.X)
        ###

        # Таблица с корнями метода половинного деления из библиотеки Scipy
        Scipy_bisect_frame = tk.Frame(Data_window)
        Scipy_bisect_frame.place(x=5, y=380)
        Scipy_bisect_label = tk.Label(Scipy_bisect_frame,
                                      text='Метод половинного деления из'+
                                      ' библиотеки Scipy',
                                      bg='white', borderwidth=1, relief='solid').pack(expand=1, anchor=tk.NW, fill=tk.X)
        Scipy_bisect_tree = ttk.Treeview(Scipy_bisect_frame)
        Scipy_bisect_tree['columns'] = ('#1', '#2', '#3', '#4', '#5', '#6')
        Scipy_bisect_tree.column('#0', width=40, stretch=tk.NO,
                                 anchor=tk.CENTER)
        Scipy_bisect_tree.column('#1', width=80, stretch=tk.NO,
                                 anchor=tk.CENTER)
        Scipy_bisect_tree.column('#2', width=80, stretch=tk.NO,
                                 anchor=tk.CENTER)
        Scipy_bisect_tree.column('#3', width=80, stretch=tk.NO,
                                 anchor=tk.CENTER)
        Scipy_bisect_tree.column('#4', width=65, stretch=tk.NO,
                                 anchor=tk.CENTER)
        Scipy_bisect_tree.column('#5', width=65, stretch=tk.NO,
                                 anchor=tk.CENTER)
        Scipy_bisect_tree.column('#6', width=60, stretch=tk.NO,
                                 anchor=tk.CENTER)

        Scipy_bisect_tree.heading('#0', text='№', anchor=tk.CENTER)
        Scipy_bisect_tree.heading('#1', text='Отрезок', anchor=tk.CENTER)
        Scipy_bisect_tree.heading('#2', text='Корень x', anchor=tk.CENTER)
        Scipy_bisect_tree.heading('#3', text='Значение f(x)', anchor=tk.CENTER)
        Scipy_bisect_tree.heading('#4', text='Итераций',
                                  anchor=tk.CENTER)
        Scipy_bisect_tree.heading('#5', text='Время',
                                  anchor=tk.CENTER)
        Scipy_bisect_tree.heading('#6', text='Код', anchor=tk.CENTER)

        Roots2 = list()
        Zeros2 = list()
        rows_column = 0
        for i in range(len(args) - 1):
            section = '[' + str(args[i]) + '; ' + str(args[i + 1]) + ']'

            try:
                res_of_func, rootRes = optimize.bisect(f, args[i], args[i + 1], rtol=eps, maxiter=max_iter,
                                                       full_output=True)
                time = timeit.timeit('bisect(f, args[i], args[i+1], rtol = eps,' \
                                     + ' maxiter = max_iter)',
                                     setup='from scipy.optimize import bisect;'
                                     + ' from __main__ import f, args, eps, '
                                     +'max_iter, i', number=1)
                root = '{:.7g}'.format(res_of_func)
                zero = '{:.0e}'.format(f(res_of_func)) if f(res_of_func) != 0\
                       else '0'
                iters = rootRes.iterations if zero != '0' else 1
                code = '0'
                timef = '{:.3g}'.format(time)
                Scipy_bisect_tree.insert('', i + 1, text=str(i + 1),
                                         values=(section, root, zero, iters,
                                                 timef, code))
                Roots2.append(res_of_func)
                Zeros2.append(f(res_of_func))
                rows_column += 1
            except Exception as e:
                if str(e) == 'f(a) and f(b) must have different signs':
                    continue
                elif str(e) == 'rtol too small (' + str(eps)\
                                +' < 8.88178e-16)' or \
                    str(e) == 'Failed to converge after ' + str(max_iter)\
                    + ' iterations.':
                    Scipy_bisect_tree.insert('', i + 1, text=str(i + 1),
                                             values=(section, '-', '-', '-',
                                                     '-', '101'))
                    rows_column += 1

        if rows_column >= 10:
            scrollbar2 = tk.Scrollbar(Scipy_bisect_frame)
            scrollbar2.pack(side=tk.RIGHT, fill=tk.Y)
            scrollbar2.config(command=Scipy_bisect_tree.yview)
            Scipy_bisect_tree.config(height=10, yscrollcommand=scrollbar2.set)
        else:
            Scipy_bisect_tree.config(height=rows_column)

        Scipy_bisect_tree.pack(side=tk.TOP, fill=tk.X)
        ###

        # Окно с графиком
        Plt_frame = tk.Frame(Data_window)
        Plt_frame.place(x=510, y=5)
        figure = plt.Figure(figsize=(7, 6), dpi=100)
        ax = figure.add_subplot(111)
        chart_type = FigureCanvasTkAgg(figure, Plt_frame)
        chart_type.get_tk_widget().pack()
        x = np.linspace(a, b, pointnum, endpoint=True)
        y = f(x)
        ax.plot(x, y, label='f(x)')
        ax.grid(axis='both')
        figure.text(0.5, 0.04, 'X', ha='center')
        figure.text(0.04, 0.5, 'Y', va='center', rotation='vertical')
        xextrs = extremums(x)
        ax.scatter(xextrs, f(xextrs), c='m', label='Extremums', s = 30)
        if len(Roots1) >= len(Roots2):
            ax.scatter(Roots1, Zeros1, c='r', label='Roots', s = 30)
        else:
            ax.scatter(Roots2, Zeros2, c='r', label='Roots', s = 30)
        ax.set_title('Roots and Extremums')
        figure.add_axes()
        ax.legend(fontsize=10)
        ###

        Data_window.mainloop()


def f(x):
    return np.sin(x)


def bisect(f, a, b, eps, maxiter):
    start, end = a, b
    if f(a)*f(b) > 0:
        return None     # Корня нет
    if f(a) == 0:
        return a, 1, '0'
    elif f(b) == 0:
        return b, 1, '0'
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
        return '101'  # Превышено число итераций
    else:
        return x, iters, '0'


def extremums(X):
    M = list()
    for i in range(1, len(X) - 1):
        if f(X[i-1]) < f(X[i]) > f(X[i+1]) or f(X[i-1]) > f(X[i]) < f(X[i+1]):
            M.append(X[i])
    return M


Entry_Data = tk.Tk()
Entry_Data.title('Ввод')
Entry_Data.geometry('240x150')

a_label = tk.Label(Entry_Data, text='Начало отрезка:')
a_label.grid(row=0, column=0, sticky=tk.W)
a_field = tk.Entry(Entry_Data, width=15)
a_field.grid(row=0, column=1, sticky=tk.W)

b_label = tk.Label(Entry_Data, text='Конец отрезка:')
b_label.grid(row=1, column=0, sticky=tk.W)
b_field = tk.Entry(Entry_Data, width=15)
b_field.grid(row=1, column=1, sticky=tk.W)

h_label = tk.Label(Entry_Data, text='Шаг:')
h_label.grid(row=2, column=0, sticky=tk.W)
h_field = tk.Entry(Entry_Data, width=15)
h_field.grid(row=2, column=1, sticky=tk.W)

eps_label = tk.Label(Entry_Data, text='Точность:')
eps_label.grid(row=3, column=0, sticky=tk.W)
eps_field = tk.Entry(Entry_Data, width=15)
eps_field.grid(row=3, column=1, sticky=tk.W)

max_iter_label = tk.Label(Entry_Data, text='Макс. число итераций:')
max_iter_label.grid(row=4, column=0, sticky=tk.W)
max_iter_field = tk.Entry(Entry_Data, width=15)
max_iter_field.grid(row=4, column=1, sticky=tk.W)

entr = tk.Button(Entry_Data, text='Ввод данных', command=getData)
entr.grid(row=5, column=1, sticky=tk.W)

Entry_Data.mainloop()
