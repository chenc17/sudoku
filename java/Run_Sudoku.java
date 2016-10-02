
import java.util.*;
import java.io.*;
import java.nio.file.*;

//Run_Sudoku
//This is the class that a user runs in order to generate or solve
//Sudoku puzzles

//@authors Matt Hino and Christine Chen
//@date 9/14/2016

public class Run_Sudoku {

  //constants
  private static final String CREATE = "create";
  private static final String SOLVE = "solve";
  private static final String YES = "yes";
  private static final String NO = "no";
  private static final boolean ERROR = false;

  //variables
  private final BufferedReader keyboard;
  private final SudokuSolver solver;
  private final Sudoku_Generator generator;

  //constructor
  public Run_Sudoku() {
    this.keyboard = new BufferedReader(new InputStreamReader(System.in));
    this.solver = new SudokuSolver();
    this.generator = new Sudoku_Generator();
  }

  public static void main(String args[]) {
    Run_Sudoku runner = new Run_Sudoku();
    boolean doAgain = false;

    // welcome the user to the program, describe functionality
    runner.welcomeUser();


    do {
      // ask the user if they want to create puzzles or solve a single puzzle
      String userGoal = runner.userGoals();

      /**
      * If the user wants to create puzzles, we give them the option of choosing
      * how many to create and how difficult to make them.
      **/
      if(userGoal.equals(CREATE)) {
        // how many?
        int numberToCreate = runner.getPuzzlesToCreate();
        // what difficulty?
        Sudoku_Generator.Level difficulty = runner.getPuzzleDifficulty();
        // create puzzles
        System.out.println("Creating " + numberToCreate + " puzzles of " + difficulty + " difficulty");

        boolean status = runner.createPuzzles(numberToCreate, difficulty);
        if(status != ERROR) {
          System.out.println("Done creating puzzles! Have fun solving them.");
        } else {
          System.out.println("Whoops! Something went wrong. :(");
        }
      }
      else if(userGoal.equals(SOLVE)) {
        // what is the file name?
        String fileName = runner.getPuzzleToSolve();

        // try and solve the puzzle located at that file location.
        runner.solvePuzzle(fileName);
      } else {
        System.out.println("Whoops! Something went wrong. :(");
      }

      // ask user if they want to exit the program
      String run_again = runner.ask_run_again();
      if(run_again.equals(runner.YES))
      {
        doAgain=true;
      }
      else
      {
        doAgain=false;
      }
    } while (doAgain==true);

    System.out.println("Thanks for using our program! Have a great day");
  }







  // this function will create and populate a folder full of N sudoku puzzles,
  // where 'N' is the number of puzzles to create. it also takes in a difficulty.
  private boolean createPuzzles(int numberPuzzles, Sudoku_Generator.Level difficulty) {
    try {
      // Create separate directories for the puzzles and their solutions, if they don't exist
      File puzzles = new File("puzzles");
      File puzzles_solved = new File("puzzles_solved");

      if(!puzzles.exists()) Files.createDirectory(Paths.get("./puzzles"));
      if(!puzzles_solved.exists()) Files.createDirectory(Paths.get("./puzzles_solved"));

      // Create both the solved and unsolved puzzle, then write them to text Files
      // in appropriate diretories
      Optional<Square[]> puzzle;
      Optional<Square[]> solvedPuzzle;
      for(int i = 0; i < numberPuzzles; ) {
        puzzle = this.generator.get_sudoku_puzzle(difficulty);

        if(puzzle.isPresent()) {
          Square[] present = puzzle.get();
          solvedPuzzle = this.solver.solve_puzzle(present);
          if(solvedPuzzle.isPresent()) {
            long suffix = System.currentTimeMillis();
            SudokuParser.writeSudoku(present, "./puzzles/puzzle_" + i + "_" + suffix + ".txt");
            SudokuParser.writeSudoku(solvedPuzzle.get(), "./puzzles_solved/puzzle_" + i + "_" + suffix + "_solution.txt");
          }
          // increment only if successful in creating a puzzle and it's solution
          ++i;
        }

        // reset the board so we can create a new one next time
        this.generator.refresh_sudoku_grid();
      }


    } catch (IOException ioe) {
      System.out.println("Error creating directories");
      return ERROR;
    }
    return true;
  }

