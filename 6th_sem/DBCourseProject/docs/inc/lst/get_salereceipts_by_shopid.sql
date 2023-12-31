create or replace function get_salereceipts_by_shopid(shop_id integer)
returns table(SR_ID integer, FIO text, DateOfPurchase date, SummaryCost integer)
as $$
	select S.S_ID, max(FIO), max(DateOfPurchase), sum(Cost) as SummaryCost
	from ((select ID as S_ID, FIO, ShopID, DateOfPurchase from SaleReceipts where ShopID = shop_id) as SR join SaleReceiptPositions on SaleReceiptPositions.SaleReceiptID = SR.S_ID) as S join Costs on S.AvailabilityID = Costs.AvailabilityID
	group by S.S_ID;
$$ language sql;