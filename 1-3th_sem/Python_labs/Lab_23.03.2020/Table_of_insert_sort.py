from tkinter import *
import tkinter.messagebox as mb
import matplotlib.pyplot as plt
import time
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np


def barier_insert_sort(A):
    L = np.insert(A, 0, A[0])
    N = len(L)
    j = 0
    for i in range(2, N):
        if L[i - 1] > L[i]:
            L[0] = L[i]
            j = i - 1
            while L[j] > L[0]:
                L[j + 1] = L[j]
                j -= 1
        L[j + 1] = L[0]
    L = np.delete(L, 0)
    return L


def clock_mass(A):
    t = time.perf_counter()
    barier_insert_sort(A)
    return time.perf_counter() - t


def string_mass(L):
    s = ''
    for i in range(len(L)):
        if i < len(L) - 1:
            s += str(L[i]) + ' '
        else:
            s += str(L[i])
    return s


def get_data():
    if int(a_field.get()) * int(b_field.get()) * int(N1_field.get()) \
            * int(N2_field.get()) * int(N3_field.get()) > 0 \
            and int(a_field.get()) < int(b_field.get()):
        root = Tk()
        root.title('Данные о сортировке вставками с барьером')
        root.geometry('550x570')
        Table_label = Label(root, text='Таблица зависимости времени сортировки от длины и вида массива',
                            font='Arial 12')
        Table_label.place(x=5, y=5)
        Table_frame = Frame(root)
        Table_frame.place(x=45, y=35)

        N_a = int(a_field.get())
        N_b = int(b_field.get())
        N1 = int(N1_field.get())
        N2 = int(N2_field.get())
        N3 = int(N3_field.get())

        sectors = np.linspace(N_a, N_b, 10, True, dtype=np.int_)

        Rand_L1 = np.random.randint(-N1, N1 + 1, N1)
        Rand_L2 = np.random.randint(-N2, N2 + 1, N2)
        Rand_L3 = np.random.randint(-N3, N3 + 1, N3)

        Ord_L1 = np.linspace(-N1, N1, N1, endpoint=True, dtype=np.int_)
        Ord_L2 = np.linspace(-N2, N2, N2, endpoint=True, dtype=np.int_)
        Ord_L3 = np.linspace(-N3, N3, N3, endpoint=True, dtype=np.int_)

        Rev_ord_L1 = np.flip(Ord_L1)
        Rev_ord_L2 = np.flip(Ord_L2)
        Rev_ord_L3 = np.flip(Ord_L3)

        # Таблица
        type_label = Label(Table_frame, bd=2, text='Вид массива', relief='solid',
                           font='Arial 10', width=12)
        type_label.grid(row=0, column=0)
        n1 = Label(Table_frame, bd=2, text='N1 = ' + str(N1), relief='solid',
                   font='Arial 10', width=12)
        n1.grid(row=0, column=1)
        n2 = Label(Table_frame, bd=2, text='N2 = ' + str(N2), relief='solid',
                   font='Arial 10', width=12)
        n2.grid(row=0, column=2)
        n3 = Label(Table_frame, bd=2, text='N3 = ' + str(N3), relief='solid',
                   font='Arial 10', width=12)
        n3.grid(row=0, column=3)

        r1 = Label(Table_frame, bd=2, text='Упорядоченный\nмассив',
                   relief='solid', font='Arial 10', width=12)
        r1.grid(row=1, column=0)
        r2 = Label(Table_frame, bd=2, text='Случайный\nмассив',
                   relief='solid', font='Arial 10', width=12)
        r2.grid(row=2, column=0)
        r3 = Label(Table_frame, bd=2,
                   text='Упорядоченный\nв обратном\nпорядке',
                   relief='solid', font='Arial 10', width=12)
        r3.grid(row=3, column=0)

        Rand_L1_t = clock_mass(Rand_L1)
        Rand_L2_t = clock_mass(Rand_L2)
        Rand_L3_t = clock_mass(Rand_L3)

        Ord_L1_t = clock_mass(Ord_L1)
        Ord_L2_t = clock_mass(Ord_L2)
        Ord_L3_t = clock_mass(Ord_L3)

        Rev_ord_L1_t = clock_mass(Rev_ord_L1)
        Rev_ord_L2_t = clock_mass(Rev_ord_L2)
        Rev_ord_L3_t = clock_mass(Rev_ord_L3)

        r1n1 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Ord_L1_t),
                     relief='solid', font='Arial 10', width=12, height=2)
        r1n1.grid(row=1, column=1)
        r1n2 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Ord_L2_t),
                     relief='solid', font='Arial 10', width=12, height=2)
        r1n2.grid(row=1, column=2)
        r1n3 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Ord_L3_t),
                     relief='solid', font='Arial 10', width=12, height=2)
        r1n3.grid(row=1, column=3)

        r2n1 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Rand_L1_t),
                     relief='solid', font='Arial 10', width=12, height=2)
        r2n1.grid(row=2, column=1)
        r2n2 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Rand_L2_t),
                     relief='solid', font='Arial 10', width=12, height=2)
        r2n2.grid(row=2, column=2)
        r2n3 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Rand_L3_t),
                     relief='solid', font='Arial 10', width=12, height=2)
        r2n3.grid(row=2, column=3)

        r3n1 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Rev_ord_L1_t),
                     relief='solid', font='Arial 10', width=12, height=3)
        r3n1.grid(row=3, column=1)
        r3n2 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Rev_ord_L2_t),
                     relief='solid', font='Arial 10', width=12, height=3)
        r3n2.grid(row=3, column=2)
        r3n3 = Label(Table_frame, bd=2, text='{:.7g} с'.format(Rev_ord_L3_t),
                     relief='solid', font='Arial 10', width=12, height=3)
        r3n3.grid(row=3, column=3)

        t_n = [0.0] * 10
        for i in range(10):
            t_n[i] = clock_mass(np.random.randint(-sectors[i], sectors[i] + 1, sectors[i]))

        # Окно с графиком
        Plt_frame = Frame(root)
        Plt_frame.place(x=5, y=200)
        figure = plt.Figure(figsize=(6, 4), dpi=90)
        ax = figure.add_subplot(111)
        chart_type = FigureCanvasTkAgg(figure, Plt_frame)
        chart_type.get_tk_widget().pack()
        ax.plot(sectors, t_n, label='t(N)')
        ax.grid(axis='both')
        figure.text(0.5, 0.025, 'Длина массива N', ha='center')
        figure.text(0.025, 0.5, 'Время сортировки t(N), с', va='center', rotation='vertical')
        ax.set_title('Зависимость времени сортировки от длины массива')
        figure.add_axes()
        ax.legend(fontsize=10)

        root.mainloop()
    else:
        mb.showerror('Ошибка', 'Введите корректные данные!')
        a_field.delete(0, END)
        b_field.delete(0, END)
        N1_field.delete(0, END)
        N2_field.delete(0, END)
        N3_field.delete(0, END)


