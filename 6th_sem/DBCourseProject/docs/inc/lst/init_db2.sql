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