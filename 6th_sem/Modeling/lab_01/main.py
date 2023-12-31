import numpy as np
import matplotlib.pyplot as plt


def func(x, u):
    return x * x + u * u
        

def Picar(x, s):
    match s:
        case 1:
            return x ** 3 / 3
        case 2:
            return Picar(x, s - 1) + x ** 7 / 63
        case 3:
            return Picar(x, s - 1) + 2 * (x ** 11) / 2079 + (x ** 15) / 59535
        case 4:
            return Picar(x, s - 2) + 2 * (x ** 11) / 2079 + 13 * (x ** 15) / 218295 + 82 * (x ** 19) / 37328445 + 662 * (x ** 23) / 10438212015 + 4 * (x ** 27) / 3341878155 + (x ** 31) / 109876902975


def Euler(x0, u0, h, x):
    cur_x = x0
    cur_u = u0

    n = int(abs(x - x0) / h)

    is_rev = 1 if x0 < x else -1

    for x in np.arange(n):
        cur_u += h * func(cur_x, cur_u)
        cur_x += h

    return cur_u * is_rev


def RungeKutta(x0, u0, h, x, alpha):
    cur_x = x0
    cur_u = u0

    n = int(abs(x - x0) / h)

    is_rev = 1 if x0 < x else -1

    for i in np.arange(n):
        cur_u += h * ((1 - alpha) * func(cur_x, cur_u) + alpha * func(cur_x + h / (2 * alpha), cur_u + h / (2 * alpha) * func(cur_x, cur_u)))
        cur_x += h

    return cur_u * is_rev


def PrintTable():
    h = 1e-5
    x_step = 0.05
    x_end = 2

    print("\nТаблица:")
    print('-' * 175)
    print("|   X  | Метод Пикара (1-е приближение) | Метод Пикара (2-е приближение) | Метод Пикара (3-е приближение) | Метод Пикара (4-е приближение) | Метод Эйлера | Метод Рунге-Кутта |")
    print('-' * 175)

    for x in np.arange(0, x_end + x_step, x_step):
        print("| {:^4.2f} | {:^30.6f} | {:^30.6f} | {:^30.6f} | {:^30.6f} | {:^12.6f} | {:^17.6f} |".format(x, Picar(x, 1), Picar(x, 2), Picar(x, 3), Picar(x, 4), Euler(0, 0, h, x), RungeKutta(0, 0, h, x, 1)))

    print('-' * 175)
    

def PrintGraph():
    h = 1e-2
    print("\nПостроение графика...")

    xs = np.arange(-2, 2 + h, h)
    n = len(xs)
    ys = np.ndarray(n)

    for i in range(n):
        ys[i] = Euler(0, 0, 1e-5, xs[i])
        
    plt.plot(xs, ys, label="Euler")

    for i in range(n):
        ys[i] = RungeKutta(0, 0, 1e-5, xs[i], 1)
        
    plt.plot(xs, ys, label="Runge-Kutta")

    xs = np.arange(-0.85, 0.85 + h, h)
    n = len(xs)
    ys = np.ndarray(n)

    for i in range(n):
        ys[i] = Picar(xs[i], 1)

    plt.plot(xs, ys, label="Picar (1th approximation)")

    xs = np.arange(-0.95, 0.95 + h, h)
    n = len(xs)
    ys = np.ndarray(n)

    for i in range(n):
        ys[i] = Picar(xs[i], 2)

    plt.plot(xs, ys, label="Picar (2th approximation)")

    xs = np.arange(-1.3, 1.3 + h, h)
    n = len(xs)
    ys = np.ndarray(n)

    for i in range(n):
        ys[i] = Picar(xs[i], 3)

    plt.plot(xs, ys, label="Picar (3th approximation)")

    xs = np.arange(-1.5, 1.5 + h, h)
    n = len(xs)
    ys = np.ndarray(n)

    for i in range(n):
        ys[i] = Picar(xs[i], 4)

    plt.plot(xs, ys, label="Picar (4th approximation)")
    
    plt.legend()
    plt.show()


def main():
    h = 1e-5
    
    print("Picar: u(2) =", Picar(2, 4))
    print("Euler: u(2) =", Euler(0, 0, h, 2))
    print("Runge-Kutta: u(2) =", RungeKutta(0, 0, h, 2, 1))

    PrintTable()
    PrintGraph()


if __name__ == '__main__':
    main()
