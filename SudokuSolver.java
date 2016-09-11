import java.util.Optional;
import java.util.stream.Collectors;
import java.util.Arrays;
import java.util.Set;
/**
*
**/
public class SudokuSolver {

  public SudokuSolver() {
    // empty constructor
  }

  // Return a container that holds a solved puzzle or is empty if not solvable
  public Optional<Square[]> solve_puzzle(Square[] unsolvedPuzzle) {
    // first ensure that the Square[] is of correct size
    if(!validate(unsolvedPuzzle)) {
      return Optional.empty();
    }

    // get the set of unknown squares to iterate over for algorithms 1 and 2.
    Set<Square> unknownSquares = get_unknown(unsolvedPuzzle);

    // 1. First solve as many as possible using 'Candidate Checking'

    // 2. Now narrow down selection using 'Place Finding Method'

    // 3. Finally, solve using a basic backtracking algorithm
    Optional<Square[]> solvedPuzzle = backtracking_solver(unsolvedPuzzle);
    if(solvedPuzzle.isPresent()) {
      System.out.println("Solved puzzle!");
    } else {
      System.out.println("Unable to solve puzzle :(");
    }

    return solvedPuzzle;
  }

  private Optional<Square[]> backtracking_solver(Square[] puzzle) {
    Optional<Square> firstUnknown = get_first_unknown(puzzle);

    // if there are no unknown squares, we've solved the puzzle :)
    if(!firstUnknown.isPresent()) {
      return Optional.of(puzzle);
    }

    // get & loop through possible values of the unknown
    Set<Integer> possibleValues = firstUnknown.get().get_possible_values();

    for(int val=1; val<=Square.MAX_SUDOKU_VAL; val++) {
      if(!has_conflict(puzzle, firstUnknown.get().get_square_no(), val)) {
          // assign possible value to that square, and recurse
          int square_no = firstUnknown.get().get_square_no();
          Square newSquare = new Square(square_no, val);
          Square oldSquare = puzzle[square_no];
          System.out.println(newSquare);
          puzzle[square_no] = newSquare;

          // RECURSIVE CASE: if solver returns a solved puzzle, return the puzzle
          Optional<Square[]> solvedPuzzle = backtracking_solver(puzzle);
          if(solvedPuzzle.isPresent()) {
            return solvedPuzzle;
          }

          // No solved puzzle found, try again.
          puzzle[square_no] = oldSquare;
      }
    }
    return Optional.empty();
  }

  // return the first
  private Optional<Square> get_first_unknown(Square[] puzzle) {
    // first sort the array of squares by square number
    Arrays.sort(puzzle);

    // now look for the first Square of unkown value.
    for(int i=0; i < puzzle.length; i++) {
      if(puzzle[i].get_value() == Square.UNKNOWN) {
        return Optional.of(puzzle[i]);
      }
    }
    return Optional.empty();
  }

  private Set<Square> get_unknown(Square[] puzzle) {
    return Arrays.asList(puzzle)
                 .stream()
                 .filter(s -> (s.get_value() == Square.UNKNOWN))
                 .collect(Collectors.toSet());
  }

  // see if we can change 'test_square's value to 'value' with the existing 'puzzle'
  // return true if there is no conflict, false otherwise
  private boolean has_conflict(Square[] puzzle, int test_square_no, int value) {
    for(int sq_num=0; sq_num<puzzle.length && sq_num!=test_square_no; sq_num++) {
      //for every square, if in same region or row or column as test_square, test values...
      //if values are the same, CONFLICT!!!
      if(puzzle[sq_num].get_row()==puzzle[test_square_no].get_row() ||
         puzzle[sq_num].get_column()==puzzle[test_square_no].get_column() ||
         puzzle[sq_num].get_region()==puzzle[test_square_no].get_region())
      {
        if(puzzle[sq_num].get_value()==value)
        {
          //CONFLICT!!
          return true;
        }
      }

    }
      return false;
  }

  // make sure that the puzzle has the appropriate size and each square
  // contains valid values. returns true if valid.
  private boolean validate(Square[] puzzle) {
    if(puzzle.length != Square.NUM_SQUARES) {
      return false;
    }

    for(Square square: puzzle) {
      if(!square.validate(square.get_square_no(), square.get_value())) {
        return false;
      }
    }
    return true;
  }

}
