# Лабораторная работа: Файлы

# Программа предназначена для записи строк из одного файла в другой
# в обратном порядке

# f, g - файлы для чтения/записи
# rewriter - рекурсивная функция, записывающая строки в обратном порядке
# из f в g

def rewriter(f, g):
    for i in f:
        rewriter(f, g)
        if i[-1] == '\n':
            g.write(i)
        else:
            g.write(i+'\n')

f = open('f.txt')
g = open('g.txt', 'w')
rewriter(f, g)
f.close()
g.close()
