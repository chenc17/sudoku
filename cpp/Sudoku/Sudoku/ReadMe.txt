========================================================================
    CONSOLE APPLICATION : Sudoku Project Overview
========================================================================

This file contains a summary of the important files in the project as well as information on how to run the project.

Run_Sudoku.cpp 
Run_Sudoku.h
	main method in Run_Sudoku walks user through process of creating puzzles or solving a sudoku puzzle  		
	
Sudoku_Parser.cpp 
Sudoku_Parser.h
	write_sudoku() method takes an array of Square objects and prints the value of each Square in proper
	sudoku grid format to the file specified
	parseSudoku() takes the file given and attempts to parse the sudoku puzzle in the file into
	an array of Square objects 

Sudoku_Solver.cpp 
Sudoku_Solver.h
	The most important public method is the solve_puzzle() method that takes an unsolved puzzle and returns a solved puzzle. The algorithm used here is “backtracking 		recursive”, meaning the algorithm will keep filling in blank squares until it hits a 	dead end (all values for a square have been tried)…at that point it will back track 		and recurse again to try to find a solution.
	The solver will declare a puzzle unsolvable after it has gone through every potential possible value for every empty square without finding a solution. 

Sudoku_Generator.cpp
Sudoku_Generator.h
	A Sudoku_Generator object contains a sudoku grid--an array of Square objects.
	The most important public method is the get_sudoku_puzzle() method that will return an unsolved sudoku grid (array of Square objects).
	The unsolved sudoku grid is obtained by first creating a completely solved Sudoku 
	and then “erasing” the values for certain squares (according to the algorithm created
	by Andrew Stuart: http://www.sudokuwiki.org/Sudoku_Creation_and_Grading.pdf).

Square.cpp
Square.h
	A square object is one box in a Sudoku grid. It has a column, row, 3x3 region, value, and square number. See Square.h for the public operations associated with a Square 		object (i.e. getters and setters).
   
Test.cpp
	Class that tests methods in Solver, Generator, and Parser
	Currently Test main method is the entry point for this project (calls Runner main method)

/////////////////////////////////////////////////////////////////////////////
Running the project:
-Open Visual Studio 2013
-File>Open>Project/Solution 
-Navigate to the project and open Sudoku.sln 
-Build solution
-Start Without Debugging
-Follow prompts on screen
/////////////////////////////////////////////////////////////////////////////
