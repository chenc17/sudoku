#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <set>
#include <assert.h>
#include "Square.h"
#include "Sudoku_Generator.h"


using namespace std;


//Sudoku_Generator
//A Sudoku_Generator object contains the sudoku grid--an array of Square objects
//It also has methods to create a solved sudoku grid
//and an unsolved sudoku grid
//The method of most interest to those using this class is the
//get_sudoku_puzzle() method that will return an unsolved sudoku grid (array of Square objects)


//@authors Matt Hino and Christine Chen
//@date 10/2/2016

Sudoku_Generator::Sudoku_Generator()
{
	//pointer to a Square object
	sudoku_grid = new Square[Square::TOTAL_NUM_SQ];

	
	for (int idx = 0; idx<Square::TOTAL_NUM_SQ; idx++)
	{
		Square * sud_ptr = sudoku_grid + idx;
		sud_ptr->Square::Square(idx, Square::UNKNOWN);
		
		//make sure the declaration is valid
		if (sud_ptr->get_column() == Square::INVALID_VAL)
		{
			cout<<"Error in game initialization. Exiting."<<endl;
			exit(0);
		}
	}
}

void Sudoku_Generator::print_sudoku()
{

	for (int i = 0; i < Square::TOTAL_NUM_SQ; i++)
	{
		Square * sud_ptr = sudoku_grid + i;
		if (sud_ptr->get_square_no() % Square::NUM_SQ_ROW_COL == 0)
		{
			cout << endl;
		}
		cout<<sud_ptr->get_value();

	}
	cout << endl;
}

Square* Sudoku_Generator::get_sudoku_grid(void) {
	return this->sudoku_grid;
}


//int main(int argc, char **argv)
//{
//
//	cout << "Calling Sudoku_Generator Constructor!\n";
//	Sudoku_Generator test = Sudoku_Generator();
//	return 0;
//
//}

////populate sudoku_grid with "blank" Square objects
//int idx = 0;
//
//for (Square* ptr = sudoku_grid; ptr<sudoku_grid + Square::TOTAL_NUM_SQ; ptr++)
//{
//	ptr = new Square(idx, Square::UNKNOWN);
//
//
//	if (ptr->get_column() == Square::INVALID_VAL)
//	{
//		cout << "Error in game initialization. Exiting." << endl;
//		exit(EXIT_FAILURE);
//	}
//	idx++;