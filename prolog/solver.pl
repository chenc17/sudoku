

/*http://www.swi-prolog.org/pldoc/man?predicate=transpose/2*/
:- use_module(library(clpfd)).

/* check a list and verify that it has no repeated elements*/
all_distinct2([]).
all_distinct2([First|Rest]) :-
   all_distinctHelper(First, Rest),
   allDistinct2(Rest).

all_distinctHelper(_, []).
all_distinctHelper(X, [First|Rest]) :-
    X \= First,
    all_distinctHelper(X, Rest).

sudoku(Rows) :-
  append(Rows, Vs), Vs ins 1..9,
  maplist(all_distinct, Rows),
  transpose(Rows, Columns),
  maplist(all_distinct, Columns),
  Rows = [A,B,C,D,E,F,G,H,I],
  blocks(A, B, C), blocks(D, E, F), blocks(G, H, I),
  maplist(label, Rows).

/* set's the Ith element of a list to Value and
stores the output in the last parameter */
setElement([_|Rest], 0, Value, [Value|Rest]).
setElement([First|Rest], I, Value, [First|End]):-
  I > 0, Next is I-1,
  setElement(Rest, Next, Value, End).

blocks([], [], []).
blocks([A,B,C|Bs1], [D,E,F|Bs2], [G,H,I|Bs3]) :-
  all_distinct([A,B,C,D,E,F,G,H,I]),
  blocks(Bs1, Bs2, Bs3).

  problem(1, [[7,_,_,8,_,_,_,_,_],
            [3,_,_,_,_,_,_,_,_],
            [5,_,_,_,_,9,_,_,_],
            [1,_,_,_,_,_,_,_,_],
            [4,_,_,_,_,_,_,_,_],
            [8,_,_,_,_,_,7,_,_],
            [2,_,_,_,_,_,_,9,_],
            [6,_,_,_,_,_,_,_,_],
            [9,_,_,_,_,_,_,_,_]]).
