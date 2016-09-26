// Sudoku_CPP.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <set>

using namespace std;


//Square Class
//A square object is one box in a Sudoku grid
//It has a column, row, 3x3 region, value, and square number

//@authors Christine Chen and Matt Hino
//@date 9/23/16

class Square
{
  private:
  	int column; //0 based
  	int row; //0 based
  	int region; //0 based
  	int value; //1 to 9, 0 if unknown
  	int square_no; //0 based
  	std::set<int> possible_values;

  	//private methods
  	int get_row_idx(int square_num);
  	int get_col_idx(int row_idx, int square_num);
  	int get_region_from_row_col(int row, int col);


  public:
  	Square(int sq_number, int val);
  	//Need a destructor????
  	void set_possible_values(void);

  	int get_column(void);
  	int get_row(void);
  	int get_region(void);
  	int get_value(void);
  	void set_value(int potential_value);
  	std::set<int> get_possible_values(void);
  	static bool validate(int square_num, int val);

  	//int compareTo(Square otherSquare);
  	string toString();

    //constants
  	static const int INVALID_VAL = -1;
  	static const int NUM_SQ_ROW_COL = 9;
  	static const int TOTAL_NUM_SQ = (NUM_SQ_ROW_COL)*(NUM_SQ_ROW_COL);
  	static const int MAX_SUDOKU_VAL = 9;
  	static const int UNKNOWN = 0; //used for a "blank" sudoku square
  	static const int MIN_SUDOKU_VAL = 1;
  	static const int MAX_ROW_COL = 8;
  	static const int MIN_ROW_COL = 0;

};

int Square::get_row_idx(int square_num)
{
  int row_idx=(square_num/Square::NUM_SQ_ROW_COL);
  return row_idx;
}

int Square::get_col_idx(int row_idx, int square_num)
{
  int col_idx=square_num-(Square::NUM_SQ_ROW_COL*row_idx);
  return col_idx;
}

// there are 9 regions in a sudoku board
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
//this method calculates a square's region based on its row and col
int Square::get_region_from_row_col(int row, int col)
{
  int region=0;
  int row_region=0;
  int col_region=0;

  if(row>=0 && row<=2)
  {
    row_region=0;
  }
  if(row>=3 && row<=5)
  {
    row_region=1;
  }
  if(row>=6 && row<=8)
  {
    row_region=2;
  }

  if(col>=0 && col<=2)
  {
    col_region=0;
  }
  if(col>=3 && col<=5)
  {
    col_region=1;
  }
  if(col>=6 && col<=8)
  {
    col_region=2;
  }

  region=(3*row_region)+col_region;
  return region;
}

Square::Square(int sq_num, int val)
{
  if(validate(sq_num, val))
  {
    this->row = get_row_idx(sq_num);
    this->column = get_col_idx(this->row, sq_num);
    this->region = get_region_from_row_col(this->row, this->column);
    this->value = val;
    this->square_no = sq_num;
  }
  else
  {

    this->column=Square::INVALID_VAL;
    this->row=Square::INVALID_VAL;
    this->region=Square::INVALID_VAL;
    this->value=Square::INVALID_VAL;
    this->square_no=Square::INVALID_VAL;
  }

  set_possible_values();
}

void Square::set_possible_values(void)
{
  for(int i=Square::MIN_SUDOKU_VAL; i<=Square::MAX_SUDOKU_VAL; i++)
  {
    this->possible_values.insert(i);
  }
}

int Square::get_column(void)
{
  return this->column;
}

int Square::get_row(void)
{
  return this->row;
}
int Square::get_region(void)
{
  return this->region;
}
int Square::get_value(void)
{
  return this->value;
}

void Square::set_value(int potential_value)
{
  if(validate(this->square_no, potential_value)==true)
  {
    this->value = potential_value;
  }
  else
  {
    this->value = Square::INVALID_VAL;
  }
}

std::set<int> Square::get_possible_values(void)
{
  return this->possible_values;
}
