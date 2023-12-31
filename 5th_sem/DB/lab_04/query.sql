create extension if not exists plpython3u;

-- 1. Скалярная функция
drop function if exists AgePy(date_of_birth date);

create or replace function AgePy(date_of_birth date)
returns int
as $$
    import datetime as d

    dt = d.datetime.strptime(date_of_birth, '%Y-%m-%d')

    return 201 - dt.year
$$ language plpython3u;

select AgePy(date_of_birth)
from merchants
where id = 1;


-- 2. Агрегатная функция
drop function if exists MerchantShopsCountPy(id_merch integer);

create or replace function MerchantShopsCountPy(id_merch integer)
returns integer
as $$
    query = "select count(*) from Shops where Id_merchant= {0};".format(id_merch)
    result = plpy.execute(query)

    return result[0]["count"]
$$ language plpython3u;

select MerchantShopsCountPy(7);


-- 3. Табличная функция
drop function if exists ShopsInTownsPy();

create or replace function ShopsInTowns()
returns table(
    Shop_Name text,
    Merchandise text,
    Town_Name text
)
as $$
    query = "select Shops.Name as Shop_Name, Shops.Merchandise as Merchandise, Towns.Name as Town_Name \
            from Shops join Towns on Towns.Id = Shops.Id_town \
            where Towns.Type = 'Город';"

    result = plpy.execute(query)

    for row in result:
        yield (row["shop_name"], row["merchandise"], row["town_name"])
$$ language plpython3u;

select * from ShopsInTowns();


-- 4. Процедура
drop procedure if exists ChangeRulerPy(id_town int, new_ruler text);

create or replace procedure ChangeRulerPy(id_town int, new_ruler text)
as $$
    plan = plpy.prepare("update Towns set Ruler = $1 where Id = $2;", ["TEXT", "INT"])
    plpy.execute(plan, [new_ruler, id_town])
$$ language plpython3u;

select * from Towns where Id = 444;
call ChangeRulerPy(444, 'MyName');
select * from Towns where Id = 444;


-- 5. Триггер
drop trigger if exists GetNewTownInfo on Towns;
drop function if exists GetTownsTriggerPy();

create or replace function GetTownsTriggerPy()
returns trigger
as $$
    if TD["new"]["type"].strip() == 'Город':
        plpy.notice(f"Был добавлен новый город {TD['new']['town_name']}")
    elif TD["new"]["type"].strip() == 'Деревня':
        plpy.notice(f"Была добавлена новая деревня {TD['new']['town_name']}")
    else:
        plpy.notice("Неизвестный тип поселения!")
$$ language plpython3u;

create trigger GetNewTownInfo after insert on Towns
for row execute procedure GetTownsTriggerPy();

insert into towns
values (1001, 'Test', 'Myself', 100000, 'Город');

delete from towns
where Id = 1001;


-- 6. Тип данных
drop function if exists SetRuler(name text, gender text, race text, date_of_birth date);
drop type if exists Ruler;

create type Ruler as (
	Name text,
	Gender text,
	Race text,
	Date_of_birth date
)

create or replace function SetRuler(name text, gender text, race text, date_of_birth date)
returns setof Ruler
as $$
	return ([name, gender, race, date_of_birth],)	
$$ language plpython3u;

select * from SetRuler('Иван', 'Мужчина', 'Норд', date('2001-01-03'));