
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <set>
#include "Square.h"

using namespace std;


  //Square Class
  //A square object is one box in a Sudoku grid
  //It has a column, row, 3x3 region, value, and square number

  //@authors Christine Chen and Matt Hino
  //@date 9/23/16


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

//constructors (note that default constructor shouldn't ever be used)
Square::Square()
{
	Square(Square::INVALID_VAL, Square::INVALID_VAL);

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

//getters and setters
void Square::set_possible_values(void)
{
  for(int i=Square::MIN_SUDOKU_VAL; i<=Square::MAX_SUDOKU_VAL; i++)
  {
    this->possible_values.insert(i);
  }
}

// remove a number from the set of potential numbers the square could be
void Square::remove_int(int value) {
	this->possible_values.erase(value);
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

int Square::get_square_no(void) {
	return this->square_no;
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

bool Square::validate(int square_num, int val)
{
  if((square_num<Square::TOTAL_NUM_SQ) && (square_num>=Square::MIN_ROW_COL) &&
     ((val>=Square::MIN_SUDOKU_VAL || val==Square::UNKNOWN) && val<=MAX_SUDOKU_VAL))
  {
    return true;
  }

  return false;
}



//don't think this is going to work because variables are private
std::string Square::toString(void)
{
  ostringstream square_str;
  square_str << "Square Num: " << Square::square_no << ", Row: " << Square::row << ", Col: " << Square::column << ", Region: " << Square::region << ", Val: " << Square::value;
  return square_str.str();

}
