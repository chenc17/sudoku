#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <set>
#include <assert.h>
#include "Square.h"
#include "Sudoku_Generator.h"
#include <time.h> 


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

Square* Sudoku_Generator::get_sudoku_puzzle(Level diff)
{
	bool success = create_solved_puzzle();
	if (success)
	{
		if (true) //need to change
		{
			//Sudoku_Generator::create_unsolved_puzzle(diff);
			return sudoku_grid;
		}
	}

	//deallocate and return NULL?
	return NULL;
	
}

bool Sudoku_Generator::create_solved_puzzle()
{
	//know at this point that sudoku_grid has been initialized with 81 blank squares
	//go through sudoku_grid and start giving the squares values
	
	/* initialize random seed: */
	srand(time(NULL));

	for (int sq_num = 0; sq_num<Square::TOTAL_NUM_SQ; sq_num++)
	{
		Square * sq_ptr = sudoku_grid + sq_num;
		std::set<int> poss_vals = (sudoku_grid+sq_num)->get_possible_values();
		
		//check that there are still values in the square's possible_values set
		if (poss_vals.empty() == false)
		{
			//use an iterator to get a random value from the possible values for the square
			set<int>::const_iterator it(poss_vals.begin());
			int rand_adv = get_random_idx(poss_vals.size());
			// 'advance' the iterator rand_val times
			advance(it, rand_adv);
			int square_rand_val = *it;


			//check to see if setting rand_val as the square's value
			//results in a valid sudoku grid
			sq_ptr->set_value(square_rand_val);
			if (sq_ptr->get_value() == square_rand_val)
			{
				bool conflict = check_for_conflict(sq_num);
				sq_ptr->remove_int(square_rand_val);
				if (conflict != false)
				{
					//there's an issue with this value, try again
					sq_num--;
				}
			}
			else
			{
				
				return false;
			}
		
		}
		else
		{
			//need to reset possible_values for this square and backtrack to previous square
			sq_ptr->set_possible_values();
			sq_num = sq_num - 2;
		}
	}
	

	return true;
		
}



int Sudoku_Generator::get_random_idx(int len_array)
{
	return rand() % len_array;
}

//takes a square number and checks to see if that square creates a conflict in
//sudoku_grid
bool Sudoku_Generator::check_for_conflict(int sq_num_test)
{
	for (int sq = 0; sq<Square::TOTAL_NUM_SQ && sq != sq_num_test; sq++)
	{
		Square * sq_ptr = sudoku_grid + sq;
		Square * test_ptr = sudoku_grid + sq_num_test;
		//for every square, if in same region or row or column as test_square, test values...
		//if values are the same, CONFLICT!!!
		if (sq_ptr->get_row() == test_ptr->get_row() ||
			sq_ptr->get_column() == test_ptr->get_column() ||
			sq_ptr->get_region() == test_ptr->get_region())
		{
			if (sq_ptr->get_value() == test_ptr->get_value())
			{
				//CONFLICT!!
				return true;
			}
		}

	}
	return false;
}
//	//creates a fully solved sudoku puzzle
//	private boolean create_solved_puzzle()
//	{
//		//know at this point that sudoku_grid has been initialized with 81 blank squares
//		//go through sudoku_grid and start giving the squares values
//		for (int sq_num = 0; sq_num<sudoku_grid.length; sq_num++)
//		{
//
//			Set<Integer> poss_vals_set = sudoku_grid[sq_num].get_possible_values();
//			//check that there are still values in the square's possible_values set
//			if (poss_vals_set.isEmpty() == false)
//			{
//				//randomly choose a value from square_poss_vals (SEEMS A LITTLE IFFY)
//				Object[] poss_vals_arr = poss_vals_set.toArray();
//				int rand_val = (int)poss_vals_arr[get_random_idx(poss_vals_arr)];
//				//System.out.println(rand_val);
//
//				//check to see if setting rand_val as sudoku_grid[sq_num]'s value
//				//results in a valid sudoku grid
//				sudoku_grid[sq_num].set_value(rand_val);
//				if (sudoku_grid[sq_num].get_value() == rand_val)
//				{
//					boolean conflict = check_for_conflict(sq_num);
//					sudoku_grid[sq_num].remove_int(rand_val);
//					if (conflict != false)
//					{
//						//there's an issue with this value, try again
//						sq_num--;
//					}
//				}
//				else
//				{
//					return false;
//				}
//
//			}
//			else
//			{
//				//need to reset possible_values for this square and backtrack to previous square
//				sudoku_grid[sq_num].reset_possible_values();
//				sq_num = sq_num - 2;
//			}
//		}
//
//		return true;
//
//	}
//
//	//selects a random index from the array passed in
//	private int get_random_idx(Object[] array)
//	{
//		return new Random().nextInt(array.length);
//	}
//


