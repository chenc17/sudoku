#include <ctime>
#include <iostream>

#include "Square.h"
#include "Sudoku_Parser.h"
#include "Solver_Test.h"
#include "Sudoku_Solver.h"

using namespace std;

int Solver_Test::parser_test(bool timed) {
	string infile = "test_puzzle.txt";
	string outfile = "test_puzzle_solved.txt";

	std::clock_t start;

	if (timed) 	start = std::clock();
	Square* square_arr = Sudoku_Parser::parseSudoku(infile);
	if (timed) cout << "Time to parse: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << endl;
	

	if (square_arr == nullptr) {
		return -1;
	}

	Sudoku_Solver* solver = new Sudoku_Solver();

	if (timed) start = std::clock();
	Square* result = solver-> solve_puzzle(square_arr);
	if (timed) cout << "Time to solve: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << endl;


	if (timed) start = std::clock();
	Sudoku_Parser::write_sudoku(result, outfile);
	if (timed) cout << "Time to write: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << endl;

	delete[] square_arr;

	return 0;
}