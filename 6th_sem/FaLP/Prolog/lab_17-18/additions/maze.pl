:- use_module(library(http/http_server)).
:- use_module(library(http/http_json)).
:- use_module(library(http/http_cors)).
:- use_module(library(settings)).
:- use_module(library(http/thread_httpd)).
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/json_convert)).
:- use_module(library(option)).

:- dynamic maze_cell/4. % ’ранит данные о всех €чейках лабиринта
:- dynamic maze_size/2. % ’ранит данные о всех €чейках лабиринта

:- http_handler(/,сервис(M), [method(M),methods([get,post]),time_limit(10000)]).
:- set_setting(http:cors, [*]).

сервер :- http_server(http_dispatch, [port(8084)]).

сервис(get, Request) :-
cors_enable,
 http_parameters(Request,[val(„исло,[integer])]),
  обсчитать(„исло).


сервис(post,«апрос) :-
  cors_enable,
  http_parameters(«апрос,[val(„исло,[integer])]),
  обсчитать(„исло).


ответить(¬ставка):-
 format('Content-type: text/html~n~n~w~n', [¬ставка]).


обсчитать(Num):-
  retractall(maze_size(_,_)),
  assert(maze_size(Num, Num)),
  start(Res),
  ответить(Res).


% типы €чеек
cell_type(1, air, "O").
cell_type(2, trap, "T").
cell_type(3, enter, "S").
cell_type(4, exit, "F").

% размер лабиринта
maze_size(10, 10).

% условие дл€ €чейки
cond_cell(X, Y) :- not(clause(maze_cell(X, Y, _, _), true)), maze_size(W, H), X =< W, X >= 0, Y =< H, Y >= 0.

% условие дл€ ловушки
cond_trap(X, Y) :- Xinc is X + 1, Yinc is Y + 1, Xdec is X-1, Ydec is Y-1,
  cond_stp(Xinc,Y), cond_stp(Xdec,Y), cond_stp(X,Yinc), cond_stp(X,Ydec).
cond_stp(X, Y) :- not(clause(maze_cell(X, Y, trap, _), true)).

% решаем куда идти на основе условий
% X_offset,Y_offset - сдвиг на новую €чейку,т.е. (+2, 0) | (-2, 0) | (0, +2) или (0, -2)
where_to_go(X,Y,X_offset,Y_offset):-
  where_to_go(X,Y,X_offset,Y_offset, [(2, 0),(-2,0),(0,2),(0,-2)]).

% если перебрали все возможные направлени€ и ни одно не подошло - фейл
where_to_go(_,_,_,_,[]):-fail,!.

where_to_go(X,Y,X_offset,Y_offset, Lst) :-
  random_member((X_off_new,Y_off_new), Lst),
  Xn is X + X_off_new, Yn is Y + Y_off_new,
  select((X_off_new,Y_off_new), Lst, New_Lst),
  (cond_cell(Xn, Yn) ->
  X_offset is X_off_new, Y_offset is Y_off_new
  ;
  where_to_go(X,Y,X_offset,Y_offset, New_Lst)
  ).

%  онец генерации, стек пуст.
generate(_,_, [], Res):- draw(Res), !.

% очередной шаг. –аботаем шагом в 2 €чейки в одном выбранном направлении (чтобы между
% каждой €чейками пути всегда была стена)
generate(X, Y, S, Res):-
  % проверка была ли уже это точка занесена в базу знаний (возникает, когда берем точку из стека)
  (not(clause(maze_cell(X, Y, _, _), true)) ->
  add(X,Y)
  ;
  true
  ),
  % решаем куда дальше идти, если некуда - фейл
  where_to_go(X,Y,X_offset,Y_offset),
  % добавл€ем промежуточный узел и переходим на след шаг
  X2 is X_offset/2 + X, Y2 is Y_offset/2 + Y,
  add(X2, Y2),
  X3 is X_offset + X, Y3 is Y_offset + Y,
  generate(X3,Y3, [(X3,Y3) | S], Res), !.

% если не смогли найти новую точку в where_to_go, то берем последнюю точку из стека
generate(X, Y, [(X,Y)|Ss], Res):-
  maze_size(_, H), Hdec is H-1,
  % если это нижн€€ грань, то добавим выход
  ( Y = Hdec->
  add_exit(X, H)
  ;
  true
  ),	generate(X, Y, Ss, Res), !.

% добавл€ем единственный выход
add_exit(X, Y):- not(clause(maze_cell(_,_,exit,_), true)),
  assert(maze_cell(X,Y,exit, -1)).

% добавл€ем €чейку
add(X, Y) :-
% провер€ем можно ли там ставить
cond_cell(X,Y),
% провер€ем шанс ловушки и условие ловушки, иначе воздух
random_between(1, 10, TrapChance),
( TrapChance < 3, cond_trap(X,Y) ->
  assert(maze_cell(X,Y,trap, TrapChance))
  ;
  assert(maze_cell(X,Y,air, -1))
).


draw(Res) :-
    start2(Res).

start(Res):-
retractall(maze_cell(_,_,_,_)),
assert(maze_cell(1,0,enter, -1)),
generate(1,1,[(1,1)], Res).



internal2(List, W, X, Y, ResList) :-
  X < W,


  format(atom(WWWW), '~d', W),
  atom_number(WWWW, WW),

  format(atom(WWW), '~d', W),
  atom_number(WWW, WW),

  format(atom(XXX), '~d', X),
  atom_number(XXX, XX),

  format(atom(YYY), '~d', Y),
  atom_number(YYY, YY),
  NEWXX is XX + 1,



  (clause(maze_cell(XX, YY, _, _), true) ->
    maze_cell(XX, YY, Type, _),
    cell_type(_, Type, C),
    format(atom(R1), '~w', C)
  ;
    % стена
    format(atom(R1), '~w', "W")
  ),

  append(List, [R1], NewList),

  NewX = X + 1,
  internal2(NewList, W, NewX, Y, ResList),
  !.

internal2(List, _, _, _, ResList) :-
  format(atom(R1), '~w', "W"),
  append(List, [R1], NewList),
  ResList = NewList,
  !.


startInternal(List2, W, H, X, Y, Res) :-
  Y < H + 1,
  internal2([], W, 0, Y, ResList),
  append(List2, [ResList], ResList2),
  Ynew = Y + 1,
  startInternal(ResList2, W, H, X, Ynew, Res),
  !.

startInternal(List2, _, _, _, _, Res) :- Res = List2, !.


start2(Res) :-
  maze_size(W, H),
  startInternal([], W, H, 0, 0, Res).

