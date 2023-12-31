from tkinter import *
import tkinter.messagebox as mb
import math


def geometric_center(dots):
    p1 = dots[0]
    p2 = dots[1]
    max_distance = math.hypot(dots[0][0] - dots[1][0], dots[0][1] - dots[1][1])
    n = len(dots)

    if not n:
        return 0, 0

    for i in range(n):
        for j in range(n):
            distance = math.hypot(dots[i][0] - dots[j][0],
                                  dots[i][1] - dots[j][1])
            if distance > max_distance:
                max_distance = distance
                p1 = dots[i]
                p2 = dots[j]

    return (p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2


def get_point(dots):
    eps = 1e-8
    if isfloat(x_entry.get()) and isfloat(y_entry.get()):
        x = float(x_entry.get())
        y = float(y_entry.get())
        if abs(x) <= field_width and abs(y) <= field_height:
            dots.append((x, y))
            field.create_oval(x - eps + field_width, field_height - y - eps,
                              x + eps + field_width, field_height - y + eps,
                              width=5, outline='blue')
        else:
            mb.showerror('Неверные значения', 'Координаты точки не соответсвуют'
                                              ' условию')
    else:
        mb.showerror('Ошибка ввода данных', 'Введите корректные данные!')

    x_entry.delete(0, END)
    y_entry.delete(0, END)


def get_the_farthest_point_and_radius(dots, central_point):
    if not len(dots):
        return (0, 0), 0

    farthest_point = dots[0]
    max_distance = math.hypot(central_point[0] - farthest_point[0],
                              central_point[1] - farthest_point[1])
    for p in dots:
        distance = math.hypot(central_point[0] - p[0], central_point[1] - p[1])
        if distance > max_distance:
            max_distance = distance
            farthest_point = p
    return farthest_point, max_distance


def draw_grid_and_axises(canvas, line_distance):
    field.create_line(0, field_height, canvas_width, field_height,
                      width=3, arrow=LAST)  # X
    field.create_line(field_width, 0, field_width, canvas_height,
                      width=3, arrow=FIRST)  # Y
    for x in range(line_distance, canvas_width, line_distance):
        canvas.create_line(x, 0, x, canvas_height, fill='grey')
        if x - field_width:
            canvas.create_text(x, field_height + 8,
                               text=str(x - field_width),
                               font='Arial 6', justify=CENTER, fill='black')

    for y in range(line_distance, canvas_height, line_distance):
        canvas.create_line(0, y, canvas_width, y, fill='grey')
        if y - field_height:
            canvas.create_text(field_width + 8, y,
                               text=str(y - field_height),
                               font='Arial 6', justify=CENTER, fill='black')
    canvas.create_text(canvas_width - 5, field_height + 10, text='X')
    canvas.create_text(field_width + 8, 8, text='Y')


def paint_point(event):
    eps = 1e-8

    x1, y1 = event.x - eps, event.y - eps
    x2, y2 = event.x + eps, event.y + eps
    field.create_oval(x1, y1, x2, y2, outline='blue', width=6)
    points.append((event.x - field_width, field_height - event.y))


def isfloat(s):
    try:
        float(s)
    except ValueError:
        return False
    return True


def calculate(dots):
    eps = 1e-8

    if not len(dots):
        mb.showerror('Ошибка ввода', 'Не введена ни одна точка')
        return 0

    central_point = geometric_center(dots)
    farthest_point_and_radius = get_the_farthest_point_and_radius(dots,
                                                                  central_point)
    farthest_point = farthest_point_and_radius[0]
    radius = farthest_point_and_radius[1]

    field.create_oval(central_point[0] - eps + field_width,
                      field_height - central_point[1] - eps,
                      central_point[0] + eps + field_width,
                      field_height - central_point[1] + eps,
                      outline='green', width=9)
    field.create_line(central_point[0] + field_width,
                      field_height - central_point[1],
                      farthest_point[0] + field_width,
                      field_height - farthest_point[1], fill='red', width=3)
    field.create_oval(central_point[0] - radius + field_width,
                      field_height - central_point[1] - radius,
                      central_point[0] + radius + field_width,
                      field_height - central_point[1] + radius,
                      outline='light green', width=3)

    data_text = Label(main_window, relief='solid', width=18, justify=LEFT,
                      anchor=W, font='Arial 9', text='Данные'.rjust(18) +
                      '\n\nЦентр: ' + '{:.4g}, {:.4g}'.format(central_point[0],
                                                              central_point[1])
                      + '\nРадиус: ' + '{:.4g}'.format(radius) +
                      '\nПлощадь: ' + '{:.4g}'.format(math.pi * radius
                                                      * radius))
    data_text.place(x=515, y=250)
    entry_p_but.config(state=DISABLED)
    entry_but.config(state=DISABLED)
    field.unbind('<Button-1>')

    def destroy_all():
        field.delete('all')
        clear_but.destroy()
        data_text.destroy()
        points.clear()

        draw_grid_and_axises(field, int(field_width / 10))
        entry_p_but.config(state=NORMAL)
        entry_but.config(state=NORMAL)
        field.bind('<Button-1>', paint_point)

    clear_but = Button(main_window, text='Очистить', width=15, relief='solid',
                       command=destroy_all)
    clear_but.place(x=530, y=420)


points = list()

main_window = Tk()
main_window.title('Поиск центра и радиуса круга мин. площади, '
                  'охватывающий все точки на плоскости')
main_window.geometry('650x510')

canvas_width = 500
canvas_height = 500

field_width = int(canvas_width / 2)
field_height = int(canvas_height / 2)

field = Canvas(main_window, width=canvas_width, height=canvas_height,
               bg='white')
field.place(x=5, y=5)
field.bind('<Button-1>', paint_point)

draw_grid_and_axises(field, int(field_width / 10))

enter_points_label = Label(main_window,
                           text='Ввести\nкоординаты точки\nс клавиатуры',
                           width=15, relief='solid')
enter_points_label.place(x=530, y=5)

cond_label = Label(main_window, text='|x|, |y| <= ' + str(field_width),
                   justify=CENTER, width=15)
cond_label.place(x=530, y=60)

x_label = Label(main_window, text='x:')
x_label.place(x=530, y=80)
x_entry = Entry(main_window, width=10)
x_entry.place(x=550, y=80)

y_label = Label(main_window, text='y:')
y_label.place(x=530, y=100)
y_entry = Entry(main_window, width=10)
y_entry.place(x=550, y=100)

entry_p_but = Button(main_window, text='Ввод', width=15, relief='solid',
                     command=lambda: get_point(points))
entry_p_but.place(x=530, y=125)

entry_but = Button(main_window, text='Окончить ввод', width=15, relief='solid',
                   command=lambda: calculate(points))
entry_but.place(x=530, y=450)

main_window.mainloop()
