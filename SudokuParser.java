import java.io.*;
import java.util.*;

public class SudokuParser {

  private static final String LINE_SEPARATOR = "+=======================+";
  private static final int REGION_SIZE = 3;

  // takes a sudoku puzzle and writes it to a file
  public static void writeSudoku(Square[] puzzle, String fileName) throws IOException {
    try(BufferedWriter bw = new BufferedWriter(new FileWriter(fileName))) {
      for(int square_no = 0; square_no < puzzle.length; square_no++ ){

        // write a new line if we've written a full row
        if(square_no%Square.NUM_SQUARES_ROW_COL==0 && square_no != 0) {
          bw.write("| ");
          bw.newLine();
        }

        // write a horizontal bar to separate regions
        if(square_no%(Square.NUM_SQUARES_ROW_COL * REGION_SIZE) == 0) {
          bw.write(LINE_SEPARATOR);
          bw.newLine();
        }

        // write a pipe to separate the regions
        if(square_no%REGION_SIZE == 0) {
          bw.write("| ");
        }

        String numberToWrite = Integer.toString(puzzle[square_no].get_value());
        if(puzzle[square_no].get_value() == Square.UNKNOWN) {
          bw.write("- ");
        } else {
          bw.write(numberToWrite + " ");
        }
      }

      bw.write("| ");
      bw.newLine();
      bw.write(LINE_SEPARATOR);
      bw.close();
    }
  }

  // Reads in a sudoku grid from a text file and converts it to a square array
  public static Square[] parseSudoku(String fileName) throws IOException {

    List<Square> squareList = new ArrayList<Square>();

    // open the file and read line by line
    // skip lines that start with the '+' character
    // remove the pipes and convert the '-' to '0'
    // split the string by spaces then get each int value for the square
    try(BufferedReader br = new BufferedReader(new FileReader(fileName))) {
      int square_no = 0;
      for(String line; (line = br.readLine()) != null; ) {
          // if it's a non-spacing line, then convert to squares
          if(line.length() > 0 && (line.charAt(0) != '+')) {
            line = line.replace("|", "").replace("-", "0");
            String[] values = line.split(" ");

            for(int i=0; i < values.length; i++) {
              if(values[i].length() > 0) {
                try {
                  squareList.add(new Square(square_no, Integer.parseInt(values[i])));
                } catch (NumberFormatException nfe) {
                  System.out.println("Error in parsing Sudoku from file" + nfe);
                  System.out.println("Unable to convert grid values.");
                } finally {
                  square_no++;
                }
              }
            }
          }
      }

      // after parsing the file, return the squareList
      return squareList.toArray(new Square[squareList.size()]);
    }
  }

  private static void printStringArray(String[] strings) {
    for(String string: strings) {
      System.out.print(string + " " );
    }
    System.out.print("\n");
  }

}
