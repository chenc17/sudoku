:- use_module(library(clpfd)).
:- consult(sudokuIO).

/* SOLVER: pass a file that contains a puzzle,
   if the puzzle is solvable, write the solution a new file. */
solve(FileName) :-
  read_Puzzle_From_File(FileName, Rows),
  sudoku(Rows),
  sub_atom(FileName, _, _, 4, FileNameMinusExtension),
  atom_concat(FileNameMinusExtension, '_solution.txt', X),
  write_Puzzle_to_File(Rows, X),
  maplist(writeln, Rows).

/* solving logic */
/*http://www.swi-prolog.org/pldoc/man?predicate=transpose/2*/
sudoku(Rows) :-
  append(Rows, Vs), Vs ins 1..9,
  maplist(all_distinct, Rows),
  transpose(Rows, Columns),
  maplist(all_distinct, Columns),
  Rows = [A,B,C,D,E,F,G,H,I],
  blocks(A, B, C), blocks(D, E, F), blocks(G, H, I),
  maplist(label, Rows).

blocks([], [], []).
blocks([A,B,C|Bs1], [D,E,F|Bs2], [G,H,I|Bs3]) :-
  all_distinct([A,B,C,D,E,F,G,H,I]),
  blocks(Bs1, Bs2, Bs3).
/* end code that was found from swi-prolog.org */
