create or replace function get_products_by_shopid(shop_id integer)
returns table(ProdID integer, ProdName text, ProdType text, Cost float)
as $$
	select APC.ProductID, APC.Name, APC.ProductType, APC.Cost
	from (((select Availability.ID as AvailID, Availability.ShopID, Availability.ProductID from Availability where Availability.ShopID = shop_id) as A 
	join Products on A.ProductID = Products.ID) as AP join Costs on AP.AvailID = Costs.AvailabilityID) as APC;
$$ language sql;