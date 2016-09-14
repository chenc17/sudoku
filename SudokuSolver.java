import java.util.Optional;
import java.util.stream.Collectors;
import java.util.Arrays;
import java.util.Set;

//SudokuSolver
//uses recursive DFS solution to find ONE solution to an unsolved sudoku puzzle
//(note that there could be multiple solutions to a sudoku puzzle)

//@authors Matt Hino and Christine Chen
//@date 9/13/2016
public class SudokuSolver {

  public SudokuSolver() {
    // empty constructor
  }

  // Return a container that holds a solved puzzle or empty if not solvable
  public Optional<Square[]> solve_puzzle(Square[] unsolvedPuzzle) {
    if(!validate(unsolvedPuzzle)) {
      return Optional.empty();
    }

    // create a copy of the unsolved puzzle to work on
    Square[] copyPuzzle = copyPuzzle(unsolvedPuzzle);

    // use a recursive algorithm to find a single possible solution
    Optional<Square[]> solvedPuzzle = backtracking_solver(copyPuzzle);

    return solvedPuzzle;
  }


  private Optional<Square[]> backtracking_solver(Square[] puzzle) {
    // get the next square that hasn't been filled in yet
    Optional<Square> firstUnknown = get_first_unknown(puzzle);

    // Base Case: if there are no unknown squares, we've solved the puzzle :)
    if(!firstUnknown.isPresent()) {
      return Optional.of(puzzle);
    }

    // Now try and loop through all possible values for the unknown square
    Square unknown = firstUnknown.get();

    // get & loop through possible values of the unknown
    Set<Integer> possibleValues = unknown.get_possible_values();
    int square_no = unknown.get_square_no();

    for(Integer val: possibleValues) {
      if(!has_conflict(puzzle, square_no, val)) {
          // assign possible value to that square, and recurse
          puzzle[square_no].set_value(val);

          // RECURSIVE CASE: if solver returns a solved puzzle, return the puzzle
          Optional<Square[]> solvedPuzzle = backtracking_solver(puzzle);
          if(solvedPuzzle.isPresent()) {
            return solvedPuzzle;
          }

          puzzle[square_no].set_value(Square.UNKNOWN);
      }

    }
    return Optional.empty();
  }

  // return the first
  private Optional<Square> get_first_unknown(Square[] puzzle) {
    // sort the puzzle to make sure that we are looking in increasing
    // order.
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

  private Square[] copyPuzzle(Square[] original) {
    Square[] copy = new Square[original.length];
    for(int i = 0; i < original.length; i++){
      copy[i] = new Square(original[i]);
    }
    return copy;
  }

  private boolean has_conflict(Square[] puzzle, int square_no, int new_value) {
    Square oldSquare = puzzle[square_no];
    for(int i=0; i<puzzle.length; i++){
      if(puzzle[i].get_column() == oldSquare.get_column() ||
         puzzle[i].get_row() == oldSquare.get_row() ||
         puzzle[i].get_region() == oldSquare.get_region()) {
           if(puzzle[i].get_value() == new_value) {
             return true; // conflict
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

  // this method checks the entire board to ensure that the solution is correct
  private boolean isValidSolution(Square[] puzzle) {
    for(int i=0; i < puzzle.length; i++) {
      if(has_conflict(puzzle, i, puzzle[i].get_value())){
        return false; // not a valid solution!
      }
    }
    return true;
  }

}
