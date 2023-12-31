# Лабораторная работа: Редактор текста

# Назначение программы:
# Программа предназначена для редактирования текста, заданного в виде строк в
# массив, с помощью консольного меню

# Описание переменных:
# Text - текст
# Rows - количество строк в тексте
# Alignment - режим выравнивания текста(по лев. или прав. краю, по ширине)
# choice - выбор пункта в меню
# oldword, newword - заменяемое и заменяющие слова
# delword - удаляемое слово
# a, b, flag, word, numbers, symbols, boo, f1, f2, operator, k - вспомогательные
# переменные

def LeftAlignment(Text, Alignment):
    if Alignment != 0:
        if Alignment == 1:
            for i in range(Rows):
                a = ''
                flag = False
                for j in range(len(Text[i])):
                    if Text[i][j] != ' ':
                        flag = True
                            
                    if flag:
                        a += Text[i][j]
                            
                Text[i] = a
                    
        else:
            DeleteCentralAlignment(Text)

def RightAlignment(Text, Alignment):
    if Alignment != 1:
        if Alignment == 2:
            DeleteCentralAlignment(Text)
        for i in range(Rows):
            b = ' '*(80 - len(Text[i])) + Text[i]
            Text[i] = b

def CentralAlignment(Text, Alignment):
    if Alignment != 2:
        if Alignment == 1:
            LeftAlignment(Text, Alignment)
        for i in range(Rows - 1):
            b = Text[i]
            while len(b) < 80:
                a = ''
                flag = False
                for j in range(len(b)):
                    if b[j] == ' ':
                        flag = True
                    elif flag:
                        #if len(a)+len(b[j:len(b)-1]) < 79:
                        if len(a) + len(b) - 1 - j < 79:
                            a += ' '
                        flag = False
                    a += b[j]
                b = a
            Text[i] = b

def DeleteCentralAlignment(Text):   # Удаление лишних пробелов между слов
    for i in range(Rows - 1):
        a = ''
        flag = False
        for j in range(len(Text[i])):
            if Text[i][j] != ' ':
                a += Text[i][j]
                flag = False
            elif not flag:
                a += Text[i][j]
                flag = True
            else:
                continue
        Text[i] = a

def ReplaceWord(Text, oldword, newword):
    if newword == '':           # Режим удаления слова 
        for i in range(Rows):
            a = ''
            word = ''
            prevsymbol = ''
            boo = False
            for j in range(len(Text[i])):
                if Text[i][j] != ' ' and Text[i][j] != ','\
                   and Text[i][j] != '.':
                    word += Text[i][j]
                    if j == len(Text[i]) - 1:
                        if word == oldword and not boo:
                            word = ''
                            boo = True
                        else:
                            a += word
                            word = ''
                else:
                    if word == oldword and not boo:
                        if Text[i][j] == '.' or Text[i][j] == ',':
                            a = list(a)
                            k = len(a) - 1
                            while a[k] == ' ':
                                k -= 1
                            a[k + 1] = Text[i][j]
                            a = ''.join(a)
                        else:
                            a += Text[i][j]
                        word = ''
                        boo = True
                    else:
                        a += word + Text[i][j]
                        word = ''
                    
                    
            Text[i] = a
            if boo:
                break
            if boo:
                break
    else:           # Режим замены слов             
        for i in range(Rows):
            a = ''
            word = ''
            for j in range(len(Text[i])):
                if j == len(Text[i]) - 1:
                    word += Text[i][j]
                    if word == oldword:
                        a += newword
                    else:
                        a += word
                
                if Text[i][j] != ' ' and Text[i][j] != '.' \
                   and Text[i][j] != ',':
                    word += Text[i][j]
                else:
                    if word == oldword:
                        a += newword
                    else:
                        a += word
                    word = ''
                    a += Text[i][j]                
            Text[i] = a

