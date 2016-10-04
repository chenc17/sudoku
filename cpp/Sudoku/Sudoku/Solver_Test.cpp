#include "Square.h"
#include "Sudoku_Parser.h"
#include "Solver_Test.h"
#include "Sudoku_Solver.h"

using namespace std;

int Solver_Test::parser_test() {
	string infile = "test_puzzle.txt";
	string outfile = "test_puzzle_solved.txt";

	Square* square_arr = Sudoku_Parser::parseSudoku(infile);
	
	if (square_arr == nullptr) {
		return -1;
	}

	Sudoku_Solver* solver = new Sudoku_Solver();
	Square* result = solver-> solve_puzzle(square_arr);

	Sudoku_Parser::write_sudoku(result, outfile);

	delete[] square_arr;

	return 0;
}