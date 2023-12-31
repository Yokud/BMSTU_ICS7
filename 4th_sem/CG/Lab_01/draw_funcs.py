import tkinter as tk
from data_structures import *


def draw_solution(solution, points):
    root = tk.Tk()
    screen_res = (root.winfo_screenwidth(), root.winfo_screenheight())
    root.geometry("+10+10")
    root.title("Результат в графическом виде")
    root.resizable(False, False)

    screen_size = (screen_res[0] - 100, screen_res[1] - 100)
    screen = tk.Canvas(root, width=screen_size[0], height=screen_size[1])
    screen.pack()

    min_x, max_x = min([p.x for p in solution]), max([p.x for p in solution])
    min_y, max_y = min([p.y for p in solution]), max([p.y for p in solution])
    x_interval, y_interval = (min_x, max_x), (min_y, max_y)

    scale_factor = min(screen_size[0] / (max_x - min_x), screen_size[1] / (max_y - min_y))

    # Выравнивание точек по центру
    justify_x, justify_y = ((screen_size[0] - 0.9 * scale_factor * abs(max_x - min_x)) / 2,
                            (screen_size[1] - 0.9 * scale_factor * abs(max_y - min_y)) / 2)
    justify = (justify_x, justify_y)

    ans_triangle = Triangle(*solution)
    ans_triangle.init_bisects()
    
    # Рисование треугольника с пребразованием точек
    screen.create_polygon(justify_p(transform(ans_triangle.point_a, scale_factor, x_interval, y_interval), justify),
                          justify_p(transform(ans_triangle.point_b, scale_factor, x_interval, y_interval), justify),
                          justify_p(transform(ans_triangle.point_c, scale_factor, x_interval, y_interval), justify),
                          fill="red")

    # Рисование биссектрис
    screen.create_line(justify_p(transform(ans_triangle.bisect_ak.head, scale_factor, x_interval, y_interval), justify),
                       justify_p(transform(ans_triangle.bisect_ak.tail, scale_factor, x_interval, y_interval), justify),
                       fill="yellow", width=2)
    screen.create_line(justify_p(transform(ans_triangle.bisect_bl.head, scale_factor, x_interval, y_interval), justify),
                       justify_p(transform(ans_triangle.bisect_bl.tail, scale_factor, x_interval, y_interval), justify),
                       fill="blue", width=2)
    screen.create_line(justify_p(transform(ans_triangle.bisect_cm.head, scale_factor, x_interval, y_interval), justify),
                       justify_p(transform(ans_triangle.bisect_cm.tail, scale_factor, x_interval, y_interval), justify),
                       fill="green", width=2)

    # Рисование точек
    point_number = 0
    for point in points:
        point_number += 1
        if min_x <= point.x <= max_x and min_y <= point.y <= max_y:
            transformed_x, transformed_y = transform(point, scale_factor, x_interval, y_interval)
            screen.create_oval(transformed_x + justify_x - 2, transformed_y + justify_y - 2,
                               transformed_x + justify_x + 2, transformed_y + justify_y + 2,
                               fill='black')
            screen.create_text(transformed_x + justify_x - 3, transformed_y + justify_y - 10,
                               text="{:d}({:.6g}; {:.6g})".format(point_number, point.x, point.y))

    root.mainloop()


def transform(point, scale, x_interval, y_interval):
    return Point(0.9 * scale * abs(point.x - x_interval[0]), 0.9 * scale * abs(y_interval[1] - point.y))


def justify_p(point, justify):
    return point[0] + justify[0], point[1] + justify[1]
