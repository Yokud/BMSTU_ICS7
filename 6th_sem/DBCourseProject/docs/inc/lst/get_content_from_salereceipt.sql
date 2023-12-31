create or replace function get_content_from_salereceipt(sr_id integer)
returns table(ProdID integer, Name text, ProductType text, Cost integer)
as $$
	select SAP.ProductID as ProdID, Name, ProductType, Cost::integer
	from ((SaleReceiptPositions join Availability on SaleReceiptPositions.AvailabilityID = Availability.ID) as SA join Products on Products.ID = SA.ProductID) as SAP join Costs on SAP.AvailabilityID = Costs.AvailabilityID
	where SaleReceiptID = sr_id;
$$ language sql;