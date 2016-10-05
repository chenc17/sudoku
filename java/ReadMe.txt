Running and Navigating Java Sudoku

Running via commandline: 
1. Navigate to the folder containing all the Sudoku files 
2. Type: javac Run_Sudoku.java Sudoku_Generator.java SudokuParser.java SudokuSolver.java 
3. Type: java Run_Sudoku 

Navigating (one possible use case): 
1. You should see a welcome message and the option to create or solve 
Sudoku puzzles 
2. If you type 'create', you will be asked how many puzzles you want to create. Enter a positive integer. 
3. You will then be asked to enter a difficulty level for the puzzles. 
Enter 'easy', 'medium', 'difficult', or 'random'. 
4. If you go to the Sudoku folder, you will now see two new folders--puzzles and puzzles_solved. 
There will be one file in the puzzles folder and one corresponding solution file in the puzzles_solved folder 
for each puzzle generated. 
5. You will now be asked if you want to run the program again. Enter 'yes' or 'no'. 
6. Say you enter 'yes' and you indicate that now you want to solve a puzzle. You will be prompted 
to enter the relative path of the file containing the Sudoku puzzle (this puzzle must be in the format 
depicted in test_puzzle.txt). Example of relative path: './puzzles/puzzle_0_1473875255669.txt' 
7. If the format of the Sudoku in the file is correct and the puzzle is solvable, you will get a message 
such as 'Solved puzzle! See: ./puzzles/puzzle_0_1473875255669_solved.txt'. Otherwise you will get an error 
message. 

Important Note

While a Sudoku puzzle could potentially have multiple solutions, please note that SudokuSolver will just return ONE solution.