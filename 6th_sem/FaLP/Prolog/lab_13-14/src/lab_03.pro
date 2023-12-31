domains
surname, phone, city, street, color, bank, name = string
home, flat, cost, account, summ, total = integer
address = address(city, street, home, flat)

own = building(name, cost);
	region(name, cost);
	car(name, color, cost);
	water_transport(name, color, cost)

predicates
phone_book(surname, phone, address)
deposit(surname, bank, account, summ)
owner(surname, own)

all_owns(surname, name)
all_owns_cost(surname, name, cost)

all_owns_cost_type(surname, symbol, cost)
total_cost(surname, total)

clauses
phone_book("Malyshev", "+78005553535", address("Moscow", "Obychnaya", 11, 2)).
phone_book("Shatskiy", "+71231421433", address("Saint Peterburg", "Olenevaya", 12, 4)).
phone_book("Voronin", "+71454663765", address("Saratov", "Bychkovaya", 12, 11)).
phone_book("Gribochkov", "+71531432289", address("Tver", "Tomatnaya", 12, 7)).
phone_book("Sazonov", "+71766543721", address("Moscow", "Marmeladnaya", 13, 6)).
phone_book("Tsetochkin", "+71728332062", address("Tver", "Kabachkovaya", 16, 1)).

owner("Shatskiy", car("Suzuki", "red", 10000000)).
owner("Gribochkov", car("BMW", "yellow", 15000000)).
owner("Malyshev", car("Highwayman", "gray", 100000000)).
owner("Voronin", car("Volga", "black", 20000000)).
owner("Malyshev", region("Hell", 666666666)).
owner("Tsetochkin", building("Big garden", 550000)).
owner("Gribochkov", water_transport("Boatalia", "pink", 55555555)).

deposit("Sazonov", "Sber", 145464235, 1000).
deposit("Shatskiy", "Tinkoff", 585642576, 20000).
deposit("Voronin", "Raif", 346536624, 100000).
deposit("Malyshev", "Sber", 364562663, 10000).

all_owns(Surname, Name) :- owner(Surname, car(Name, _, _)).
all_owns(Surname, Name) :- owner(Surname, building(Name, _)).
all_owns(Surname, Name) :- owner(Surname, region(Name, _)).
all_owns(Surname, Name) :- owner(Surname, water_transport(Name, _, _)).

all_owns_cost(Surname, Name, Cost) :- owner(Surname, car(Name, _, Cost)).
all_owns_cost(Surname, Name, Cost) :- owner(Surname, building(Name, Cost)).
all_owns_cost(Surname, Name, Cost) :- owner(Surname, region(Name, Cost)).
all_owns_cost(Surname, Name, Cost) :- owner(Surname, water_transport(Name, _, Cost)).

all_owns_cost_type(Surname, car, Cost) :- owner(Surname, car(_, _, Cost)), !.
all_owns_cost_type(Surname, building, Cost) :- owner(Surname, building(_, Cost)), !.
all_owns_cost_type(Surname, region, Cost) :- owner(Surname, region(_, Cost)), !.
all_owns_cost_type(Surname, water_transport, Cost) :- owner(Surname, water_transport(_, _, Cost)), !.
all_owns_cost_type(_, _, 0).

total_cost(Surname, Total) :- 
		all_owns_cost_type(Surname, car, Cost1),
		all_owns_cost_type(Surname, building, Cost2),
		all_owns_cost_type(Surname, region, Cost3),
		all_owns_cost_type(Surname, water_transport, Cost4),
		Total = Cost1 + Cost2 + Cost3 + Cost4.

goal
%all_owns("Malyshev", Name).
%all_owns_cost("Shatskiy", Name, Cost).
total_cost("Gribochkov", Total).