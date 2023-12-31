domains
name = string
phone = string
city = string
street = string
home = integer

predicates
record(name, phone, city, street, home)

clauses
record("Ivan", "+79631416412", "Moscow", "Frunzenskaya", 15).
record("Peter", "+79123456789", "Saint Peterburg", "Nevskaya", 27).
record("Sergey", "+79335436781", "Moscow", "Obychnaya", 5).
record("Marya", "+79027531212", "Moscow", "Yartsevskaya", 13).
record("Michail", "+79635432121", "Tver", "Chekhovskaya", 33).

goal
record(Name, Phone, "Moscow", Street, Home).