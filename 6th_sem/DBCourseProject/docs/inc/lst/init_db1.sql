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