#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <set>
#include <algorithm>

#include "Square.h"
#include "Sudoku_Parser.h"

using namespace std;

const string Sudoku_Parser::LINE_SEPARATOR = "+=======================+";

//Sudoku_Parser
//write_sudoku method takes an array of Square objects and prints the value of each Square in proper
//sudoku grid format to the file specified
//parseSudoku takes the file given and attempts to parse the sudoku puzzle in the file into
//an array of Square objects 

//@authors Matt Hino and Christine Chen
//@date 10/1/2016

int Sudoku_Parser::write_sudoku(Square* puzzle, string fileName) {

	ofstream myfile(fileName);

	// if we were unable to open the file, exit out gracefully
	if (!myfile.is_open()) {
		return Sudoku_Parser::ERROR;
	}

	// opened file nicely (:
	for (int square_no = 0; square_no < Square::TOTAL_NUM_SQ; square_no++){

		// write a new line if we've written a full row
		if (square_no%Square::NUM_SQ_ROW_COL == 0 && square_no != 0) {
			myfile << "| " << endl;
		}

		// write a horizontal bar to separate regions
		if (square_no % (Square::NUM_SQ_ROW_COL * Sudoku_Parser::REGION_SIZE) == 0) {
			myfile << Sudoku_Parser::LINE_SEPARATOR << endl;
		}

		// write a pipe to separate the regions
		if (square_no%Sudoku_Parser::REGION_SIZE == 0) {
			myfile << "| ";
		}

		int numberToWrite = (puzzle + square_no) -> get_value();
		if (numberToWrite == Square::UNKNOWN) {
			myfile << "- ";
		}
		else {
			myfile << numberToWrite << " ";
		}
	}

	myfile << "| " << endl << Sudoku_Parser::LINE_SEPARATOR;
	myfile.close();
	return 0;
}

/*
* This method reads in a sudoku file, creates, and intializes an array of squares
* then returns a pointer to that square array.
*/
Square* Sudoku_Parser::parseSudoku(string file_name) {

	ifstream myfile(file_name);
	// make sure to exit if we aren't able to open the file nicely.
	if (!myfile.is_open()) {
		return nullptr;
	}

	Square* square_arr = new Square[Square::TOTAL_NUM_SQ];
	string line;
	int square_no = 0;

	while (getline(myfile, line)) {
		if (line.size() > 0 && (line[0] != '+')) {

			// get rid of spacing characters and dashes
			replace(line.begin(), line.end(), '|', ' ');
			replace(line.begin(), line.end(), '-', '0');

			// iterate through the string, if we come across a number, then add a square
			// with that value to the square array.
			for (int i = 0; i < line.size(); i++) {
				if (line[i] != ' ') {
					int value = atoi(&line[i]);
					*(square_arr + square_no) = Square(square_no, value);
					square_no++;
				}
			}
		}
	}

	myfile.close();
	return square_arr;
}


