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