#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <set>

#include "Square.h"
#include "Sudoku_Solver.h"

using namespace std;

Sudoku_Solver::Sudoku_Solver() {
	cout << "WTF\n";
}

/*
Square* Sudoku_Solver::solve_puzzle(Square* unsolved_puzzle) {
	if (!validate(unsolved_puzzle)) {
		return nullptr;
	}

	// create a copy of the passed in puzzle
	Square* copy = Sudoku_Solver::copy_puzzle(unsolved_puzzle);
	
	// try and find a solution to the puzzle
	Square* solved_puzzle = Sudoku_Solver::backtracking_solver(copy);

	return solved_puzzle;
}

Square* Sudoku_Solver::backtracking_solver(Square* puzzle) {
	// get the next square that hasn't been filled in yet
	Square* first_unknown = Sudoku_Solver::get_first_unknown(puzzle);

	// Base Case: if there are no unknown squares, we've solved the puzzle :)
	if (first_unknown != nullptr) {
		return puzzle;
	}

	Square unknown = *first_unknown;

	// get & loop through possible values of the unknown
	set<int> possible_values = unknown.get_possible_values();
	
	int square_no = unknown.get_square_no();

	for (int val : possible_values) {
		if (!has_conflict(puzzle, square_no, val)) {
			// assign possible value to that square, and recurse
			puzzle[square_no].set_value(val);

			// RECURSIVE CASE: if solver returns a solved puzzle, return the puzzle
			Square* solved_puzzle = backtracking_solver(puzzle);
			if (solved_puzzle != nullptr) {
				return solved_puzzle;
			}

			puzzle[square_no].set_value(Square::UNKNOWN);
		}

	}
	return nullptr;
}
*/
int Sudoku_Solver::get_first_unknown(Square* puzzle, int size) {
	// now look for the first Square of unkown value.
	for (int i = 0; i < size; i++) {
		Square tmp = puzzle[i];
		if (tmp.get_value() == Square::UNKNOWN) {
			return i;
		}
	}

	return -1;
}
/*
Square* copyPuzzle(Square* original);
bool has_conflict(Square* puzzle, int square_no, int new_value);
bool validate(Square* puzzle);


Square* solve_puzzle(Square* unsolvedPuzzle);
*/