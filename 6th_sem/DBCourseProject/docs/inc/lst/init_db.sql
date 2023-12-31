Drop database if exists spsr_lt_db;
Create database spsr_lt_db;

create table Shops
(
	ID serial primary key,
	Name text not null,
	Description text not null
);

create table SaleReceipts
(
	ID serial primary key,
	FIO text not null,
	ShopID integer not null,
	DateOfPurchase date not null,
	foreign key (ShopID) references Shops(ID) on delete cascade
);

create table Products
(
	ID serial primary key,
	Name text not null,
	ProductType text not null
);

create table Availability
(
	ID serial primary key,
	ShopID integer not null,
	ProductID integer not null,
	foreign key (ShopID) references Shops(ID) on delete cascade,
	foreign key (ProductID) references Products(ID) on delete cascade
);

create table SaleReceiptPositions
(
	ID serial primary key,
	AvailabilityID integer not null,
	SaleReceiptID integer not null,
	foreign key (AvailabilityID) references Availability(ID) on delete cascade,
	foreign key (SaleReceiptID) references SaleReceipts(ID) on delete cascade
);

create table CostStory
(
	ID serial primary key,
	Year integer not null,
	Month integer not null,
	Cost integer not null,
	AvailabilityID integer not null,
	foreign key (AvailabilityID) references Availability(ID) on delete cascade
);

create view Costs as
	select T.AvailabilityID, Cost
	from CostStory join 
	(select AvailabilityID, max(make_date(Year, Month, 1)) as CostDate
	from CostStory
	group by AvailabilityID) 
	as T on T.AvailabilityID = CostStory.AvailabilityID and T.CostDate = make_date(CostStory.Year, CostStory.Month,1);

-- Триггерная функция, которая удаляет значение цены товара в магазине если она старше новой на более 18 месяцев
create or replace function remove_too_old_coststory()
returns trigger
as $$
declare
	old_date_id integer;
	old_date date;
	new_date_id integer;
	new_date date;
	months_diff integer;
	new_avail_id integer;
begin
	new_avail_id := new.AvailabilityID;

-- Самое старое значение цены товара
	select min(make_date(prod_coststory.Year, prod_coststory.Month, 1)) into old_date
	from (select *
		  from CostStory
		  where AvailabilityID = new_avail_id) as prod_coststory;

	select prod_coststory.id into old_date_id
	from (select *
		  from CostStory
		  where AvailabilityID = new_avail_id) as prod_coststory
	where make_date(prod_coststory.Year, prod_coststory.Month, 1) = old_date;

-- Самое новое значение цены товара
	select max(make_date(prod_coststory.Year, prod_coststory.Month, 1)) into new_date
	from (select *
		  from CostStory
		  where AvailabilityID = new_avail_id) as prod_coststory;

	select prod_coststory.id into new_date_id
	from (select *
		  from CostStory
		  where AvailabilityID = new_avail_id) as prod_coststory
	where make_date(prod_coststory.Year, prod_coststory.Month, 1) = new_date;

	select (date_part('year', new_date) - date_part('year', old_date)) * 12 + (date_part('month', new_date) - date_part('month', old_date)) + 1
	into months_diff;

	if months_diff > 18 then
		delete from CostStory where AvailabilityID = new_avail_id and ID = old_date_id;
	end if;
	return new;
end
$$ language plpgsql;

drop trigger update_coststory on CostStory;
create trigger update_coststory after insert on CostStory
	for each row execute function remove_too_old_coststory();

create user "user";
grant connect on database spsr_lt_db to "user";
grant usage on schema public to "user";
grant select on table Shops, Products, Availability, Costs to "user";
alter user "user" with password 'user';

create user "analyst" with password 'analyst';
grant connect on database spsr_lt_db to "analyst";
grant usage on schema public to "analyst";
grant select on table Shops, Products, Availability, CostStory to "analyst";
grant select on table Costs to "analyst";

create user "admin" with password 'admin';
grant connect on database spsr_lt_db to "admin";
grant usage on schema public to "admin";
grant select, insert, update, delete on all tables in schema public to "admin";

drop user if exists "user";
drop user if exists "analyst";
drop user if exists "admin";

create or replace function get_products_by_shopid(shop_id integer)
returns table(ProdID integer, ProdName text, ProdType text, Cost float)
as $$
	select APC.ProductID, APC.Name, APC.ProductType, APC.Cost
	from (((select Availability.ID as AvailID, Availability.ShopID, Availability.ProductID from Availability where Availability.ShopID = shop_id) as A
	join Products on A.ProductID = Products.ID) as AP join Costs on AP.AvailID = Costs.AvailabilityID) as APC;
$$ language sql;

create or replace function get_coststory_by_shopid_prodid(shop_id integer, prod_id integer)
returns table(ID integer, Year integer, Month integer, Cost integer, AvailabilityID integer)
as $$
	select CostStory.ID, CostStory.Year, CostStory.Month, CostStory.Cost, CostStory.AvailabilityID
	from CostStory
	where AvailabilityID = 
	(select ID
	from Availability
	where ShopID = shop_id and ProductID = prod_id);
$$ language sql;

create or replace function get_salereceipts_by_shopid(shop_id integer)
returns table(SR_ID integer, FIO text, DateOfPurchase date, SummaryCost integer)
as $$
	select S.S_ID, max(FIO), max(DateOfPurchase), sum(Cost) as SummaryCost
	from ((select ID as S_ID, FIO, ShopID, DateOfPurchase from SaleReceipts where ShopID = shop_id) as SR join SaleReceiptPositions on SaleReceiptPositions.SaleReceiptID = SR.S_ID) as S join Costs on S.AvailabilityID = Costs.AvailabilityID
	group by S.S_ID;
$$ language sql;

create or replace function get_content_from_salereceipt(sr_id integer)
returns table(ProdID integer, Name text, ProductType text, Cost integer)
as $$
	select SAP.ProductID as ProdID, Name, ProductType, Cost::integer
	from ((SaleReceiptPositions join Availability on SaleReceiptPositions.AvailabilityID = Availability.ID) as SA join Products on Products.ID = SA.ProductID) as SAP join Costs on SAP.AvailabilityID = Costs.AvailabilityID
	where SaleReceiptID = sr_id;
$$ language sql;

copy Products from '...\src\db\tables_data\Products.csv' delimiter ';' CSV HEADER;
copy Shops from '...\src\db\tables_data\Shops.csv' delimiter ';' CSV HEADER;
copy SaleReceipts from '...\src\db\tables_data\SaleReceipts.csv' delimiter ';' CSV HEADER;
copy Availability from '...\src\db\tables_data\Availability.csv' delimiter ';' CSV HEADER;
copy SaleReceiptPositions from '...\src\db\tables_data\SaleReceiptPositions.csv' delimiter ';' CSV HEADER;
copy CostStory from '...\src\db\tables_data\CostStory.csv' delimiter ';' CSV HEADER;

delete from Products;
delete from Shops;
delete from SaleReceipts;
delete from Availability;
delete from SaleReceiptPositions;
delete from CostStory;