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