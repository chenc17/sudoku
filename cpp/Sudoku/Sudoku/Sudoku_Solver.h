#include <set>
#include <string>
#include "Square.h"

// Sudoku_Solver.h
#ifndef _SUDOKU_SOLVER_H
#define _SUDOKU_SOLVER_H

class Sudoku_Solver {
	public: 
		Square* backtracking_solver(Square* puzzle);
		int get_first_unknown(Square* puzzle, int size);
		Square* copy_puzzle(Square* original);
		bool has_conflict(Square* puzzle, int puzzle_length, int square_no, int new_value);
		bool validate(Square* puzzle, int puzzle_length);

		Sudoku_Solver();
		Square* solve_puzzle(Square* unsolved_puzzle);
};

#endif