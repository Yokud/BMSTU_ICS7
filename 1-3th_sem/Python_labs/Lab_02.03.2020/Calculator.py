from tkinter import *
import tkinter.messagebox as mb


def dec_to_bin(x):
    module_x = None
    sign = x[0]
    if sign == '-':
        module_x = x[1:]
    else:
        module_x = x
        sign = ''
    xib = ''
    xrb = ''
    ix = int(float(module_x))
    rx = float(module_x) - ix
    while ix > 0:
        xib += str(ix % 2)
        ix //= 2
    while rx > 1e-6 and len(xrb) <= 6:
        xrb += str(int(rx * 2))
        rx = 2 * rx - int(rx * 2)
    
    xb = sign + xib[::-1] + '.' + xrb if xrb != '' else sign + xib[::-1]
    
    return xb


def bin_to_dec(xb):
    module_xb = None
    sign = xb[0]
    if sign == '-':
        module_xb = xb[1:]
        sign = -1
    else:
        module_xb = xb
        sign = 1
    xid = 0
    xrd = 0
    xib = int(float(module_xb))
    xrb = ''
    flag = 0
    for i in range(len(module_xb)):
        if module_xb[i] == '.': flag = 1
        elif flag: xrb += module_xb[i]
        
    n = 1
    while xib != 0:
        xid += (xib % 10) * n
        n *= 2
        xib //= 10

    n = 0.5
    for i in range(len(xrb)):
        xrd += n * int(xrb[i])
        n /= 2

    xd = xid + xrd
    return sign * xd

def checker_to_bin():
    s = entry_field.get()
    if isreal(s):
        x = dec_to_bin(s)
        res_field.config(state=NORMAL)
        res_field.delete(0, END)
        res_field.insert(0, x)
        res_field.config(state=DISABLED)
    else:
        mb.showerror('Ошибка', 'Введите корректные данные!')
        entry_field.delete(0, END)

def isbin(s):
    for i in range(len(s)):
        if s[i] == '0' or s[i] == '1' or s[i] == '.'\
        or s[i] == '-' and (s[i+1] == '1' or s[i+1] == '0'):
            continue
        else: return False
    return True

def isreal(s):
    for i in range(len(s)):
        if s[i].isdigit() or s[i] == '.'\
           or s[i] == '-' and s[i+1].isdigit():
            pass
        else:
            return False
    return True


def checker_to_dec():
    s = entry_field.get()
    if isbin(s):
        x = bin_to_dec(s)
        res_field.config(state=NORMAL)
        res_field.delete(0, END)
        res_field.insert(0, '{:.6g}'.format(x))
        res_field.config(state=DISABLED)
    else:
        mb.showerror('Ошибка', 'Введите корректные данные!')
        entry_field.delete(0, END)


def inf():
    s = '''Переводчик чисел из десятеричной системы счисления
в двоичную и обратно
    
Создатель:
Малышев Иван ИУ7-21Б'''
    mb.showinfo('О программе и об авторе', s)


def enter1():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '1')

def enter2():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '2')

def enter3():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '3')

def enter4():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '4')

def enter5():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '5')

def enter6():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '6')

def enter7():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '7')

def enter8():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '8')

def enter9():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '9')

def enter0():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '0')

def enterp():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '.')

def enterminus():
    if len(entry_field.get()) <= 16: entry_field.insert(END, '-')
    

def clear():
    entry_field.delete(0, END)
    res_field.config(state=NORMAL)
    res_field.delete(0, END)
    res_field.config(state=DISABLED)

def back():
    s = entry_field.get()
    entry_field.delete(0, END)
    entry_field.insert(END, s[:-1])

def _exit():
    main_window.destroy()

main_window = Tk()
main_window.title('Калькулятор')
main_window.geometry('350x350')

mainmenu = Menu(main_window)
main_window.config(menu=mainmenu)
mainmenu.add_command(label='Справка',command = inf)
mainmenu.add_command(label='Очистка',command = clear)
mainmenu.add_command(label='Возврат',command = back)
mainmenu.add_command(label='Выход',command = _exit)
mainmenu.add_command(label='Перевод в двоичную СС',command = checker_to_bin)
mainmenu.add_command(label='Перевод в десятеричную СС',command = checker_to_dec)

res_label = Label(main_window, text = 'Result:')
res_label.place(x=0, y=10)

res_field = Entry(main_window, font = ('Arial', 24), width = 16, state=DISABLED)
res_field.place(x=40, y=10)

entry_field = Entry(main_window, font = ('Arial', 24), width = 18, justify=RIGHT)
entry_field.place(x=5, y=60)

but_1 = Button(main_window, padx = 10, pady = 10, font='10', text = '1',
               command=enter1)
but_1.place(x=5, y = 105)
but_2 = Button(main_window, padx = 10, pady = 10, font='10',text = '2',
               command=enter2)
but_2.place(x=55, y = 105)
but_3 = Button(main_window, padx = 10, pady = 10, font='10',text = '3',
               command=enter3)
but_3.place(x=105, y = 105)
but_4 = Button(main_window, padx = 10, pady = 10, font='10',text = '4',
               command=enter4)
but_4.place(x=5, y = 160)
but_5 = Button(main_window, padx = 10, pady = 10, font='10',text = '5',
               command=enter5)
but_5.place(x=55, y = 160)
but_6 = Button(main_window, padx = 10, pady = 10, font='10',text = '6',
               command=enter6)
but_6.place(x=105, y = 160)
but_7 = Button(main_window, padx = 10, pady = 10, font='10',text = '7',
               command=enter7)
but_7.place(x=5, y = 215)
but_8 = Button(main_window, padx = 10, pady = 10, font='10',text = '8',
               command=enter8)
but_8.place(x=55, y = 215)
but_9 = Button(main_window, padx = 10, pady = 10, font='10',text = '9',
               command=enter9)
but_9.place(x=105, y = 215)
but_0 = Button(main_window, padx = 10, pady = 10, font='10',text = '0',
               command=enter0)
but_0.place(x=55, y = 270)

but_p = Button(main_window, padx = 12.49, pady = 10, font='10', text = '.',
               command=enterp)
but_p.place(x=105, y=270)

but_minus = Button(main_window, padx = 12, pady = 10, font='10',text = '-',
               command=enterminus)
but_minus.place(x=5, y=270)

but_c = Button(main_window, padx = 10, pady = 10, font='10',text = 'C',
               command=clear)
but_c.place(x=185, y=105)

but_back = Button(main_window, padx = 10, pady = 10, font='10',text = 'Back',
               command=back)
but_back.place(x=240, y =105)

but_to_b = Button(main_window, padx = 24, pady = 10, font='10',
                  text = '10 >>> 2', command=checker_to_bin)
but_to_b.place(x=185, y=165)

but_to_d = Button(main_window, padx = 24, pady = 10, font='10',
                  text = '2 >>> 10', command=checker_to_dec)
but_to_d.place(x=185, y=225)
