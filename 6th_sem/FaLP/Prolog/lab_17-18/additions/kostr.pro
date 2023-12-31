domains
intlist = integer*
  
predicates
swap1(intlist, intlist)

len(intlist, integer)
len_rec(intlist, integer, integer)

swap3(intlist, intlist)
bubble(intlist, intlist)
bubble_rec(intlist, intlist, intlist)
bubble_n(intlist, integer, intlist)

swap2(intlist, intlist)
swap2_rec(intlist, integer, intlist)
pop_nth(intlist, integer, intlist, integer)

clauses
swap1([Head1, Head2 | Tail], [Head2, Head1 | ResTail]) :- !, swap1(Tail, ResTail).
swap1([Head | Tail], [Head | ResTail]) :- swap1(Tail, ResTail).
swap1([], []).

len(List, Len) :- len_rec(List, 0, Len).
len_rec([], Len, Len) :- !.
len_rec([_|Tail], Buffer, Len) :- NewBuffer = Buffer + 1, len_rec(Tail, NewBuffer, Len).

swap3(List, Res) :- len(List, Len), HalfLen = Len div 2, bubble_n(List, HalfLen, Res).
bubble_n(List, N, Res) :- N > 0, bubble(List, NewList), NewN = N - 1, bubble_n(NewLIst, NewN, Res), !.
bubble_n(List, _, List) :- !.

bubble([H|T], Res) :- bubble_rec(T, [H], Res).
bubble_rec([], List, List) :- !.
bubble_rec([H|T], Elem, [H|TRes]) :- bubble_rec(T, Elem, TRes).

swap2(List, Res) :- len(List, Len), HalfLen = Len div 2, swap2_rec(List, HalfLen, Res), !.
swap2_rec(List, N, Res) :- N > 0, NewN = N - 1, pop_nth(List, NewN, Buffer, Elem), bubble([Elem|Buffer], NewList), swap2_rec(NewList, NewN, Res).
swap2_rec(List, _, List) :- !.

pop_nth([H|T], N, [H|TRes], Elem) :- N > 0, NewN = N - 1, pop_nth(T, NewN, TRes, Elem), !.
pop_nth([H|T], _, T, H) :- !.

goal
List = [1, 2, 3, 4, 5, 6], swap1(List, Res1), swap2(List, Res2), swap3(List, Res3).