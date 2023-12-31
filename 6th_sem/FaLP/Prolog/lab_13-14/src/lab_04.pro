domains
name, sex = string
human = human(name, sex)

predicates
is_parent(human, human)
is_grandparent(human, sex, name)

clauses
is_grandparent(human(GName, GSex), PSex, Name) :- 
	is_parent(human(GName, GSex), human(TmpName, PSex)), is_parent(human(TmpName, _), human(Name, _)).

is_parent(human("Elena", f), human("Ivan", m)).
is_parent(human("Alexey", m), human("Ivan", m)).
is_parent(human("Nina", f), human("Alexey", m)).
is_parent(human("Anatoly", m), human("Alexey", m)).
is_parent(human("Vera", f), human("Elena", f)).
is_parent(human("Evgeny", m), human("Elena", f)).

goal
%is_grandparent(human(GName, f), _, "Ivan").
%is_grandparent(human(GName, m), _, "Ivan").
%is_grandparent(human(GName, _), _, "Ivan").
%is_grandparent(human(GName, f), f, "Ivan").
is_grandparent(human(GName, _), f, "Ivan").
