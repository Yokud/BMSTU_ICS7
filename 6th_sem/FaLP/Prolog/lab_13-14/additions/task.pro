domains
name, sex = string
human = human(name, sex)
n = integer

predicates
is_parent(human, human)
is_grandparent(human, sex, name)

mother_nth_gen(human, n, human)

clauses
is_grandparent(human(GName, GSex), PSex, Name) :- 
	is_parent(human(GName, GSex), human(TmpName, PSex)), is_parent(human(TmpName, _), human(Name, _)).

is_parent(human("Elena", f), human("Ivan", m)).
is_parent(human("Alexey", m), human("Ivan", m)).
is_parent(human("Nina", f), human("Alexey", m)).
is_parent(human("Anatoly", m), human("Alexey", m)).
is_parent(human("Vera", f), human("Elena", f)).
is_parent(human("Evgeny", m), human("Elena", f)).

is_parent(human("Anastasya", f), human("Vera", f)).

mother_nth_gen(Human, N, Res) :- N > 0, !, is_parent(human(NewName, f), Human), NewHuman = human(NewName, f), NewN = N - 1, mother_nth_gen(NewHuman, NewN, Res).
mother_nth_gen(Human, _, Res) :- is_parent(human(NewName, f), Human), Res = human(NewName, f).

goal
mother_nth_gen(human("Ivan", m), 2, Res).