# Начальное окно
Entry_Data = Tk()
Entry_Data.title('Ввод данных')
Entry_Data.geometry('300x215')

demo_label = Label(Entry_Data, text='Демонстрационный массив:')
demo_label.place(x=70, y=5)
demo_sort_label = Label(Entry_Data, text='Отсортированная версия:')
demo_sort_label.place(x=70, y=50)

L = np.random.randint(0, 1001, 10)
demo_mass = Label(Entry_Data, text=string_mass(L), relief='solid', width=30, bd=1)
demo_mass.place(x=45, y=25)
L = barier_insert_sort(L)
demo_sort_mass = Label(Entry_Data, text=string_mass(L), relief='solid', width=30, bd=1)
demo_sort_mass.place(x=45, y=70)

section_label = Label(Entry_Data, text='Введите отрезок размерностей:')
section_label.place(x=60, y=95)

a_label = Label(Entry_Data, text='Начало:')
a_label.place(x=30, y=115)
a_field = Entry(Entry_Data, width=10)
a_field.place(x=80, y=115)

b_label = Label(Entry_Data, text='Конец:')
b_label.place(x=155, y=115)
b_field = Entry(Entry_Data, width=10)
b_field.place(x=197, y=115)

N1N2N3_label = Label(Entry_Data, text='Введите размерности массивов N1, N2, N3:')
N1N2N3_label.place(x=30, y=140)

N1_label = Label(Entry_Data, text='N1 =')
N1_label.place(x=2, y=160)
N1_field = Entry(Entry_Data, width=10)
N1_field.place(x=32, y=160)

N2_label = Label(Entry_Data, text='N2 =')
N2_label.place(x=102, y=160)
N2_field = Entry(Entry_Data, width=10)
N2_field.place(x=132, y=160)

N3_label = Label(Entry_Data, text='N3 =')
N3_label.place(x=202, y=160)
N3_field = Entry(Entry_Data, width=10)
N3_field.place(x=232, y=160)

entry_but = Button(Entry_Data, text='Ввод', width=10, command=get_data)
entry_but.place(x=100, y=185)

Entry_Data.mainloop()
###
