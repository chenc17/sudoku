#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <set>
#include <algorithm>

using namespace std;

#include "Run_Sudoku.h"
#include "Sudoku_Generator.h"
#include "Sudoku_Parser.h"
#include "Sudoku_Solver.h"
#include "Square.h"

//constants
const string Run_Sudoku::CREATE = "CREATE";
const string SOLVE = "SOLVE";
const string YES = "YES";
const string NO = "NO";
const bool ERROR = false;

//variables
Sudoku_Solver* solver;
Sudoku_Generator* generator;

bool create_puzzles(int num_puzzles, Level level);
bool is_valid_level(string lvl);	// determines if user gave a valid puzzle level
string get_solution_filename(string original); // creates the filename for the solution
void handle_invalid_response(string invalid_response, string valid_response);
bool ask_run_again(void);			// asks the user if they want to re-run the program, true if yes.


// constructor destructor
Run_Sudoku::Run_Sudoku() {
	solver = new Sudoku_Solver();
	generator = new Sudoku_Generator();
}

Run_Sudoku::~Run_Sudoku() {
	delete solver;
	delete generator;
}

int Run_Sudoku::main() {
	Run_Sudoku* runner = new Run_Sudoku();
	bool do_again = false;

	// welcome user to the program, describe the functionality
	runner->welcome_user();

	do {
		string user_goal = runner->user_goals();

		//	If user wants to create puzzles, give them the following options:
		//	1. how many, 2. what difficulty
		if (user_goal.compare(Run_Sudoku::CREATE) == 0) {
			// get the information from the user
			int num_to_create = runner->get_num_puzzles();
			string difficulty = runner->get_puzzle_level();
			cout << "Creating " << num_to_create << "puzzles of " << difficulty << " difficulty" << endl;

			// create the puzzles and let the user know the result.
			bool status = runner->create_puzzles(num_to_create, difficulty);
			if (status != Run_Sudoku::ERROR) {
				cout << "Done creating puzzles! Have fun solving them!" << endl;
			}
			else {
				cout << "Whoops! Something went wrong :(" << endl;
			}
		}
		// ask the user which puzzle they would like to solve, and solve it
		else if (user_goal.compare(Run_Sudoku::SOLVE) == 0) {
			string file_name = runner->get_puzzle_to_solve();
			runner->solve_puzzle(file_name);
		}
		else {
			cout << "Whoops! Something went wrong here. :( " << endl;
		}

		// ask if the user wants to repear the process over again.
		do_again = runner->ask_run_again();
	} while (do_again);

} // main

// displays nice welcome message to user of program.
void Run_Sudoku::welcome_user(void) {
	cout << "Welcome to the Sudoku Suite!" << endl;
	cout << "This program is designed so that you can create ";
	cout << "and solve some" << endl << "sudoku puzzles ";
	cout << "or solved an already created one." << endl;
}

// asks if user wants to create or solve puzzles
string Run_Sudoku::user_goals() {
	cout << "Would you like to 'create' or 'solve'?" << endl;

	string result;
	getline(cin, result);
	
	// transform string to upper case
	transform(result.begin(), result.end(), result.begin(), toupper);
	
	// keep asking until the user types 'create' or 'solve'
	while (!(Run_Sudoku::CREATE.compare(result) == 0 ||
			 Run_Sudoku::SOLVE.compare(result) == 0)) {
		handle_invalid_response(result, "'" + Run_Sudoku::CREATE + "' or '" + Run_Sudoku::SOLVE + "'");
		getline(cin, result);
		transform(result.begin(), result.end(), result.begin(), toupper);
	}

	return result;
}

// asks user how many puzzles to create
int Run_Sudoku::get_num_puzzles(void) {
	cout << "How many puzzles would you like to create?" << endl;
	string result;

	bool valid = false;
	int num_puzzles = -1;

	// ask the user how many puzzles they want to create
	// if the input is not an integer, handle nicely and ask again.
	while (!valid) {
		getline(cin, result);

		try{
			num_puzzles = stoi(result);

			if (num_puzzles > 0) {
				valid = true;
			}

		}
		// handle the appropriate erros
		catch (invalid_argument ia){
			handle_invalid_response(result, "Any positive integer");
		}
		// if they enter a number that's too big
		catch (out_of_range oor) {
			handle_invalid_response(result, "Must be less than" + INT_MAX);
		}
	}
	
	return num_puzzles;
}

// asks user what difficulty puzzle to create
string  Run_Sudoku::get_puzzle_level(void) {
	cout << "Would you like your puzzle difficulty to be" << endl;
	cout << "'easy', 'medium', 'difficult', or 'random'?" << endl;

	string difficulty;
	// until the user types in one of the specified difficulties, continue to ask
	getline(cin, difficulty);
	transform(difficulty.begin(), difficulty.end(), difficulty.begin(), toupper);
	while (!is_valid_level(difficulty)) {
		handle_invalid_response(difficulty, "'easy', 'medium', 'difficult', or 'random'?");
		getline(cin, difficulty);
		transform(difficulty.begin(), difficulty.end(), difficulty.begin(), toupper);
	}
	
	return difficulty;
}

// asks user for relative path to puzzle
string Run_Sudoku::get_puzzle_to_solve(void) {
	cout << "What is the relative path to the puzzle you want to solve?" << endl;
	string path;

	getline(cin, path);

	return path;
}

// solves the puzzle at a given path
void Run_Sudoku::solve_puzzle(string file) {
	Square* unsolved_puzzle = Sudoku_Parser::parseSudoku(file);
	if (unsolved_puzzle == nullptr) {
		cout << "Next time please enter a valid file name" << endl;
	}

	Square* solved = solver->solve_puzzle(unsolved_puzzle);
	if (solved == nullptr) {
		cout << "Unable to solve puzzle!" << endl;
	} else{
		string solution_file = get_solution_filename(file);
		Sudoku_Parser::write_sudoku(solved, solution_file);
		cout << "Solved puzzle! See: " << solution_file << endl;
	}
}
