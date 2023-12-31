drop procedure if exists MaxCommodityPerCapitaByType();
drop table if exists tbl;

alter table Towns rename Name to Town_name;

create temp table tbl(merch text, town_name text, max_per_capita real);

create or replace procedure MaxCommodityPerCapitaByType() as $$
begin
	insert into tbl
	select merch, max(town_name), max(per_capita)
	from (select ST.Merchandise as merch, ST.Town_name as town_name, cast(count(*) as real) / ST.Population as per_capita
			from (Shops S join Towns T on S.Id_town = T.Id) as ST
		 	group by ST.Merchandise, ST.Town_name, ST.Population) as TMP
	group by merch;
	
end;
$$ language plpgsql;

call MaxCommodityPerCapitaByType();

select *
from tbl
order by merch;