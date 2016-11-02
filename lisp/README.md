## Synopsis:

This file contains information on how to generate or solve sudoku puzzles using the LISP programming language. Note that all code is in the file: sudoku.lisp.

In order to run the code, first load the program. Be sure to use the __*full path*__ to the file.

i.e. (load “/Users/username/Desktop/Sudoku/lisp/sudoku.lisp”)

## How to generate puzzles:

#### Usage: (generate\_puzzles N path)

**Parameters:**

* N - the number of puzzles you would like to generate\_puzzles
* path - the full path to where you would like the puzzles and their solutions to be saved

*Note: If you passed in ".../Desktop", then the program will create two directories ".../Desktop/puzzles" and ".../Desktop/solutions" and save the puzzles and their solutions.*

## How to solve a puzzle:

#### Usage: (solve\_puzzle path)

**Parameters:**

* path - the full path to where you would like the puzzles and their solutions to be saved

*Note: If you passed in ".../Desktop/puzzle1.txt" as the path, then the program will try and find a solution to puzzle1.txt. It will then create a file at ".../Desktop/puzzle1.txt\_solution.txt" that contains the solution to the puzzle (if one exists).*

## Important Methods:

Below, you'll find descriptions for some of the more complex methods being used in the program. If you are just trying to create or solve sudoku puzzles, the following methods are not necessary to understand.

#### Usage: (create\_solved sudoku\_grid sq\_num)

**Description:** Takes in sudoku_grid structure and the square to start at. Utilizes recursion to solve puzzle and returns solved sudoku grid.

**Parameters:**

* sudoku\_grid - our representaion of a sudoku puzzle
* sq\_num - the current square we are evaluating

#### Usage: (create\_unsolved solved\_sudoku\_grid num\_to\_remove)

**Description:** Turns a solved sudoku grid into an unsolved sudoku grid by removing a certain number of squares (specified by num\_to\_remove).

**Parameters:**

* sudoku\_grid - our representation of a sudoku puzzle
* num\_to\_remove - the number of unknown squares you would like to have

#### Usage: (read\_sudoku\_file path)

**Description:** reads in the file holding the sudoku puzzle (specified by path) character by character. If the character is in the IO_VALUES list (list of sudoku grid values that can appear in a valid sudoku puzzle file), it gets put into a list that is eventually returned. The values in the list correspond to values in a sudoku grid.

#### Usage: (write\_grid\_to\_file sudoku\_grid filename)

**Description:** writes the grid in human readable format

**Parameters:**

* sudoku_grid - our representation of a sudoku puzzle
* filename - the *full path* of where the puzzle should be written
