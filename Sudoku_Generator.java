import java.util.*;
import java.util.stream.IntStream;
import java.io.FileOutputStream;
import java.lang.Enum;
import java.lang.Class;


//Sudoku_Generator Class
//A Sudoku_Generator object contains the sudoku grid--an array of Square objects
//It also has methods to create a solved sudoku grid (complete)
//and a solvable sudoku grid (not started)
//The method of most interest to those using this class is the
//get_sudoku_puzzle() method that will return a solvable sudoku grid (array of Square objects)
//or null if there is some Error
//NOTE: currently, get_sudoku_puzzle() returns a completely solved sudoku grid
//or null

//@authors Christine Chen and Matt Hino
//@date 9/10/2016
public class Sudoku_Generator
{
  //create an array of 81 Square objects

  private Square[] sudoku_grid;
  public static final int REMOVE_SQ_STAGE_1=4;
  public static final int STAGE_2_SQ_REM=20;
  public static final int REMOVE_SQ_STAGE_2=2;
  public static final int STAGE_3_SQ_REM=40;
  public static final int REMOVE_SQ_STAGE_3=1;


  //game "levels"
  public enum Level
  {
    EASY, MEDIUM, DIFFICULT, RANDOM
  }

  public static final int HARD_STOP_SQ_REM_EASY=41; //40 left
  public static final int HARD_STOP_SQ_REM_MED=51; //30 left
  public static final int HARD_STOP_SQ_REM_DIFF=61; //20 left




  public Sudoku_Generator()
  {
    sudoku_grid = new Square[Square.NUM_SQUARES];

    //populate sudoku_grid with "blank" Square objects
    for(int idx=0; idx<sudoku_grid.length; idx++)
    {
        sudoku_grid[idx]=new Square(idx, Square.MIN_SUDOKU_VAL);

        //make sure the declaration is valid
        if(sudoku_grid[idx].get_column()==Square.INVALID_VAL)
        {
          System.out.println("Error in game initialization. Exiting. \n");
          System.exit(0);
        }
      }
  }

  public static void main(String[] args)
  {
    //welcome message
    Sudoku_Generator generator = new Sudoku_Generator();

    Optional<Square[]> puzzle =  generator.get_sudoku_puzzle(Level.RANDOM);
    if(puzzle.isPresent())
    {
      generator.print_sudoku_puzzle();
    }
    else
    {
      System.out.println("Error in getting sudoku puzzle. Exiting!\n");
      System.exit(0);
    }
  }

  private void print_sudoku_puzzle()
  {

    for (int i=0; i<sudoku_grid.length; i++)
    {
      if(sudoku_grid[i].get_square_no()%sudoku_grid[i].NUM_SQUARES_ROW_COL==0)
      {
        System.out.println();
      }
      System.out.print((sudoku_grid[i].get_value()));

    }
    System.out.println();
  }


  public Optional<Square[]> get_sudoku_puzzle(Level level_diff)
  {
    boolean created_sp_success=create_solved_puzzle();
    if(created_sp_success==true)
    {
      create_unsolved_puzzle(level_diff);
      return Optional.of(sudoku_grid);
    }
    else
    {
      return Optional.empty();
    }
  }

  private boolean create_solved_puzzle()
  {
    //know at this point that sudoku_grid has been initialized with 81 blank squares
    //go through sudoku_grid and start giving the squares values
    for (int sq_num=0; sq_num<sudoku_grid.length; sq_num++)
    {

      Set<Integer> poss_vals_set=sudoku_grid[sq_num].get_possible_values();
      //check that there are still values in the square's possible_values set
      if(poss_vals_set.isEmpty()==false)
      {
          //randomly choose a value from square_poss_vals (SEEMS A LITTLE IFFY)
          Object[] poss_vals_arr=poss_vals_set.toArray();
          int rand_val=(int)poss_vals_arr[get_random_idx(poss_vals_arr)];
          //System.out.println(rand_val);

          //check to see if setting rand_val as sudoku_grid[sq_num]'s value
          //results in a valid sudoku grid
          sudoku_grid[sq_num].set_value(rand_val);
          if(sudoku_grid[sq_num].get_value()==rand_val)
          {
            boolean conflict=check_for_conflict(sq_num);
            sudoku_grid[sq_num].remove_int(rand_val);
            if(conflict!=false)
            {
              //there's an issue with this value, try again
              sq_num--;
            }
          }
          else
          {
            System.out.println("Error setting square " + sq_num + " value! Returning to create_solved_puzzle!\n");
            return false;
          }

      }
      else
      {
        //need to reset possible_values for this square and backtrack to previous square
        sudoku_grid[sq_num].reset_possible_values();
        sq_num=sq_num-2;
      }
    }

    return true;

  }

  private int get_random_idx(Object[] array)
  {
    return new Random().nextInt(array.length);
  }

