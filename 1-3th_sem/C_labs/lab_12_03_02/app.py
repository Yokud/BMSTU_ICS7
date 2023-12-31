import sys
sys.path.append('py/')
from arr_lib import *

import tkinter as tk
import tkinter.messagebox as mbox
import tkinter.filedialog as fd
import tkinter.simpledialog as sd


def is_int(num_str):
    if len(num_str) == 0:
        return False
    
    return num_str.isdigit() or (num_str[0] == '-' and num_str[1:].isdigit())


def add_item():
    if is_int(entry.get()):
        arr_listbox.insert(tk.END, entry.get())
    else:
        mbox.showwarning(title="Ошибка", message="Введенные данные не являются числом")
    entry.delete(0, tk.END)
 
 
def del_list():
    select = list(arr_listbox.curselection())
    select.reverse()
    for i in select:
        arr_listbox.delete(i)
 
 
def save_list():
    filename = fd.asksaveasfilename(defaultextension=".txt",
                                    filetypes=(("TXT files", "*.txt"),
                                               ("HTML files", "*.html;*.htm"),
                                               ("All files", "*.*")))
    f = open(filename, 'w')
    f.writelines("\n".join(arr_listbox.get(0, tk.END)))
    f.close()


def clear_list():
    arr_listbox.delete(0,tk.END)


def fill_list():
    prime_count = sd.askinteger("Диалоговое окно", "Введите кол-во простых чисел")

    if prime_count > 0:
        arr_listbox.delete(0,tk.END)
        prime_arr = fill_array_by_prime_nums(prime_count)

        for num in prime_arr:
            arr_listbox.insert(tk.END, str(num))
    else:
        mbox.showwarning(title="Ошибка", message="Введен неверный размер массива")


def filter_list():
    nums = list(map(int, arr_listbox.get(0, tk.END)))
    res = create_array_with_elems_after_even(nums)

    filename = fd.asksaveasfilename(defaultextension=".txt",
                                    filetypes=(("TXT files", "*.txt"),
                                               ("HTML files", "*.html;*.htm"),
                                               ("All files", "*.*")))
    f = open(filename, 'w')
    f.writelines("\n".join([str(num) for num in res]))
    f.close()


main_window = tk.Tk()
main_window.title("PPAP - Python Proccessing Array Programm")
main_window.geometry("410x280")

f_main = tk.Frame(main_window)
f_main.pack(anchor=tk.NW, padx=20, pady=5)

f_list = tk.LabelFrame(f_main, text='Массив')
arr_listbox = tk.Listbox(f_list, width = 25, height = 15, bd = 1, relief='solid')
arr_listbox.pack(side=tk.LEFT, fill=tk.Y)
scroll = tk.Scrollbar(f_list, command=arr_listbox.yview)
scroll.pack(side=tk.RIGHT, fill=tk.Y)
arr_listbox.config(yscrollcommand=scroll.set)
f_list.pack(side=tk.LEFT)

f_buttons = tk.Frame(f_main)
entry = tk.Entry(f_buttons, width=28, bd = 2, relief='solid')
entry.pack(anchor=tk.N)
tk.Button(f_buttons, width=24, bd = 1, relief='solid', text="Добавить в массив", command=add_item).pack(padx=10, pady=3, fill=tk.X)
tk.Button(f_buttons, width=24, bd = 1, relief='solid', text="Удалить из массива", command=del_list).pack(padx=10, pady=3, fill=tk.X)
tk.Button(f_buttons, width=24, bd = 1, relief='solid', text="Сохранить массив в файл", command=save_list).pack(padx=10, pady=3, fill=tk.X)
tk.Button(f_buttons, width=24, bg = '#cf1a1b', fg = 'white', bd = 1, relief='solid', text="Очистить массив", command=clear_list).pack(padx=10, pady=5, fill=tk.X)
tk.Button(f_buttons, width=24, bg = '#0091fe', fg = 'white', bd = 1, relief='solid', text="Заполнить массив\nпростыми числами", command=fill_list).pack(padx=10, pady=3, fill=tk.X)
tk.Button(f_buttons, width=24, bg = '#0091fe', fg = 'white', bd = 1, relief='solid', text="Выписать элем-ты массива,\nидущие после чётных, в файл", command=filter_list).pack(padx=10, pady=3, fill=tk.X)

f_buttons.pack(pady=10)

main_window.mainloop()
