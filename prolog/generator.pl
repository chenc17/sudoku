/*generator.pl writes an unsolved sudoku puzzle to a file*/

/*import in the solver.pl file and some libraries*/
:- consult('solver.pl').
:- consult('sudokuIO.pl').
:- use_module(library(clpfd)).
:- use_module(library(random)).

/*initial empty Sudoku grid*/
problem(2, [[_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_],
          [_,_,_,_,_,_,_,_,_]]).


/*generator*/
generator(0).
generator(N) :-

  /*get empty Sudoku grid*/
  problem(2,Rows),

  /*get unique numbers in the range 1-9*/
  randseq(5, 9, Seq),

  /*get the first row of the empty sudoku grid*/
  nth0(0, Rows, First_Row, Others),

  /*put the 1st element of Seq into the first spot in First_Row*/
  nth0(0, Seq, Val1, Rest1),
  setElement(First_Row, 0, Val1, A),
  %write(A),

  /*2nd element*/
  nth0(0, Rest1, Val2, Rest2),
  setElement(A, 1, Val2, B),
  %write(B),

  /*3rd element*/
  nth0(0, Rest2, Val3, Rest3),
  setElement(B, 2, Val3, C),
  %write(C),

  /*4th element*/
  nth0(0, Rest3, Val4, Rest4),
  setElement(C, 3, Val4, D),
  %write(D),

  /*5th element*/
  nth0(0, Rest4, Val5, Rest5),
  setElement(D, 4, Val5, E),
  %write(E),

  /*set the first row of the sudoku grid to be the newly modified row*/
  setElement(Rows,0,E,Sudoku_Grid),
  %write(Sudoku_Grid),

  /*solve the sudoku grid with 5 values to get a fully solved grid*/
  sudoku(Sudoku_Grid),
  %write(Sudoku_Grid),

  /*list of lists to single list of values*/
  flatten(Sudoku_Grid,All_Vals),
  %write(All_Vals), nl,

  /*get a list containing 50 random values between 1 and 81...these
  values correspond with the indices of the values in All_Vals that will
  be replaced with the anonymous variable*/
  randset(40, 81, Replace_Indices),
  %write(Replace_Indices), nl,

  /*now actually replace values in All_Vals accordingly*/
  create_unsolved(All_Vals, Replace_Indices, Result),
  %write('Indices'), nl,
  %write(Replace_Indices), nl,

  /*change the list back to a list of lists*/
  lst_2_lst_of_lst(Result, 9, List_Of_Lists),
  %write('1st'), nl,
  %maplist(writeln, List_Of_Lists), nl,

  /*check whether or not the puzzle is solvable*/
  (sudoku(List_Of_Lists) ->

  get_time(Curr_time),
  /*create solved puzzle file*/
  atom_concat('puzzle', Curr_time, Y),
  atom_concat(Y, '_solution.txt', SP_file_name),
  write_Puzzle_to_File(List_Of_Lists, SP_file_name),

  /*create the unsolved puzzle file name using the current time*/
  flatten(List_Of_Lists, Flat),
  create_unsolved(Flat, Replace_Indices, Unsolved_F),
  lst_2_lst_of_lst(Unsolved_F, 9, Unsolved),
  %write('Unsolved'), nl,
  %maplist(writeln, Unsolved), nl,

  atom_concat('puzzle', Curr_time, X),
  atom_concat(X, '.txt', UP_file_name),
  write_Puzzle_to_File(Unsolved, UP_file_name),
  NumLeft is N -1,
  write("Generated, "),
  write(UP_file_name), nl,
  generator(NumLeft)
  ;
  write("Wasn't able to generate this one, calling generator again!"), nl,
  generator(N)).


  /*sudoku(List_Of_Lists),
  maplist(writeln, List_Of_Lists), nl.*/

/*takes a list of sudoku values and replaces all values specified by middle list
with the anonymous variable*/
create_unsolved(Result,[],Result).
create_unsolved(Sudoku_Vals, [Idx_Replace|Rest], Result) :-
  setElement(Sudoku_Vals, Idx_Replace, _, New_Result),
  create_unsolved(New_Result, Rest, Result).

/*clauses courtesy of http://www.tek-tips.com/viewthread.cfm?qid=1504821
they collectively turn a list into a list of lists where each sublist is of length
N*/
lst_2_lst_of_lst([], _N, []).

lst_2_lst_of_lst(L, N, LL) :-
    lst_2_lst_of_lst_helper(L, 1, N, LL).

lst_2_lst_of_lst_helper([H|T], N, N, [[H]|LL]):-
    lst_2_lst_of_lst(T, N, LL).

lst_2_lst_of_lst_helper([H|T], N1 , N, [[H|TMP]|LL]):-
    N2 is N1 + 1,
    lst_2_lst_of_lst_helper(T, N2 , N, [TMP| LL]).

/* sets the Ith element of a list to Value and
stores the output in the last parameter */
setElement([_|Rest], 0, Value, [Value|Rest]).

setElement([First|Rest], I, Value, [First|End]):-
 I > 0, Next is I-1,
 setElement(Rest, Next, Value, End).
