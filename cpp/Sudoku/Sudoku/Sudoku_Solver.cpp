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
	
}

Square* Sudoku_Solver::solve_puzzle(Square* unsolved_puzzle) {
	if (!validate(unsolved_puzzle, Square::TOTAL_NUM_SQ)) {
		return nullptr;
	}

	// create a copy of the passed in puzzle
	Square* copy = Sudoku_Solver::copy_puzzle(unsolved_puzzle);
	
	// try and find a solution to the puzzle
	Sudoku_Solver::backtracking_solver(copy);

	return copy;
}

Square* Sudoku_Solver::backtracking_solver(Square* puzzle) {
	// get the next square that hasn't been filled in yet
	int first_unknown = Sudoku_Solver::get_first_unknown(puzzle, Square::TOTAL_NUM_SQ);

	// Base Case: if there are no unknown squares, we've solved the puzzle :)
	if (first_unknown == -1) {
		return puzzle;
	}

	Square unknown = *(puzzle + first_unknown);

	// get & loop through possible values of the unknown
	set<int> possible_values = unknown.get_possible_values();
	
	int square_no = unknown.get_square_no();

	for (int val : possible_values) {
		if (!has_conflict(puzzle, Square::TOTAL_NUM_SQ, square_no, val)) {
			// assign possible value to that square, and recurse
			(puzzle + square_no ) -> set_value(val);

			// RECURSIVE CASE: if solver returns a solved puzzle, return the puzzle
			Square* solved_puzzle = backtracking_solver(puzzle);
			if (solved_puzzle != nullptr) {
				return solved_puzzle;
			}

			(puzzle + square_no) -> set_value(Square::UNKNOWN);
		}

	}

	return nullptr;
}

int Sudoku_Solver::get_first_unknown(Square* puzzle, int size) {
	// now look for the first Square of unkown value.
	for (int i = 0; i < size; i++) {
		Square tmp = *(puzzle + i);
		if (tmp.get_value() == Square::UNKNOWN) {
			return i;
		}
	}

	return -1;
}

Square* Sudoku_Solver::copy_puzzle(Square* original) {
	Square* copy = new Square[Square::TOTAL_NUM_SQ];

	for (int i = 0; i < Square::TOTAL_NUM_SQ; i++) {
		int val = (original + i)->get_value();
		*(copy + i) = Square::Square(i, val);
	}

	return copy;
}

bool Sudoku_Solver::has_conflict(Square* puzzle, int puzzle_length, int square_no, int new_value) {
	Square oldSquare = *(puzzle + square_no);
	for (int i = 0; i< puzzle_length; i++){
		if ((puzzle + i) -> get_column() == oldSquare.get_column() ||
			(puzzle + i) -> get_row() == oldSquare.get_row() ||
			(puzzle + i) -> get_region() == oldSquare.get_region()) {
			if( (puzzle + i) -> get_value() == new_value) {
				return true; // conflict
			}
		}
	}

	return false;
}

bool Sudoku_Solver::validate(Square* puzzle, int puzzle_length) {
	for (int i = 0; i < puzzle_length; i++) {
		Square* tmp = (puzzle + i);
		if (!(tmp -> validate(tmp -> get_square_no(), tmp -> get_value())) ) {
			return false;
		}
	}
	return true;
}
