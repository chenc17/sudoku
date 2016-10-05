#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <set>
#include <assert.h>
#include "Square.h"
#include "Sudoku_Solver.h"
#include "Sudoku_Generator.h"
#include "Solver_Test.h"
#include "Run_Sudoku.h"

using namespace std;


//Test
//This class mainly contains tests that verify
//the robustness and accuracy of the Square class
//setter methods

//@authors Matt Hino and Christine Chen
//@date 10/1/2016

class Test
{
  private:
     static const int TOO_BIG = 81;
	   static const int TOO_SMALL = -1;
	   static const int VALID = 5;

  public:
    static void validateHandlesAllValidParametersTest(void);
    static void validateHandlesTooLargeSquareNumTest(void);
    static void testToString(void);
	static void testFindFirstUnknown(void);
	static void testCreateSudokuGrid(void);
	static void testParser(void);
	int notmain(int argc, char **argv);
	static void testCreateSolvedSudokuGrid();
	
};

int main(int argc, char **argv)
{
  //cout << "Tests for Square.cpp:\n";
  //Test::validateHandlesAllValidParametersTest();

  //Test::validateHandlesTooLargeSquareNumTest();
  //Test::testToString();

  //Test::testFindFirstUnknown();
  //Test::testCreateSolvedSudokuGrid();

  //Test::testParser();

  Run_Sudoku* runner = new Run_Sudoku();
  runner->main();
  delete runner;

  return 0;
}

void Test::validateHandlesAllValidParametersTest() {
  cout << "validateHandlesAllValidParametersTest\n";
  bool result = Square::validate(Test::VALID, Test::VALID);
  assert(result==true);
  cout << "\n";
}

void Test::validateHandlesTooLargeSquareNumTest() {
  cout << "validateHandlesTooLargeSquareNumTest\n";
  bool result = Square::validate(Test::TOO_BIG, Test::VALID);
  assert(result==false);
  cout << "\n";
}

void Test::testToString() {
  cout << "testToString\n";
  Square test_sq = Square::Square(3, 2);
  cout << "Result: " << test_sq.toString() << endl;


}

void Test::testFindFirstUnknown() {
	Square* arr = new Square[3];
	arr[0] = Square::Square(0, 1);
	arr[1] = Square::Square(1, 2);
	arr[2] = Square::Square(2, Square::UNKNOWN);

	Sudoku_Solver* solver = new Sudoku_Solver();
	int result = solver->get_first_unknown(arr, 3);

	if (result != -1) {
		cout << "Result: " << arr[result].toString() << endl;
	} else {
		cout << "ERROR";
	}
	delete[] arr;
	delete solver;
}

void Test::testCreateSolvedSudokuGrid()
{

	cout << endl << "testCreateSolvedSudokuGrid" << endl;
	Sudoku_Generator * gen = new Sudoku_Generator();
	gen->print_sudoku();
	Level diff = easy;
	gen->get_sudoku_puzzle(diff);
	gen->print_sudoku();


}

void Test::testParser()
{
	int result = Solver_Test::parser_test(true);
	if (result == 0) {
		cout << "nice!" << endl;
	}
	else {
		cout << "oops!" << endl;
	}
}