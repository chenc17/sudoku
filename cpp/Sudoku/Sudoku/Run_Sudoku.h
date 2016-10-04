#include <stdio.h>
#include <string>

#include "Square.h"
#include "Sudoku_Generator.h"
#include "Sudoku_Parser.h"
#include "Sudoku_Solver.h"


#ifndef _RUN_SUDOKU_H
#define _RUN_SUDOKU_H

class Run_Sudoku
{
	private:
		//constants
		static const string CREATE;
		static const string SOLVE;
		static const string YES;
		static const string NO;
		static const bool ERROR = false;

		//variables
		const Sudoku_Solver solver;
		const Sudoku_Generator generator;

		// methods
		bool create_puzzles(int num_puzzles, Level level);
		void welcome_user(void);			// displays nice welcome message to user of program.
		string user_goals(void);			// asks if user wants to create or solve puzzles
		int get_num_puzzles(void);			// asks user how many puzzles to create
		Level get_puzzle_level(void);		// asks user what difficulty puzzle to create
		bool is_valid_level(string lvl);	// determines if user gave a valid puzzle level
		string get_puzzle_to_solve(void);	// asks user for relative path to puzzle
		void solve_puzzle(string file);		// solves the puzzle at a given path
		string get_solution_filename(string original); // creates the filename for the solution
		void handle_invalid_response(string invalid_response, string valid_response); 
		bool respond_again(void);			// asks the user if they want to re-run the program, true if yes.



	public:
		// constructor destructor
		Run_Sudoku();
		~Run_Sudoku();

		int main();	// main entrypoint to the program.

};

#endif