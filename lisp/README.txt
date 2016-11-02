README
This file contains information on how to generate or solve sudoku puzzles using the LISP programming language. Note that all code is in sudoku.lisp.

GENERATING PUZZLES
->Load sudoku.lisp using the correct path to the sudoku.lisp file 
i.e. (load “…Desktop/Sudoku/lisp/sudoku.lisp”)
->Call generate_puzzles with the number of puzzles you would like to create and the path to the location where the puzzles should be stored
i.e. (generate_puzzles 10 "…/Desktop/puzzles_folder/")
->The unsolved puzzles will be stored in one folder and the solved puzzles will be stored in another folder within the puzzles_folder (using the example above)

SOLVING PUZZLES
->Load sudoku.lisp
->Call solve_puzzle with the path to the file that contains the sudoku puzzle to be solved
(solve_puzzle "…/Desktop/puzzles/puzzles/puzzle1.txt")
->A file containing the solved puzzle will be placed in the same folder as the puzzle that was passed in to be solved

IMPORTANT METHODS

(defun create_solved (sudoku_grid sq_num)…
Description: Takes in sudoku_grid structure and the square to start at. Utilizes recursion to solve puzzle and returns solved sudoku grid.

(defun create_unsolved (solved_sudoku_grid num_to_remove)…
Description: Turns a solved sudoku grid into an unsolved sudoku grid by removing a certain number of squares (specified by num_to_remove). 

(defun read_sudoku_file (path)…
Description: reads in the file holding the sudoku puzzle (specified by path) character by character. If the character is in the IO_VALUES list (list of sudoku grid values that can appear in a valid sudoku puzzle file), it gets put into a list that is eventually returned. The values in the list correspond to values in a sudoku grid.

(defun write_grid_to_file (sudoku_grid filename)…
Description: writes the grid in human readable format


