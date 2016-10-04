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
#include "Sudoku_Solver.h"


using namespace std;

//destructor? initialize?


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


//this method assumes sudoku_grid has gone through the create_solved_puzzle() treatment
//and now removes square values to create an unsolved sudoku_puzzle
//the approach taken is based on the algorithm found: http://www.sudokuwiki.org/Sudoku_Creation_and_Grading.pdf
void Sudoku_Generator::create_unsolved_puzzle(Level difficulty)
{

	/*if the difficulty is RANDOM or any other value other than those listed in the enum,
	assign a difficulty level here*/
	if (difficulty != Level::easy && difficulty != Level::medium && difficulty != Level::difficult)
	{
		//randomly assign a difficulty level out of the 3 possible levels
		int difficulty_val = get_random_idx(3);
		if (difficulty_val == 0)
		{
			difficulty = Level::easy;
		}
		else if (difficulty_val == 1)
		{
			difficulty = Level::medium;
		}
		else if (difficulty_val == 2)
		{
			difficulty = Level::difficult;
		}
	}

	/*the difficulty level affects the number of squares to remove
	set that value here*/
	int num_squares_to_rem = 0;
	switch (difficulty)
	{
		case Level::easy:
			num_squares_to_rem = Sudoku_Generator::REMOVE_NUM_EASY;
			break;
		case Level::medium:
			num_squares_to_rem = Sudoku_Generator::REMOVE_NUM_MED;
			break;
		case Level::difficult:
			num_squares_to_rem = Sudoku_Generator::REMOVE_NUM_DIFF;
			break;
		default:
			num_squares_to_rem = Sudoku_Generator::REMOVE_NUM_EASY;
	
	}

	//almost ready to start clearing squares
	int current_num_empty_sq = 0;

	//these two arrays keep track of the square number and corresponding value of
	//squares that are candidates for "clearing" in the event that a backtrack is necessary
	
	//note that there can only be at most REMOVE_NUM_STAGE_1 candidate squares at a time 
	//(the number of squares to remove decreases in each subsequent stage)
	int* square_no_candidates = new int[Sudoku_Generator::REMOVE_NUM_STAGE_1];
	int* square_value_candidates = new int[Sudoku_Generator::REMOVE_NUM_STAGE_1];
	
	//get a solver to use in determining that sudoku grid is still solvable after "clearing" squares
	Sudoku_Solver*solver = new Sudoku_Solver();
	
	//fills squares set with the square numbers that correspond to squares that still have a value
	std::set<int> squares_with_val = init_squares(); 

	//FINALLY READY TO START RIPPING AWAY SQUARE VALUES
	while (current_num_empty_sq<num_squares_to_rem)
	{

		//make sure the candidate arrays are reset
		for (int i = 0; i<4; i++)
		{
			square_candidates_num[i] = -1;
			square_candidates_val[i] = -1;
		}


		//the number of squares to attempt to "clear" each time
		//depends on the number of currently "cleared" squares
		if (num_empty_squares<STAGE_2_SQ_REM)
		{
			//System.out.println("\nIn STAGE 1\n");
			num_squares_to_clear = REMOVE_SQ_STAGE_1;
		}
		else if (num_empty_squares<STAGE_3_SQ_REM)
		{
			//System.out.println("\nIn STAGE 2\n");
			num_squares_to_clear = REMOVE_SQ_STAGE_2;
		}
		else
		{
			//System.out.println("\nIn STAGE 3\n");
			num_squares_to_clear = REMOVE_SQ_STAGE_3;
		}


		//keeps track of how many squares have been selected as candidates
		int num_squares_selected = 0;
		while (num_squares_selected<num_squares_to_clear)
		{
			//get a random square candidate
			Object[] squares_arr = squares.toArray();
			int square_no = (int)squares_arr[get_random_idx(squares_arr)];
			//make sure this square hasn't already been chosen as a candidate
			if (IntStream.of(square_candidates_num).anyMatch(x->x == square_no))
			{
				continue;
			}
			else
			{
				//enter the square and its value into the appropriate arrays
				square_candidates_num[num_squares_selected] = square_no;
				square_candidates_val[num_squares_selected] = sudoku_grid[square_no].get_value();
				num_squares_selected++;
			}


	//deallocate square_candidates_num
	//deallocate solver
}
//returns an array containing the numbers 0 up to but not including Square::TOTAL_NUM_SQ
std::set<int> Sudoku_Generator::init_squares()
{
	
	std::set<int> square_nums;
	
	for (int i = 0; i<Square::TOTAL_NUM_SQ; i++)
	{
		square_nums.insert(i);
	}
	
	return square_nums;
	
	
}

//
//		while (num_empty_squares<stop_at_num_empty_squares)
//		{
//
//			//make sure the arrays are reset
//			for (int i = 0; i<4; i++)
//			{
//				square_candidates_num[i] = -1;
//				square_candidates_val[i] = -1;
//			}
//
//
//			//the number of squares to attempt to "clear" each time
//			//depends on the number of currently "cleared" squares
//			if (num_empty_squares<STAGE_2_SQ_REM)
//			{
//				//System.out.println("\nIn STAGE 1\n");
//				num_squares_to_clear = REMOVE_SQ_STAGE_1;
//			}
//			else if (num_empty_squares<STAGE_3_SQ_REM)
//			{
//				//System.out.println("\nIn STAGE 2\n");
//				num_squares_to_clear = REMOVE_SQ_STAGE_2;
//			}
//			else
//			{
//				//System.out.println("\nIn STAGE 3\n");
//				num_squares_to_clear = REMOVE_SQ_STAGE_3;
//			}
//
//
//			//keeps track of how many squares have been selected as candidates
//			int num_squares_selected = 0;
//			while (num_squares_selected<num_squares_to_clear)
//			{
//				//get a random square candidate
//				Object[] squares_arr = squares.toArray();
//				int square_no = (int)squares_arr[get_random_idx(squares_arr)];
//				//make sure this square hasn't already been chosen as a candidate
//				if (IntStream.of(square_candidates_num).anyMatch(x->x == square_no))
//				{
//					continue;
//				}
//				else
//				{
//					//enter the square and its value into the appropriate arrays
//					square_candidates_num[num_squares_selected] = square_no;
//					square_candidates_val[num_squares_selected] = sudoku_grid[square_no].get_value();
//					num_squares_selected++;
//				}
//
//
//			}
//
//			//try removing the values for the squares in square_candidates_num and try solving
//			for (int i = 0; i<num_squares_selected; i++)
//			{
//				sudoku_grid[square_candidates_num[i]].set_value(Square.UNKNOWN);
//				sudoku_grid[square_candidates_num[i]].reset_possible_values();
//			}
//
//			//System.out.println("CANDIDATE!");
//			//print_sudoku_puzzle();
//			//System.out.println();
//
//			Optional<Square[]> solved = solver.solve_puzzle(sudoku_grid);
//			//System.out.println("After Attempted Solve!");
//			//print_sudoku_puzzle();
//			//System.out.println();
//
//			if (!(solved.isPresent()))
//			{
//				//PUZZLE IS UNSOLVABLE
//				//backtrack and try again
//				for (int i = 0; i<num_squares_selected; i++)
//				{
//					sudoku_grid[square_candidates_num[i]].set_value(square_candidates_val[i]);
//					sudoku_grid[square_candidates_num[i]].reset_possible_values();
//				}
//
//				if (num_empty_squares>STAGE_3_SQ_REM)
//				{
//					//if we're already in stage 3, just stop
//					break;
//				}
//				else
//				{
//					//System.out.println("---------------------------------------------");
//					continue;
//				}
//
//			}
//			else
//			{
//				//the puzzle is solvable
//				//update num_empty_squares
//				num_empty_squares = num_empty_squares + num_squares_selected;
//
//				//remove the appropriate squares from the squares set
//				for (int i = 0; i<num_squares_selected; i++)
//				{
//					squares.remove(square_candidates_num[i]);
//				}
//
//				//since the solver solved the puzzle, need to reinstate the blanks for the next Round
//				for (int i = 0; i<Square.NUM_SQUARES; i++)
//				{
//					if (!squares.contains(i))
//					{
//						sudoku_grid[i].set_value(Square.UNKNOWN);
//						sudoku_grid[i].reset_possible_values();
//					}
//				}
//
//				//System.out.println("Round Completed!");
//				//print_sudoku_puzzle();
//				//System.out.println();
//				//System.out.println("---------------------------------------------");
//
//			}
//
//
//
//		}
//
//		//System.out.println ("NUMBER OF SQUARES REMOVED " + num_empty_squares + "\n");
//
//	}