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