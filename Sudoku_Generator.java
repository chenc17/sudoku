import java.util.HashSet;
import java.util.Set;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;
import java.io.FileOutputStream;


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
    Square[] puzzle = generator.get_sudoku_puzzle();
    if(puzzle==null)
    {
      System.out.println("Error in getting sudoku puzzle. Exiting!\n");
      System.exit(0);
    }
    else
    {
      generator.print_sudoku_puzzle();
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


  public Square[] get_sudoku_puzzle()
  {
    boolean created_sp_success=create_solved_puzzle();
    if(created_sp_success==true)
    {
      return sudoku_grid;
    }
    else
    {
      return null;
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
          int rand_val=(int)poss_vals_arr[new Random().nextInt(poss_vals_arr.length)];
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
