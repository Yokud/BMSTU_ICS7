import csv
import random as rnd
from tes_humanoids import *
from tes_shops import *
from tes_towns import *


def GenTables(n: int):
    humanoids = [*GetAllObjs()]
    shop_gen = Shop()
    town_gen = Town()
    merchants = [GenHumanoidInfo(rnd.choice(humanoids)) for i in range(n)]
    towns = [("Вайтран", "Балгруф Старший", rnd.randint(1000, 10000), "Город"),
             ("Виндхельм", "Ульфрик Буревестник", rnd.randint(1000, 10000), "Город"),
             ("Винтерхолд", "Корир", rnd.randint(1000, 10000), "Город"),
             ("Данстар", "Скальд", rnd.randint(1000, 10000), "Город"),
             ("Маркарт", "Игмунд", rnd.randint(1000, 10000), "Город"),
             ("Морфал", "Идгрод Чёрная", rnd.randint(1000, 10000), "Город"),
             ("Рифтен", "Лайла Рука Закона", rnd.randint(1000, 10000), "Город"),
             ("Солитьюд", "Элисиф Прекрасная", rnd.randint(1000, 10000), "Город"),
             ("Фолкрит", "Сиддгейр", rnd.randint(1000, 10000), "Город"), *[town_gen.GenTownInfo() for i in range(n - 9)]]
    shops = [shop_gen.GetShopInfo() for i in range(n)]
    chain_stores = list()

    for i in range(n):
        id_merch, id_town = rnd.randint(1, n), rnd.randint(1, n)
        shops[i] = (*shops[i], id_merch, id_town)
        chain_stores.append((id_merch, id_town, rnd.randint(10000, 100000)))

    with open("C:\\PostgreSQL_data\\merchants.csv", "w", newline='', encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)

        for i in range(1, n + 1):
            writer.writerow([i, *merchants[i - 1]], )

    with open("C:\\PostgreSQL_data\\shops.csv", "w", newline='', encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)

        for i in range(1, n + 1):
            writer.writerow([i, *shops[i - 1]])

    with open("C:\\PostgreSQL_data\\towns.csv", "w", newline='', encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)

        for i in range(1, n + 1):
            writer.writerow([i, *towns[i - 1]])

    with open("C:\\PostgreSQL_data\\chain_stores.csv", "w", newline='', encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)

        for i in range(n):
            writer.writerow(chain_stores[i])

    print("Writing complete")


if __name__ == "__main__":
    GenTables(1000)
