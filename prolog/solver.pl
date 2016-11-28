
/*http://www.swi-prolog.org/pldoc/man?predicate=transpose/2*/
:- use_module(library(clpfd)).

sudoku(Rows) :-
  append(Rows, Vs), Vs ins 1..9,
  maplist(all_distinct, Rows),
  rows_to_cols(Rows, Columns),
  maplist(all_distinct, Columns),
  Rows = [A,B,C,D,E,F,G,H,I],
  blocks(A, B, C), blocks(D, E, F), blocks(G, H, I),
  maplist(label, Rows).

blocks([], [], []).
blocks([A,B,C|Bs1], [D,E,F|Bs2], [G,H,I|Bs3]) :-
  all_distinct([A,B,C,D,E,F,G,H,I]),
  blocks(Bs1, Bs2, Bs3).


/*http://stackoverflow.com/questions/4280986/how-to-transpose-a-matrix-in-prolog*/
rows_to_cols([],[]).

/*Isolate the first row and specify the result desired (columns)*/
rows_to_cols([FIRST_ROW|OTHER_ROWS], COLUMNS) :-
  rows_to_cols(FIRST_ROW, [FIRST_ROW|OTHER_ROWS], COLUMNS).

rows_to_cols([],_,[]).
/*Isolate the tail of the first row, all rows, and the first column*/
rows_to_cols([_|REST_FR],ALL_ROWS,[COL_1|OTHER_COLS]) :-
  /*call lists_firsts_rests with all the rows, the first column, and specify a variable to hold the result*/
  lists_firsts_rests(ALL_ROWS,COL_1,RESULT),
  /*recurse with the rest of the first row, the result that came back in from lists_firsts_rests
  (all rows with the same amount of elements shaved off the front of each row), and the rest of the ultimate columns*/
  rows_to_cols(REST_FR, RESULT, OTHER_COLS).

lists_firsts_rests([],[],[]).
/*Isolate the head of the first row, make that the head of the first column, put the tail of the first row in the result variable*/
lists_firsts_rests([[HF|REST_FIRST]|OTHER],[HF|REST_COL],[REST_FIRST|OTHERS_REST]) :-
  /*Recurse with the rest of the rows, the rest of the column, and the rest of the result*/
  lists_firsts_rests(OTHER, REST_COL, OTHERS_REST).


problem(1, [[_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,3,_,8,5],
          [_,_,1,_,2,_,_,_,_],
          [_,_,_,5,_,7,_,_,_],
          [_,_,4,_,_,_,1,_,_],
          [_,9,_,_,_,_,_,_,_],
          [5,_,_,_,_,_,_,7,3],
          [_,_,2,_,1,_,_,_,_],
          [_,_,_,_,4,_,_,_,9]]).
