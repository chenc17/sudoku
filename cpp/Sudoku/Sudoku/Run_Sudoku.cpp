#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <direct.h>
#include <stdio.h>
#include <set>
#include <ctime>
#include <algorithm>

using namespace std;

#include "Run_Sudoku.h"
#include "Sudoku_Generator.h"
#include "Sudoku_Parser.h"
#include "Sudoku_Solver.h"
#include "Square.h"

//constants
const string Run_Sudoku::CREATE = "CREATE";
const string Run_Sudoku::SOLVE = "SOLVE";
const string Run_Sudoku::YES = "YES";
const string Run_Sudoku::NO = "NO";
const bool  Run_Sudoku::OOPS = false;

// constants for comparing what level the user inputted
const string EASY = "EASY";
const string MEDIUM = "MEDIUM";
const string DIFFICULT = "DIFFICULT";
const string RANDOM = "RANDOM";

//variables
Sudoku_Solver* solver;
Sudoku_Generator* generator;

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
	Run_Sudoku * runner = new Run_Sudoku();
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
			Level difficulty = runner->get_puzzle_level();
			cout << "Creating " << num_to_create << " puzzles of " << difficulty << " difficulty" << endl;

			// create the puzzles and let the user know the result.
			bool status = runner->create_puzzles(num_to_create, difficulty);
			if (status != Run_Sudoku::OOPS) {
				cout << endl;
				cout << "Done creating puzzles! Have fun solving them!" << endl;
			}
			else {
				cout << endl;
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



	return 0;
} // main

// displays nice welcome message to user of program.
void Run_Sudoku::welcome_user(void) {
	cout << "Welcome to the Sudoku Suite!" << endl;
	cout << "This program is designed so that you can create ";
	cout << "and solve some" << endl << "sudoku puzzles ";
	cout << "or solved an already created one." << endl << endl;
}

// asks if user wants to create or solve puzzles
string Run_Sudoku::user_goals() {
	cout << "Would you like to 'create' or 'solve'?" << endl;

	string result;
	getline(cin, result);
	
	// transform string to upper case
	transform(result.begin(), result.end(), result.begin(), toupper);
	
	cout << endl;

	// keep asking until the user types 'create' or 'solve'
	while (!(Run_Sudoku::CREATE.compare(result) == 0 ||
			 Run_Sudoku::SOLVE.compare(result) == 0)) {
		handle_invalid_response(result, "'" + Run_Sudoku::CREATE + "' or '" + Run_Sudoku::SOLVE + "'");
		getline(cin, result);
		transform(result.begin(), result.end(), result.begin(), toupper);
		cout << endl;
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
		cout << endl;
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
Level Run_Sudoku::get_puzzle_level(void) {
	cout << "Would you like your puzzle difficulty to be" << endl;
	cout << "'easy', 'medium', 'difficult', or 'random'?" << endl;

	string difficulty;
	// until the user types in one of the specified difficulties, continue to ask
	getline(cin, difficulty);
	transform(difficulty.begin(), difficulty.end(), difficulty.begin(), toupper);

	cout << endl;

	Level lvl = Run_Sudoku::string_to_level(difficulty);

	while (lvl == none) {
		handle_invalid_response(difficulty, "'easy', 'medium', 'difficult', or 'random'?");
		getline(cin, difficulty);
		transform(difficulty.begin(), difficulty.end(), difficulty.begin(), toupper);
		lvl = Run_Sudoku::string_to_level(difficulty);
	}
	
	return lvl;
}

// asks user for relative path to puzzle
string Run_Sudoku::get_puzzle_to_solve(void) {
	cout << "What is the relative path to the puzzle you want to solve?" << endl;
	string path;

	getline(cin, path);
	cout << endl;
	return path;
}

// asks user if they want to run the program again
bool Run_Sudoku::ask_run_again(void) {
	cout << endl;
	cout << "Would you like to run the program again?" << endl;
	cout << "Please enter 'yes' or 'no'" << endl;

	string response;
	getline(cin, response);
	transform(response.begin(), response.end(), response.begin(), toupper);

	cout << endl;
	while (YES.compare(response) != 0 && NO.compare(response) != 0) {
		handle_invalid_response(response, "'" + YES + "' or '" + NO + "'");
		getline(cin, response);
		transform(response.begin(), response.end(), response.begin(), toupper);
		cout << endl;
	}

	if (YES.compare(response) == 0) {
		return true;
	}
	else {
		return false;
	}
}

// solves the puzzle at a given path
void Run_Sudoku::solve_puzzle(string file) {
	Square* unsolved_puzzle = Sudoku_Parser::parseSudoku(file);
	if (unsolved_puzzle == nullptr) {
		cout << "Next time please enter a valid file name" << endl;
		return;
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

bool Run_Sudoku::create_puzzles(int num_puzzles, Level level) {
	const char puzzle_path[] = "./puzzles";
	const char solution_path[] = "./solutions";

	// create directories to hold the puzzles and solutions.
	if (create_folder(puzzle_path) == false) return false;
	if (create_folder(solution_path) == false) return false;

	// now create the puzzles and solutions. save them to 
	// appropriate folders.
	Square* puzzle;
	Square* solved;
	for (int i = 0; i < num_puzzles;) {
		puzzle = generator->get_sudoku_puzzle(level);

		if (puzzle != nullptr) {
			solved = solver->solve_puzzle(puzzle);
			if (solved != nullptr) {
				long now = (long)time(0);

				string puzzle_name = "./puzzles/puzzle_" + to_string(i) + "_" + to_string(now) + ".txt";
				string solution_name = "./solutions/puzzle_" + to_string(i) + "_" + to_string(now) + "_solution_" + ".txt";

				int result_p = Sudoku_Parser::write_sudoku(puzzle, puzzle_name);
				int result_s = Sudoku_Parser::write_sudoku(solved, solution_name);

				if (result_p == 0 && result_s == 0) {
					cout << "Created puzzle " << to_string(i + 1) << " of " << to_string(num_puzzles) << "." << endl;
					i++; // only increment if we can find a solution
				}
			}
		}
	}
	generator->refresh_sudoku_grid();
	return true;
}

// try and create a directory and if there is an err, inspect it
// if it's a path not found err, that's not good. otherwise
// we should be ok.
bool Run_Sudoku::create_folder(const char path[]) {
	if (_mkdir(path) != 0) {
		if (errno == ENOENT) {
			return false;
		}
	}

	return true;
}



// converts a string to the specified lvl. if the lvl is not easy,
// medium, difficult, or random, return none and handle accordingly.
Level Run_Sudoku::string_to_level(string lvl) {
	// upper case
	transform(lvl.begin(), lvl.end(), lvl.begin(), toupper);

	if (EASY.compare(lvl) == 0) {
		return easy;
	}
	else if (MEDIUM.compare(lvl) == 0) {
		return medium;
	}
	else if (DIFFICULT.compare(lvl) == 0) {
		return difficult;
	}
	else if (RANDOM.compare(lvl) == 0) {
		return random;
	}
	else {
		return none;
	}
}

void Run_Sudoku::handle_invalid_response(string invalid_response, string valid_response) {
	cout << "Sorry, '" + invalid_response + "' is not a valid response." << endl;
	cout << "Please enter one of the following: " << endl;
	cout << valid_response << endl;
}

string Run_Sudoku::get_solution_filename(string original) {
	return original + "_solved.txt";
}
