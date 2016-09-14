
import java.util.*;

public class Run_Sudoku()
{

  //create instance of SudokuParser
  SudokuParser parser = new SudokuParser();

  //create or solve?

  //create
  //how many?
  //what difficulty?

  //create a Sudoku_Generator object
  Sudoku_Generator generator = new Sudoku_Generator();
  //create a SudokuSolver
  SudokuSolver solver = new SudokuSolver();

  for(int i=0; i<HOW_MANY; i++)
  {
    //call get_sudoku_puzzle and write to file
    Optional<Square[]> unsolved_sudoku = generator.get_sudoku_puzzle(USER_LEVEL);
    if(unsolved_sudoku.isPresent())
    {

      //write to file
      parser.writeSudoku(unsolved_sudoku.get(), "SUDOKU_"+(i+1)+".txt");

      //hand off sudoku grid to solver
      Optional<Square[]> solved_sudoku = solver.solve_puzzle(unsolved_sudoku.get())
      if(solved_sudoku.isPresent())
      {
        //write solution to file
        //refresh the grid in case another puzzle needs to be generated
      }
      else
      {
        System.out.println("Error in solving sudoku puzzle. Exiting!\n");
        System.exit(0);
      }

    }
    else
    {
      System.out.println("Error in getting sudoku puzzle. Exiting!\n");
      System.exit(0);
    }


  }



  //solve
  //prompt user to enter file name containing sudoku
  //create a SudokuSolver
  //parse
  //hand off to solver
  //write solution to file


}
