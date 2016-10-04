#include <set>
#include <string>
#include "Square.h"

// Sudoku_Parser.h
#ifndef _SUDOKU_PARSER_H
#define _SUDOKU_PARSER_H

using namespace std;

class Sudoku_Parser {

	public: 
		static const string LINE_SEPARATOR;
		static const int REGION_SIZE = 3;
		static const int ERROR = -1;

		// public methods
		static int Sudoku_Parser::write_sudoku(Square* puzzle, string fileName);
		static Square* parseSudoku(string fileName);

};

#endif