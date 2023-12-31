domains
	num = integer

predicates
	fact(num, num)
	rec_fact(num, num, num)

	fib(num, num)
	rec_fib(num, num, num, num)

clauses
	rec_fact(N, Res, Acc) :- N > 1, !, NewN = N - 1, NewAcc = Acc * N, rec_fact(NewN, Res, NewAcc).
	rec_fact(_, Res, Acc) :- Res = Acc.
	fact(N, Res) :- rec_fact(N, Res, 1).
	
	rec_fib(N, F1, F2, Res) :- N > 2, !, NewF1 = F2, NewF2 = F1 + F2, NewN = N - 1, rec_fib(NewN, NewF1, NewF2, Res).
	rec_fib(_, _, B, Res) :- Res = B.
	fib(N, Res) :- rec_fib(N, 1, 1, Res).

goal
	fact(4, Res).
	fib(7, Res).