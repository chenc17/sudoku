:- use_module(library(pio)).

puzzle(1, [[_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_],
            [_,_,_,_,_,_,_,_,_]]).

/* http://stackoverflow.com/questions/4805601/read-a-file-line-by-line-in-prolog */
lines([])           --> call(eos), !.
lines([Line|Lines]) --> line(Line), lines(Lines).

eos([], []).

line([])     --> ( "\n" ; call(eos) ), !.
line([L|Ls]) --> [L], line(Ls).
/* end stackoverflow resource */

/* read from FileName, and convert the puzzle there
   to a list of lists that resembles a sudoku grid. */
fileToPuzzle(FileName, Result) :-
  phrase_from_file(lines(Ls), FileName),
  linesToSudokuRows(Ls, 0, [], Rows),
  puzzle(1, BlankRows),
  createPuzzle(Rows, BlankRows, [], Result).

/* usage:
    createPuzzle(RowsFromFileToPuzzle, blank puzzle, [], X). */
createPuzzle([],[],L1,L1).
createPuzzle([H|T],[NewH|NewT], L1, L2) :-
  addRowToPuzzleHelper(H, NewH, [], X),
  append(L1, [X], Y),
  createPuzzle(T, NewT, Y, L2).

/* takes two lists of the same length as the first two arguments.
   we override the second list with an element form the first if
   that element is not equal to 0. */
addRowToPuzzleHelper([],[], L1, L1).
addRowToPuzzleHelper([H|T], [PHead | PTail], L1, L2) :-
  (H = 0 ->
    append(L1, [PHead], X),
    addRowToPuzzleHelper(T, PTail, X, L2)
    ;
    append(L1, [H], X),
    addRowToPuzzleHelper(T, PTail, X, L2)).

/* converts a list read in from a sudoku file to a list
   of sudoku values */
listToSudokuRow([], OutList, OutList).
listToSudokuRow([H|T], OutList, List) :-
  (isValidValue(H) ->
  asciiToDigit(H, D),
  append(OutList, [D], X),
  listToSudokuRow(T, X, List)
  ;
  listToSudokuRow(T, OutList, List)).

/* convert the list of lines to list of sudoku rows */
linesToSudokuRows([], _, L1, L1).
linesToSudokuRows([H|T], RowNum, L1, L2) :-
  NextRow is RowNum + 1,
  (mod(RowNum, 4) =:= 0 ->
  linesToSudokuRows(T, NextRow, L1, L2)
  ;
  listToSudokuRow(H, [], Y),
  append(L1, [Y], X),
  linesToSudokuRows(T, NextRow, X, L2)).

/* returns true if X is 1-9 in ascii, or an unknown character '-' */
isValidValue(X) :-
  inRangeNotInclusive(X, 48, 58); X = 45.


/* take A an ascii decimal value, and turn it into a digit */
asciiToDigit(A, D) :-
  (A = 45 ->
  D is 0; % if A is unknown, set it to 0
  D is A-48).

inRangeNotInclusive(X, Lower, Upper) :-
  X > Lower, X < Upper.