  private void welcomeUser() {
    System.out.println("Welcome to the Sudoku Suite!");
    System.out.println("This program is designed so that you can either create " +
                        "some\nsudoku puzzles or try to solve a predefined one.");
  }

  // This method returns whether or not a user wants to create or solve a puzzle
  private String userGoals() {
    System.out.println("Would you like to 'create' or 'solve'?");
    String result = "";

    try {
      result =  keyboard.readLine();

      while(!result.equals(CREATE) && !result.equals(SOLVE)) {
        handleInvalidResponse(result, "'" + CREATE + "' or '" + SOLVE + "''");
        result = keyboard.readLine();
      }
    }
    catch (Exception e)
    {
      // in case of IOException
    }
    finally
    {
      return result;
    }
  }

  private int getPuzzlesToCreate() {
    System.out.println("How many puzzles would you like to create?");
    String result = "";

    boolean valid = false;
    int numPuzzles = -1;
    try{
      while(!valid) {
        result =  keyboard.readLine();

        try {
          numPuzzles = Integer.parseInt(result);
          if( numPuzzles > 0 ) {
            valid = true;
          } else {
            handleInvalidResponse(result, "Any positive integer");
          }
        } catch (NumberFormatException nfe) {
          handleInvalidResponse(result, "Any positive integer");
        }
      }
    } catch (Exception e) {
      // in case of IOException
    }
    return numPuzzles;
  }

  private Sudoku_Generator.Level getPuzzleDifficulty() {
    System.out.println("Would you like your puzzle difficulty to be \n'easy', " +
                       "'medium', 'difficult', or 'random'?");
    String difficulty = "";
    try {
        difficulty = keyboard.readLine();
        while(!isValidLevelType(difficulty)) {
          handleInvalidResponse(difficulty, "'easy', 'medium', 'difficult', or 'random'");
          difficulty = keyboard.readLine();
        }
    } catch (Exception e) {
      // this would be an IOException. if this happens then ¯\_(ツ)_/¯
    }

    return Sudoku_Generator.Level.valueOf(difficulty.toUpperCase());
  }

  private boolean isValidLevelType(String input) {
    for(Sudoku_Generator.Level level : Sudoku_Generator.Level.values()) {
      if(input.equalsIgnoreCase(level.toString())) {
        return true;
      }
    }
    return false;
  }

  private String getPuzzleToSolve() {
    System.out.println("What is the relative path to the puzzle you are trying to solve?");
    String path = "";
    try {
        path = keyboard.readLine();
    } catch (Exception e) {
      // this would be an IOException. if this happens then ¯\_(ツ)_/¯
    }
    return path;
  }

  // This function is designed to take a fileName passed by the user, parse
  // the sudoku puzzle that is in the file, solve it, and then save it to a new file.
  private void solvePuzzle(String fileName) {
    try {
      Square[] unsolvedPuzzle = SudokuParser.parseSudoku(fileName);
      Optional<Square[]> solvedPuzzle = this.solver.solve_puzzle(unsolvedPuzzle);

      if(solvedPuzzle.isPresent()) {
        String solutionFileName = getSolutionFileName(fileName);
        SudokuParser.writeSudoku(solvedPuzzle.get(), solutionFileName);
        System.out.println("Solved puzzle! See: " + solutionFileName);
      } else {
        System.out.println("No solutions exist for puzzle!");
      }

    } catch (IOException ioe) {
      System.out.println("File not found: " + fileName);
    }
  }

  private String getSolutionFileName(String origName) {
    String removedExtension = origName.substring(0, origName.lastIndexOf('.'));

    return removedExtension + "_solved.txt";
  }

  private static void handleInvalidResponse(String invalidResponse, String validResponses) {
    System.out.println("Sorry, '" + invalidResponse + "' is not a valid response.");
    System.out.println("Please enter one of the following: ");
    System.out.println(validResponses);
  }

  // This method returns whether or not a user wants to run the Sudoku program again
  private String ask_run_again() {
    System.out.println("Would you like to run program again? (Enter 'yes' or 'no')");
    String result = "";

    try {
      result =  keyboard.readLine();

      while(!result.equals(YES) && !result.equals(NO)) {
        handleInvalidResponse(result, "'" + YES + "' or '" + NO + "''");
        result = keyboard.readLine();
      }
    }
    catch (Exception e)
    {
      // in case of IOException
    }
    finally
    {
      return result;
    }
  }

}