def ArithmeticResult(Text):
    numbers = '0123456789'
    symbols = '+-'
    for i in range(Rows):
        b = Text[i]
        a = ''
        f1 = '' # Первое слагаемое
        f2 = '' # Второе слагаемое
        operator = '' 
        for j in range(len(b)):
            if b[j] in numbers or b[j] in symbols:
                if b[j] in numbers:
                    if operator != '':
                        f2 += b[j]
                    else:
                        f1 += b[j]
                    if j == len(b) - 1 and f2 == '':
                        a += f1
                elif b[j] in symbols and f1 != '':
                    operator += b[j]
                elif b[j] in symbols: # Чтобы не удалялись дефисы
                    a += b[j]
            elif f1 != '' and f2 == '' and b[j] != ' ':
                a += f1 + ' ' + b[j]
                f1 = ''
            elif f1 == '':  # Проверка фиксации записи примера
                a += b[j]
            if (b[j] == ' ' or b[j] == ',' or b[j] == '.' or j == len(b) - 1)\
               and f2 != '':
                if operator == '+':
                    if j == len(b) - 1:
                        a += str(int(f1) + int(f2))
                    else:
                        a += str(int(f1) + int(f2)) + b[j]
                    f1 = ''
                    f2 = ''
                    operator = '' 
                elif operator == '-':
                    if j == len(b) - 1:
                        a += str(int(f1) - int(f2))
                    else:
                        a += str(int(f1) - int(f2)) + b[j]
                    f1 = ''
                    f2 = ''
                    operator = ''
                    
        Text[i] = a

def UpdateAlignment(Text, Alignment):   # Обновление выравнивания
    if Alignment == 0:
        DeleteCentralAlignment(Text)
    elif Alignment == 1:
        LeftAlignment(Text, 1)
        RightAlignment(Text, 0)
    elif Alignment == 2:
        DeleteCentralAlignment(Text)
        CentralAlignment(Text, 0)

        
Text = [
'Насвистывая, Монтэг поднялся на эскалаторе на встречу ночной тишине. Не',
'думая ни о чём он дошёл до поворота. Но ещё раньше, чем выйти на угол,',
'он вдруг замедлил шаги, как будто ветер, налетев откуда-то, ударил ему',
'в лицо или кто-то окликнул его по имени. Уже несколько раз, приближаясь',
'вечером к повороту, за которым освещённый звёздами тротуар вёл к его дому,',
'он испытывал это странное чувство.'
]
Rows = len(Text)
choice = None
Alignment = 0  # 0 - по левому краю, 1 - по правому краю, 2 - по ширине

while choice != 0:
    print('''
-------------------------------------------------------------------------------
''')
    print('Текст:')
    for t in Text:
        print(t)

    print('''
-------------------------------------------------------------------------------
    1 - Выравнивание по ширине
    2 - Выравнивание по левому краю
    3 - Выравнивание по правому краю
    4 - Замена одного слова в тексте другим
    5 - Удаление одного слова в тексте
    6 - Замена арифметических выражений на результат их вычисления
    7 - Поменять местами самую длинную и самую короткую по кол-ву букв в строке
    0 - Выход
-------------------------------------------------------------------------------
    ''')
    choice = input('Выбор: ')
    if choice == '1':
        CentralAlignment(Text, Alignment)    
        Alignment = 2
            
    elif choice == '2':
        LeftAlignment(Text, Alignment)
        Alignment = 0
    
    elif choice == '3':
        RightAlignment(Text, Alignment)
        Alignment = 1
    
    elif choice == '4':
        s = 'Введите заменяемое и заменяющие слова через пробел: '
        try:
            oldword, newword = map(str, input(s).split())
            ReplaceWord(Text, oldword, newword)
            UpdateAlignment(Text, Alignment)
        except:
            print('Ошибка при вводе данных!')
    
    elif choice == '5':
        delword = input('Введите удаляемое слово: ')
        ReplaceWord(Text, delword, '')
        UpdateAlignment(Text, Alignment)
    
    elif choice == '6':
        ArithmeticResult(Text)
        UpdateAlignment(Text, Alignment)

    elif choice == '7':
        A = []
        s = ' '.join(Text)
        a = ''
        for i in range(len(s)):
            if s[i] == '.':
                a += '.'
                A.append(a)
                a = ''
            else:
                if a == '' and s[i] == ' ':
                    continue
                else:
                    a += s[i]
        for i in range(len(A)):
            for j in range(i + 1, len(A)):
                if len(A[i]) > len(A[j]):
                    A[i], A[j] = A[j], A[i]
                    
        for i in range(len(A)):
            if len(A[i]) > 80:
                for j in range(len(A[i]) - 1, -1, -1):
                    if A[i][j] == ' ' and j < 80:
                        A[i] = A[i][:j] + '\n' + A[i][j+1:]
                        break
                        
        Text = A
