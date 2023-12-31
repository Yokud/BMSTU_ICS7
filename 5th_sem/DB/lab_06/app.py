import psycopg2 as db


def print_table(cursor):
    columns = cursor.description
    result = cursor.fetchall()

    lens = [len(col.name) for col in columns]

    for row in result:
        for i in range(len(row)):
            lens[i] = max(lens[i], len(str(row[i]).strip()))

    print("\nРезультат:")
    fence = '-' * (sum(i + 3 for i in lens) + 1)

    print(fence)
    i = 0
    for col in columns:
        print("| " + col.name.capitalize().center(lens[i]) + " ", end='')
        i += 1
    print("|")
    print(fence)

    for row in result:
        i = 0
        for val in row:
            print("| " + str(val).rstrip().ljust(lens[i]) + " ", end='')
            i += 1
        print("|")
    print(fence)


conn = db.connect(database="skyrims_merchants", user="postgres", password="Dik090909", host="localhost", port=5432)
cur = conn.cursor()

print("Программа взаимодействия с базой данных торговцев Скайрима\n" + '-' * 125)
comm = -1
while comm != 0:
    print("    1. Определить среднее арифметическое населения поселений \n\
    2. Найти магазины в городах \n\
    3. Вывести информацию о поселениях и отследить мин., макс. и среднее арифм. населения по правителям городов \n\
    4. Узнать ID базы данных \n\
    5. Найти разность между населением поселений и их средним арифметическим \n\
    6. Найти книжные магазины в указанном по ID городе \n\
    7. Изменить правителя в указанном по ID городе \n\
    8. Узнать имя текущего пользователя \n\
    9. Создать таблицу магазинов в городах \n\
    10. Выполнить вставку данных в таблицу магазинов в городах\n\
    11. Изменить торговца у указанного по ID магазина\n\n\
    0. Выход\n")

    comm = int(input("Введите команду: "))

    if comm == 1:
        query = "select avg(Population) from Towns;"
        cur.execute(query)
        result = cur.fetchone()
        print("Среднее арифметическое населения поселений: " + str(float(result[0])))
    elif comm == 2:
        query = "select Shops.Name, Shops.Merchandise, Can_invest, Hours_start, Hours_end \
                 from Shops join Towns on Shops.Id_town = Towns.Id \
                 where Towns.Type = 'Город';"
        cur.execute(query)

        print_table(cur)
    elif comm == 3:
        query = "with Towns_descr (Town_name, Ruler_name, Population, Type, Min_Popul, Max_Popul, " \
                "Avg_Popul) as " \
                "(select Name, Ruler, Population, Type, \
                    min(Population) over (partition by Ruler order by Name) as Min_population,\
                    max(Population) over (partition by Ruler order by Name) as Max_population,\
                    avg(Population) over (partition by Ruler order by Name) as Avg_population\
                  from Towns)\
                select *\
                from Towns_descr;"
        cur.execute(query)

        print_table(cur)
    elif comm == 4:
        name = "skyrims_merchants"
        query = "select pg_database.oid from pg_database where pg_database.datname = '{0}';".format(name)
        cur.execute(query)
        result = cur.fetchone()
        print("Имя БД: {0}\nID БД: {1}".format(name, int(result[0])))
    elif comm == 5:
        query = "create or replace function AvgPopulationDiff(popul integer) returns real as $$ \
                    begin\
                        return (select popul - avg(Population) from Towns);\
                    end;\
                    $$ language plpgsql;\
                    \
                    select Name, Population, AvgPopulationDiff(Population)\
                    from Towns;"
        cur.execute(query)

        print_table(cur)
    elif comm == 6:
        id_town = int(input("Введите ID города: "))

        query = "create or replace function BookShops(town_id integer) returns table(shop_name nchar(32), can_invest " \
                "bool, hours_start time, hours_end time, town_name nchar(32)) as $$\
                begin \
                    create temp table if not exists tbl (shop_name nchar(32), can_invest bool, hours_start time, hours_end time, town_name nchar(32));\
                    \
                    insert into tbl\
                    select Shops.Name, Shops.Can_invest, Shops.Hours_start, Shops.Hours_end, Towns.Name\
                    from Towns join Shops on Towns.Id = Shops.id_town\
                    where Towns.Id = town_id and Merchandise = 'Книги';\
                    \
                    return query select * from tbl;\
                end;\
                $$ language plpgsql; \
                \
                select *\
                from BookShops({0});".format(id_town)
        cur.execute(query)

        print_table(cur)
    elif comm == 7:
        id_town = int(input("Введите ID города: "))
        name = input("Введите имя нового правителя: ")

        query = "create or replace procedure ChangeRuler(town_id int, ruler_name text) as $$\
                begin\
                    update Towns\
                    set Ruler = ruler_name\
                    where Id = town_id;\
                end;\
                $$ language plpgsql;\
                \
                call ChangeRuler({0}, '{1}');".format(id_town, name)

        cur.execute(query)
        conn.commit()

        print("Имя нового правителя города с ID {0}: {1}".format(id_town, name))
    elif comm == 8:
        query = "select current_user;"
        cur.execute(query)
        result = cur.fetchone()
        print("Текущий пользователь: " + str(result[0]))
    elif comm == 9:
        query = "select Shops.Name as Shop_Name, Shops.Merchandise, Shops.Can_invest, Towns.Name\
                    into Shops_in_cities\
                    from Shops join Towns on Towns.Id = Shops.Id_town\
                    where Towns.Type = 'Город';"

        cur.execute(query)
        conn.commit()

        print("Таблица с магазинами в городах была создана")

        query = "select * from Shops_in_cities;"
        cur.execute(query)
        print_table(cur)
    elif comm == 10:
        name, merch, can_inv, town_name = input("Введите новую строку значений для таблицы Shops_in_cities: ").split()

        query = "insert into Shops_in_cities\
                values('{0}', '{1}', {2}, '{3}')".format(name, merch, can_inv, town_name)

        cur.execute(query)
        conn.commit()

        print("Новое значение было вставлено в таблицу Shops_in_cities")

        query = "select * from Shops_in_cities;"
        cur.execute(query)
        print_table(cur)
    elif comm == 11:
        id_shop = int(input("Введите ID магазина: "))
        id_merchant = input("Введите ID нового торговца: ")

        query = "create or replace procedure ChangeMerchant(shop_id int, merch_id int) as $$\
                begin\
                    update Shops\
                    set id_merchant = merch_id\
                    where Id = shop_id;\
                end;\
                $$ language plpgsql;\
                \
                call ChangeRuler({0}, '{1}');".format(id_shop, id_merchant)

        cur.execute(query)
        conn.commit()

        print("Имя нового торговца магазина с ID {0}: {1}".format(id_shop, id_merchant))
    elif comm == 0:
        print("Завершение работы...")
        break
    else:
        print("Неизвестная команда!")

    print("\n" + '-' * 125)

cur.close()
conn.close()
