create or replace function get_coststory_by_shopid_prodid(shop_id integer, prod_id integer)
returns table(Year integer, Month integer, Cost integer)
as $$
	select CostStory.Year, CostStory.Month, CostStory.Cost
	from CostStory
	where AvailabilityID = (select ID
	from Availability
	where ShopID = shop_id and ProductID = prod_id);
$$ language sql;