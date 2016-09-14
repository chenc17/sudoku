## Synopsis

This Sudoku program can: <br />
1.  Generate Sudoku puzzles: each puzzle will be written to its own text file… <br />
    a corresponding solution will also be written to its own text file <br />
2.  Solve Sudoku puzzles: the program can take in a text file that contains an unsolved Sudoku puzzle <br />
    and either create a file containing the solved puzzle or inform the user that the puzzle is unsolvable <br /> (see test_puzzle.txt for an example of how to format an input puzzle) <br />


## Running and Navigating Program

Running via commandline: <br />
1.	Navigate to the folder containing all the Sudoku files <br />
2.	Type: javac Run_Sudoku.java Sudoku_Generator.java SudokuParser.java SudokuSolver.java <br />
3.	Type: java Run_Sudoku <br />
<br />
Navigating (one possible use case): <br />
1.  You should see a welcome message and the option to create or solve <br />
    Sudoku puzzles <br />
2.  If you type 'create', you will be asked how many puzzles you want to create. Enter a positive integer. <br />
3.  You will then be asked to enter a difficulty level for the puzzles. <br />
    Enter 'easy', 'medium', 'difficult', or 'random'. <br />
4.  If you go to the Sudoku folder, you will now see two new folders--puzzles and puzzles_solved. <br />
    There will be one file in the puzzles folder and one corresponding solution file in the puzzles_solved folder <br /> for each puzzle generated. <br />
5.  You will now be asked if you want to run the program again. Enter 'yes' or 'no'. <br />
6.  Say you enter 'yes' and you indicate that now you want to solve a puzzle. You will be prompted <br />
    to enter the relative path of the file containing the Sudoku puzzle (this puzzle must be in the format <br />
    depicted in test_puzzle.txt). Example of relative path: './puzzles/puzzle_0_1473875255669.txt' <br />
7.  If the format of the Sudoku in the file is correct and the puzzle is solvable, you will get a message <br />
    such as 'Solved puzzle! See: ./puzzles/puzzle_0_1473875255669_solved.txt'. Otherwise you will get an error <br /> message. <br />


##Important Note##
While a Sudoku puzzle could potentially have multiple solutions, please note that
SudokuSolver will just return ONE solution.
