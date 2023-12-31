# Лабораторная работа: Работа с файлами

# Назначение программы:
# Программа предназначена для работы с файлами с помощью меню. У неё есть
# такие возможности:
# - Создание в файле нового набора записей
# - Добавление новых записей
# - Вывод всех записей
# - Поиск по одному полю или по двум полям

# Описание переменных:
# File - Название файла
# choice - Выбор пункта меню
# Bad_symbols - Недопустимые символы в названии файла
# f, N, i, nof, nof1, nof2, field, field1, field2, s, boo - вспомогательные
# переменные

def NewRecords(file):
    f = open(file, 'w')
    N = int(input('Введите количество записей: '))
    i = 0
    while i < N:
        s = input('Введите Фамилию, Имя, Возраст и Группу через пробел '\
                  +str(i+1)+' записи: ')
        if len(s.split()) != 4:
            print('Ошибка при вводе данных!')
        else:
            if i == N - 1:
                f.write(s)
            else:
                f.write(s + '\n')
            i += 1
    f.close()


def AddRecords(file):
    try:
        f = open(file, 'r+')
        if f.readlines()[-1][-1] != '\n':
            f.write('\n')
        f.close()
    except:
        pass
    f = open(file, 'a')
    N = int(input('Введите количество новых записей: '))
    i = 0
    while i < N:
        s = input('Введите Фамилию, Имя, Возраст и Группу через пробел '\
                  +str(i+1)+' записи: ')
        if len(s.split()) != 4:
            print('Ошибка при вводе данных!')
        else:
            if i == N - 1:
                f.write(s)
            else:
                f.write(s + '\n')
            i += 1
    f.close()


def ShowAllRecords(file):
    f = open(file)
    for i in f:
        print(i, end = '')
    f.close()


def SearchingByOneField(file):
    f = open(file)
    nof = ''
    while nof == '':
        nof = input('Введите название поля: ')
        if nof == 'Фамилия':
            nof = 0
        elif nof == 'Имя':
            nof = 1
        elif nof == 'Возраст':
            nof = 2
        elif nof == 'Группа':
            nof = 3
        else:
            nof = ''
            print('Введено несуществующее поле. Попробуйте ещё раз')
    
    field = input('Введите искомое поле: ')
    boo = False
    for i in f:
        if i.split()[nof] == field:
            print(i, end = '')
            boo = True
    if not boo:
        print('Записей с таким полем не существует')
    f.close()


def SearchingByTwoFields(file):
    f = open(file)
    nof1 = ''
    nof2 = ''
    while nof1 == '':
        nof1 = input('Введите название первого поля: ')
        if nof1 == 'Фамилия':
            nof1 = 0
        elif nof1 == 'Имя':
            nof1 = 1
        elif nof1 == 'Возраст':
            nof1 = 2
        elif nof1 == 'Группа':
            nof1 = 3
        else:
            nof1 = ''
            print('Введено несуществующее поле. Попробуйте ещё раз')

    while nof2 == '':
        nof2 = input('Введите название второго поля: ')
        if nof2 == 'Фамилия':
            nof2 = 0
        elif nof2 == 'Имя':
            nof2 = 1
        elif nof2 == 'Возраст':
            nof2 = 2
        elif nof2 == 'Группа':
            nof2 = 3
        else:
            nof2 = ''
            print('Введено несуществующее поле. Попробуйте ещё раз')
    
    field1 = input('Введите первое искомое поле: ')
    field2 = input('Введите второе искомое поле: ')
    boo = False
    for i in f:
        if i.split()[nof1] == field1 and i.split()[nof2] == field2:
            print(i, end = '')
            boo = True
    if not boo:
        print('Записей с такими полями не существует')
    f.close()



File = ''
choice = None
Bad_symbols = ['', '\\', '/', ':', '*', '?', '"', '<', '>', '|', '+']
while choice != '0':
    print('''
--------------------------------------------------
    1 - Выбор файла
    2 - Создание в файле нового набора записей
    3 - Добавление новых записей в файл
    4 - Вывод всех записей
    5 - Поиск по полю
    6 - Поиск по двум полям
    0 - Выход
--------------------------------------------------
    ''')
    choice = input('Выбор: ')
    print('\n')
    if choice == '1':
        File = input('Введите название файла(без расширения): ')
        boo = True
        for s in File:
            if s in Bad_symbols:
                boo = False
                break
        if boo:
            File += '.txt'
        else:
            File = ''
            print('Недопустимое имя файла')
        
    elif choice == '2':
        if File != '':
            NewRecords(File)
        else:
            print('Для начала выберите файл')
    
    elif choice == '3':
        if File != '':
            AddRecords(File)
        else:
            print('Для начала выберите файл')
    
    elif choice == '4':
        if File != '':
            ShowAllRecords(File)
        else:
            print('Для начала выберите файл')
    
    elif choice == '5':
        if File != '':
            SearchingByOneField(File)
        else:
            print('Для начала выберите файл')
    
    elif choice == '6':
        if File != '':
            SearchingByTwoFields(File)
        else:
            print('Для начала выберите файл')
    
    elif choice == '0':
        print('Завершение работы')