  //assumes sudoku_grid has gone through the create_solved_puzzle() treatment
  private void create_unsolved_puzzle(Level difficulty)
  {
    int stop_at_num_empty_squares=0;

    while(difficulty!=Level.EASY && difficulty!=Level.MEDIUM && difficulty!=Level.DIFFICULT)
    {
      int difficulty_val=new Random().nextInt(3);
      if(difficulty_val==0)
      {
        difficulty=Level.EASY;
      }
      else if(difficulty_val==1)
      {
        difficulty=Level.MEDIUM;
      }
      else if(difficulty_val==2)
      {
        difficulty=Level.DIFFICULT;
      }
    }
    switch(difficulty)
    {
      case EASY:
        System.out.println("EASY PUZZLE\n");
        stop_at_num_empty_squares=HARD_STOP_SQ_REM_EASY;
        break;

      case MEDIUM:
        System.out.println("MEDIUM PUZZLE\n");
        stop_at_num_empty_squares=HARD_STOP_SQ_REM_MED;
        break;

      case DIFFICULT:
        System.out.println("DIFFICULT PUZZLE\n");
        stop_at_num_empty_squares=HARD_STOP_SQ_REM_DIFF;
        break;

      default:
        System.out.println("DEFAULT: EASY PUZZLE\n");
        stop_at_num_empty_squares=HARD_STOP_SQ_REM_EASY;

    }


    int num_empty_squares=0;
    //keeps track of how many squares should be "cleared" at at time
    int num_squares_to_clear=0;

    //these two arrays keep track of the square number and corresponding value of
    //squares that are candidates for "clearing"
    //there can only be at most REMOVE_SQ_STAGE_1 candidates squares at a time
    int [] square_candidates_num=new int[REMOVE_SQ_STAGE_1];
    int [] square_candidates_val=new int[REMOVE_SQ_STAGE_1];

    //get a solver to use in determining that sudoku grid is still solvable after "clearing" squares
    SudokuSolver solver = new SudokuSolver();

    //fills squares set with the square numbers that correspond to squares that still have a value
    Set<Integer> squares = init_squares();

    while(num_empty_squares<stop_at_num_empty_squares)
    {

      //make sure the arrays are reset
      for(int i=0; i<4; i++)
      {
        square_candidates_num[i]=-1;
        square_candidates_val[i]=-1;
      }


      //the number of squares to "clear" each time
      //depends on the number of currently "cleared" squares
      if(num_empty_squares<STAGE_2_SQ_REM)
      {
        System.out.println("\nIn STAGE 1\n");
        num_squares_to_clear=REMOVE_SQ_STAGE_1;
      }
      else if (num_empty_squares<STAGE_3_SQ_REM)
      {
        System.out.println("\nIn STAGE 2\n");
        num_squares_to_clear=REMOVE_SQ_STAGE_2;
      }
      else
      {
        System.out.println("\nIn STAGE 3\n");
        num_squares_to_clear=REMOVE_SQ_STAGE_3;
      }


      //keeps track of how many squares have been selected as candidates
      int num_squares_selected=0;
      while(num_squares_selected<num_squares_to_clear)
      {
          //get a random square candidate
          Object[] squares_arr=squares.toArray();
          int square_no=(int)squares_arr[get_random_idx(squares_arr)];
          //make sure this square hasn't already been chosen as a candidate
          if(IntStream.of(square_candidates_num).anyMatch(x->x==square_no))
          {
            continue;
          }
          else
          {
            square_candidates_num[num_squares_selected]=square_no;
            square_candidates_val[num_squares_selected]=sudoku_grid[square_no].get_value();
            num_squares_selected++;
          }


      }



      //try removing the values for the squares in square_candidates_num and try solving
      for(int i=0; i<num_squares_selected; i++)
      {
        sudoku_grid[square_candidates_num[i]].set_value(Square.UNKNOWN);
        sudoku_grid[square_candidates_num[i]].reset_possible_values();
      }

      System.out.println("CANDIDATE!");
      print_sudoku_puzzle();
      System.out.println();

      Optional<Square[]> solved=solver.solve_puzzle(sudoku_grid);
      System.out.println("After Attempted Solve!");
      print_sudoku_puzzle();
      System.out.println();

      if(!(solved.isPresent()))
      {
        //PUZZLE IS UNSOLVABLE
        //backtrack and try again
        for(int i=0; i<num_squares_selected; i++)
        {
          sudoku_grid[square_candidates_num[i]].set_value(square_candidates_val[i]);
          sudoku_grid[square_candidates_num[i]].reset_possible_values();
        }

        if(num_empty_squares>STAGE_3_SQ_REM)
        {
          //if we're already in stage 3, just stop
          break;
        }
        else
        {
          System.out.println("---------------------------------------------");
          continue;
        }

      }
      else
      {
        //the puzzle is solvable
        //update num_empty_squares
        num_empty_squares=num_empty_squares+num_squares_selected;

        //remove the appropriate squares from the squares set
        for(int i=0; i<num_squares_selected; i++)
        {
          squares.remove(square_candidates_num[i]);
        }

        //since the solver solved the puzzle, need to reinstate the blanks for the next Round
        for(int i=0; i<Square.NUM_SQUARES; i++)
        {
          if (!squares.contains(i))
          {
            sudoku_grid[i].set_value(Square.UNKNOWN);
            //RESET POSSIBLE VALUES...
          }
        }

        System.out.println("Round Completed!");
        print_sudoku_puzzle();
        System.out.println();
        System.out.println("---------------------------------------------");

      }



    }

    System.out.println ("NUMBER OF SQUARES REMOVED " + num_empty_squares + "\n");

  }


  private Set<Integer> init_squares()
  {
    Set<Integer> square_nums = new HashSet<Integer>();

    for(int i=0; i<Square.NUM_SQUARES; i++)
    {
      square_nums.add(i);
    }

    return square_nums;


  }


  private boolean check_for_conflict(int test_square)
  {
    for(int sq_num=0; sq_num<sudoku_grid.length && sq_num!=test_square; sq_num++)
    {
      //for every square, if in same region or row or column as test_square, test values...
      //if values are the same, CONFLICT!!!
      if(sudoku_grid[sq_num].get_row()==sudoku_grid[test_square].get_row() ||
      sudoku_grid[sq_num].get_column()==sudoku_grid[test_square].get_column() ||
      sudoku_grid[sq_num].get_region()==sudoku_grid[test_square].get_region())
      {
        if(sudoku_grid[sq_num].get_value()==sudoku_grid[test_square].get_value())
        {
          //CONFLICT!!
          return true;
        }
      }

    }
      return false;
  }
}
