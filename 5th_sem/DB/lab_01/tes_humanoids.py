import random


class Nord:
    race = "Норд"
    male_names = ["Тарстен", "Эрих", "Агвид", "Бьёрн", "Викар", "Инг", "Йорген", "Карл", "Логмэр", "Свейн"]
    female_names = ["Айдис", "Эрна", "Батильда", "Хельга", "Кэролайн", "Марта", "Рагнильд", "Свея", "Фрея", "Торберта"]
    nicknames = ["Огненный глаз", "Клык Сердца", "", "Ранний расвет", "Жестокое море", "Красная рука",
                 "Мастер янтаря", "Серая грива", "Топор Войны", "Буйный ветер"]

    def __init__(self):
        pass


class Imperian:
    race = "Имперец"
    male_names = ["Кай", "Требониус", "Аппий", "Гай", "Марк", "Квинт", "Тит", "Тиберий", "Гней", "Нумерий"]
    female_names = ["Корнелия", "Клавдия", "Юлия", "Валерия", "Туллия", "Эллия", "Рия", "Флавия"]
    nicknames = ["Эллий", "Антониус", "Косадес", "Клавдий", "Флавий", "Юлий", "Помпей", "Валерий", "Ульпий", "Туллий",
                 ""]

    def __init__(self):
        pass


class Breton:
    race = "Бретонец"
    male_names = ["Джон", "Питер", "Рубен", "Франс", "Пирс", "Алан", "Патрик", "Гай", "Леон"]
    female_names = ["Виола", "Глория", "Лиана", "Катрин", "Каролин", "Изольда", "Мора", "Кейси", "Рэйчел"]

    def __init__(self):
        pass


class Redguard:
    race = "Редгард"
    male_names = ["Амрен", "Бренуин", "Назим", "Аззада", "Зандер", "Разелан"]
    female_names = ["Алем", "Сафия"]

    def __init__(self):
        pass


class Altmer:
    race = "Альтмер"
    male_names = ["Брандил", "Ирил", "Синдерион", "Окато", "Серидур"]
    female_names = ["Эленвен", "Арданин", "Тандинви"]

    def __init__(self):
        pass


class Bosmer:
    race = "Босмер"
    male_names = ["Маглир", "Барадрас", "Агамир"]
    female_names = ["Бревен", "Гальдебир"]

    def __init__(self):
        pass


class Orc:
    race = "Орк"
    male_names = ["Дара Гра-Болл", "Шарн Гро-Музгоб"]
    female_names = ["Богруш Гро-Галаш", "Ушнар Гро-Шадборгроб"]

    def __init__(self):
        pass


class Danmer:
    race = "Данмер"
    male_names = ["Готрен", "Данар", "Сельвин", "Банор", "Эльвас", "Драм", "Эно"]
    female_names = ["Нилено", "Ведуза", "Драрейн", "Драласа", "Анара", "Дандера", "Ранис"]

    def __init__(self):
        pass


class Argonian:
    race = "Аргонианин"
    male_names = ["Джари-Ра", "Гулум-Ай", "Тален-Джей"]
    female_names = ["Диджа", "Шави"]

    def __init__(self):
        pass


class Khajiit:
    race = "Каджит"
    male_names = ["Ри'Закар", "Дж'Зарр", "Дро'Захарр", "Ма'Джад"]
    female_names = ["Хассири", "С'Драсса", "Тсави", "Джобаша"]

    def __init__(self):
        pass


def GetAllObjs():
    return Nord(), Imperian(), Breton(), Redguard(), Altmer(), Bosmer(), Danmer(), Orc(), Khajiit(), Argonian()


def GenHumanoidInfo(Humanoid):
    min_interval = 25 if Humanoid in (Altmer, Bosmer, Orc, Danmer) else 131

    month = str(random.randint(1, 12))
    day = str(random.randint(1, 30)) if month != '2' else str(random.randint(1, 28))
    date_of_birth = day + '.' + month + '.' + \
                    str(random.randint(min_interval, 181))
    gender = random.choice(["Мужчина", "Женщина"])
    name = random.choice(Humanoid.male_names) if gender == "Мужчина" else random.choice(Humanoid.female_names)

    if Humanoid.race == "Норд" or Humanoid.race == "Имперец" and gender == "Мужчина":
        name = name + " " + random.choice(Humanoid.nicknames)
        name = name.rstrip()

    return name, gender, Humanoid.race, date_of_birth
