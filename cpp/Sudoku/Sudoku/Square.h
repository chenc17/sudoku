#include <set>
#include <string>

//Square.h
#ifndef _SQUARE_H
#define _SQUARE_H

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
	Square();
    //Need a destructor????
    void set_possible_values(void);

    int get_column(void);
    int get_row(void);
    int get_region(void);
    int get_value(void);
	int get_square_no(void);
    void set_value(int potential_value);
    std::set<int> get_possible_values(void);
    static bool validate(int square_num, int val);
	void Square::remove_int(int value);

    //int compareTo(Square otherSquare);
    std::string toString();

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

#endif
