def left(x, y, h, i):
    return (y[i] - y[i - 1]) / h if i > 0 else None

def right(x, y, h, i):
    return (y[i + 1] - y[i]) / h if i < len(y) - 1 else None

def center(x, y, h, i):
    return (y[i + 1] - y[i - 1]) / 2 / h if i < len(y) - 1 and i > 0 else None

def left_double(x, y, h, i):
    return (y[i] - y[i - 2]) / 2 / h if i > 1 else None

def runge_left(x, y, h, i):
    if i < 2:
        return None
    f1 = left(x, y, h, i)
    f2 = left_double(x, y, h, i)
    return f1 + (f1 - f2) 

def align_vars_right(x, y, h, i):
    if i > len(y) - 2:
        return None
    der = (1 / y[i + 1] - 1 / y[i]) / (1 / x[i + 1] - 1 / x[i])
    return der * y[i] * y[i] / x[i] / x[i]

def second_der(x, y, h, i):
    return (y[i - 1] - 2 * y[i] + y[i + 1]) / (h * h) if i < len(y) - 1 and i > 0 else None

def main():
    x = [1, 2, 3, 4, 5, 6]
    y = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]

    methods = [left, center, runge_left, align_vars_right, second_der]
    print("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐")
    print("│    x    │    y    │   left  │  center │  runge  │  align  │  second │")
    print("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤")
    for i in range(len(x)):
        print("│{:9.3f}│".format(x[i]), end = "")
        print("{:9.3f}│".format(y[i]), end = "")
        for func in methods:
            res = func(x, y, 1, i)
            if res is None:
                print("    -    │", end = "")
            else:
                print("{:9.4f}│".format(res), end = "")
        print()
    print("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘")


if __name__ == "__main__":
    main()
