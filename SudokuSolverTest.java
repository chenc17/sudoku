import java.util.*;

public class SudokuSolverTest {

  // test puzzles obtained from: http://www.extremesudoku.info/sudoku.html
  private static int[] superHardPuzzle  = {0,0,4, 3,0,0, 0,0,5,
                                           0,8,0, 0,7,0, 0,4,0,
                                           6,0,1, 0,4,0, 2,0,0,

                                           7,0,0, 0,0,9, 0,0,0,
                                           0,6,8, 0,1,0, 4,3,0,
                                           0,0,0, 4,0,0, 0,0,2,

                                           0,0,3, 0,2,0, 5,0,8,
                                           0,2,0, 0,8,0, 0,7,0,
                                           8,0,0, 0,0,3, 6,0,0 };

   private static int[] easyPuzzle      = {4,0,0, 0,0,0, 0,7,3,
                                          8,0,9, 0,7,0, 0,2,0,
                                          0,0,7, 2,5,0, 4,0,0,

                                          9,7,8, 0,6,0, 0,0,4,
                                          0,5,8, 0,2,0, 0,9,0,
                                          1,0,0, 0,3,0, 8,5,7,

                                          0,0,3, 0,9,6, 7,0,8,
                                          0,8,0, 0,1,0, 3,0,9,
                                          2,9,0, 0,0,0, 0,0,8 };


  public static void main(String [] args) {
    System.out.println("Tests for SudokuSolver:");

    solvePuzzleTimed(convertArrayToSquareArray(easyPuzzle));
  }

  public static void solvePuzzleTimed(Square[] puzzle) {
    SudokuSolver solver = new SudokuSolver();

    long startTime = System.currentTimeMillis();
    Optional<Square[]> solved = solver.solve_puzzle(puzzle);
    long endTime = System.currentTimeMillis();
    if(solved.isPresent()) {
      print_sudoku_puzzle(solved.get());
    }
    System.out.println("Solving took " + ((endTime - startTime)/1000) + " seconds");
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
