#include <set>
#include <string>
#include "Square.h"

//Sudoku_Generator.h
#ifndef _SUDOKU_GEN_H
#define _SUDOKU_GEN_H


enum Level { easy, medium, difficult };

class Sudoku_Generator
{


private:
	Square * sudoku_grid;
	bool create_solved_puzzle();
	void create_unsolved_puzzle(Level difficulty);
	int get_random_idx(int len_array);
	bool check_for_conflict(int sq_num);
	
public:
	Sudoku_Generator();
	Square * get_sudoku_puzzle(Level level_diff);
	
	void print_sudoku();
	


	//constants
	//these constants help with removing squares from a solved sudoku
	static const int REMOVE_NUM_STAGE_1 = 4; //remove 4 squares at a time in the first stage
	static const int STAGE_2_VAL = 20; //start the second stage after 20 squares have been removed
	static const int REMOVE_NUM_STAGE_2 = 2;
	static const int STAGE_3_VAL = 40;
	static const int REMOVE_NUM_STAGE_3 = 1;

	//how many squares should be removed for each difficulty level
	static const int REMOVE_NUM_EASY = 41; //40 left
	static const int REMOVE_NUM_MED = 51; //30 left
	static const int REMOVE_NUM_DIFF = 61; //20 left
	
};


#endif
