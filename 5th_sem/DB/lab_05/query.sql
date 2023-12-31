copy (select row_to_json(m) from Merchants m) to 'D:\Repos\GitHub\5_sem_SE\DB\lab_05\dataset\merchants.json';
copy (select row_to_json(s) from Shops s) to 'D:\Repos\GitHub\5_sem_SE\DB\lab_05\dataset\shops.json';
copy (select row_to_json(t) from Towns t) to 'D:\Repos\GitHub\5_sem_SE\DB\lab_05\dataset\towns.json';
copy (select row_to_json(c) from Chain_stores c) to 'D:\Repos\GitHub\5_sem_SE\DB\lab_05\dataset\chain_stores.json';


drop table if exists merchants_from_json;
create table merchants_from_json(
    Id integer primary key,
	Name text not null,
	Gender text not null,
	Race text not null,
	Date_of_birth date not null
);

drop table if exists temp;
create table temp (
    data jsonb
);

copy temp from 'D:\Repos\GitHub\5_sem_SE\DB\lab_05\dataset\merchants.json';
insert into merchants_from_json
select (data->>'id')::integer, (data->>'name')::nchar(32), (data->>'gender')::nchar(10), (data->>'race')::nchar(10), (data->>'date_of_birth')::date
from temp;

select *
from merchants_from_json;


alter table merchants_from_json add column in_json json;
update merchants_from_json
set in_json =
    row_to_json(row)
    from (select Id, Name, Gender, Race, Date_of_birth
          from merchants_from_json) as row
where merchants_from_json.Id = row.Id;

select *
from merchants_from_json
order by Id;


select in_json
from merchants_from_json
where Race = 'Имперец';


select in_json->'name'
from merchants_from_json
where Race = 'Имперец';


create or replace function if_key_exists(json_to_check jsonb, key text)
returns boolean
as $$
begin
    return (json_to_check->key) is not null;
end;
$$ language plpgsql;

select if_key_exists(in_json, 'name') from merchants_from_json where Id = 1;
select if_key_exists(in_json, 'town') from merchants_from_json where Id = 1;


update temp
set data = data || '{"id":"1001", "name":"Лев", "gender":"Мужчина", "race":"Чел", "date_of_birth":"0001-11-1"}'::jsonb
where (data->>'id')::integer = 1000;

select *
from temp;


select jsonb_each(data)
from temp
where (data->>'id')::integer = 1;