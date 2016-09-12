import java.util.*;
import java.io.*;

public class SudokuSolverTest {

  // test puzzles obtained from: http://www.extremesudoku.info/sudoku.html
  private static int[] kindaHardPuzzle  = {0,0,4, 3,0,0, 0,0,5,
                                           0,8,0, 0,7,0, 0,4,0,
                                           6,0,1, 0,4,0, 2,0,0,

                                           7,0,0, 0,0,9, 0,0,0,
                                           0,6,8, 0,1,0, 4,3,0,
                                           0,0,0, 4,0,0, 0,0,2,

                                           0,0,3, 0,2,0, 5,0,8,
                                           0,2,0, 0,8,0, 0,7,0,
                                           8,0,0, 0,0,3, 6,0,0 };

   // http://www.telegraph.co.uk/news/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html
  private static int[] ridiculousPuzzle = {8,0,0, 0,0,0, 0,0,0,
                                           0,0,3, 6,0,0, 0,0,0,
                                           0,7,0, 0,9,0, 2,0,0,

                                           0,5,0, 0,0,7, 0,0,0,
                                           0,0,0, 0,4,5, 7,0,0,
                                           0,0,0, 1,0,0, 0,3,0,

                                           0,0,1, 0,0,0, 0,6,8,
                                           0,0,8, 5,0,0, 0,1,0,
                                           0,9,0, 0,0,0, 4,0,0 };

  private static int[] ridiculousSolved = {8,1,2, 7,5,3, 6,4,9,
                                           9,4,3, 6,8,2, 1,7,5,
                                           6,7,5, 4,9,1, 2,8,3,

                                           1,5,4, 2,3,7, 8,9,6,
                                           3,6,9, 8,4,5, 7,2,1,
                                           2,8,7, 1,6,9, 5,3,4,

                                           5,2,1, 9,7,4, 3,6,8,
                                           4,3,8, 5,2,6, 9,1,7,
                                           7,9,6, 3,1,8, 4,5,2};


  public static void main(String [] args) {
    try {
      System.out.println("Tests for SudokuSolver:");
      solvePuzzleTimed(convertArrayToSquareArray(kindaHardPuzzle), "kindaHardPuzzle_solved.txt");
      solvePuzzleTimed(convertArrayToSquareArray(ridiculousPuzzle), "ridiculousPuzzle_solved.txt");

      System.out.println("Testing Parser:");

      Square[] result = SudokuParser.parseSudoku("test_puzzle.txt");
      SudokuParser.writeSudoku(result, "test_puzzle_output.txt");
      SudokuSolver solver = new SudokuSolver();

      Optional<Square[]> solved = solver.solve_puzzle(result);
      if(solved.isPresent()) {
          SudokuParser.writeSudoku(solved.get(), "test_puzzle_solved.txt");
      }
    } catch (IOException ioe) {
      System.out.println("Uh oh, an error occured while parsing ");
    }
  }

  public static void solvePuzzleTimed(Square[] puzzle, String outputFileName) throws IOException {
    SudokuSolver solver = new SudokuSolver();

    long startTime = System.currentTimeMillis();
    Optional<Square[]> solved = solver.solve_puzzle(puzzle);
    long endTime = System.currentTimeMillis();
    if(solved.isPresent()) {
      SudokuParser.writeSudoku(solved.get(), outputFileName);
    }
    System.out.println("Solving took " + (endTime - startTime) + " milliseconds\n");
  }

  public static Square[] convertArrayToSquareArray(int[] grid) {
    List<Square> squareList = new ArrayList<Square>();
    for(int i = 0; i < grid.length; i++) {
      squareList.add(new Square(i, grid[i]));
    }

    return squareList.toArray(new Square[squareList.size()]);
  }

  private static void print_sudoku_puzzle(Square[] puzzle) {
    for (int i=0; i<puzzle.length; i++)
    {
      if((puzzle[i].get_square_no()%puzzle[i].NUM_SQUARES_ROW_COL)==0) {
        System.out.println();
      }
      System.out.print(puzzle[i].get_value());
    }
    System.out.println();
  }
}
