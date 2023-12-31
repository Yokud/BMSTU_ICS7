domains
name = string
surname = string
phone = string
university = string
group = string
course = integer

predicates
student(name, surname, phone, university, group, course)

clauses
student("Ivan", "Malyshev", "+78005553535", "BMSTU", "IU7-61B", 3).
student("Nikita", "Shatskiy", "+79996663232", "BMSTU", "IU7-61B", 3).
student("Ivan", "Ivanov", "+79543432255", "MIPT", "LFI-14", 1).
student("Sergey", "Simonov", "+79342221314", "MAI", "ACS-32", 2).
student("Ivan", "Malyshev", "+78005553535", "MIPT", "FIVT-5", 5).
student("Petr", "Grinev", "+79456784433", "MSU", "VMK-4", 4).
student("Maria", "Bublikova", "+79554327788", University, Group, Course) :- student(_, "Ivanov", _, University, Group, Course).

goal
student("Ivan", Surname, Phone, University, Group, Course).
student(Name, Surname, Phone, "BMSTU", _, 3).
student("Ivan", _, _, _, "IU7-61B", _).