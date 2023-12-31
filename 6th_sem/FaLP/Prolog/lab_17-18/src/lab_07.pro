domains
  intlist = integer*

predicates
  rec_length(integer, integer, intlist)
  length(integer, intlist)

  rec_sum(integer, integer, intlist)
  sum(integer, intlist)

  rec_oddsum(integer, integer, intlist)
  oddsum(integer, intlist)

clauses
  rec_length(Res, Len, [_ | Tail]) :- NewLen = Len + 1, !, rec_length(Res, NewLen, Tail).
  rec_length(Res, Len, []) :- Res = Len.
  length(Res, List) :- rec_length(Res, 0, List).

  rec_sum(Res, Sum, [Head | Tail]) :- NewSum = Sum + Head, !, rec_sum(Res, NewSum, Tail).
  rec_sum(Res, Sum, []) :- Res = Sum.
  sum(Res, List) :- rec_sum(Res, 0, List).

  rec_oddsum(Res, Sum, [_, Head | Tail]) :- NewSum = Sum + Head, !, rec_oddsum(Res, NewSum, Tail).
  rec_oddsum(Res, Sum, []) :- Res = Sum.
  oddsum(Res, List) :- rec_oddsum(Res, 0, List).

goal
  length(Res, [1, 2, 3, 4]).
  sum(Res, [1, 2, 3, 4]).
  oddsum(Res, [1, 2, 3, 4]).