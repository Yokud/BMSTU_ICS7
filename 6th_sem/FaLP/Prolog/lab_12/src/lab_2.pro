domains
surname, phone, city, street, brand, color, bank = string
home, flat, cost, account, summ = integer
address = address(city, street, home, flat)


predicates
phone_book(surname, phone, address)
car(surname, brand, color, cost)
deposit(surname, bank, account, summ)

car_by_phone(phone, surname, brand, cost)
brand_by_phone(phone, brand)
bank_and_street_by_surname_and_city(surname, city, bank, street, phone)


clauses
phone_book("Malyshev", "+78005553535", address("Moscow", "Obychnaya", 11, 2)).
phone_book("Shatskiy", "+71231421433", address("Saint Peterburg", "Olenevaya", 12, 4)).
phone_book("Voronin", "+71454663765", address("Saratov", "Bychkovaya", 12, 11)).
phone_book("Gribochkov", "+71531432289", address("Tver", "Tomatnaya", 12, 7)).
phone_book("Sazonov", "+71766543721", address("Moscow", "Marmeladnaya", 13, 6)).
phone_book("Tsetochkin", "+71728332062", address("Tver", "Kabachkovaya", 16, 1)).

car("Shatskiy", "Suzuki", "red", 10000000).
car("Gribochkov", "BMW", "yellow", 15000000).
car("Voronin", "Volga", "black", 20000000).

deposit("Sazonov", "Sber", 145464235, 1000).
deposit("Shatskiy", "Tinkoff", 585642576, 20000).
deposit("Voronin", "Raif", 346536624, 100000).
deposit("Malyshev", "Sber", 364562663, 10000).

car_by_phone(Phone, Surname, Brand, Cost) :- phone_book(Surname, Phone, _), car(Surname, Brand, _, Cost).

brand_by_phone(Phone, Brand) :- car_by_phone(Phone, _, Brand, _).

bank_and_street_by_surname_and_city(Surname, City, Bank, Street, Phone) :- phone_book(Surname, Phone, address(City, Street, _, _)), deposit(Surname, Bank, _, _).


goal
%car_by_phone("+71231421433", X, Y, Z).
%brand_by_phone("+71531432289", X).
bank_and_street_by_surname_and_city("Malyshev", "Moscow", X, Y, Z).