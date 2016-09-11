import java.util.HashSet;
import java.util.Set;
import java.util.Arrays;
import java.util.Collections;
import java.lang.Comparable;

//Square Class
//A square object is one box in a Sudoku grid
//It has a column, row, 3x3 region, value, and square number
//@authors Christine Chen and Matt Hino
//@date 9/10/2016
public class Square implements Comparable<Square>
{
	private int column; //0 based
	private int row; //0 based
	private int region; //0 based
	private int value; //1 to 9, 0 if unknown
	private int square_no; //0 based (0 to 80)
	private Set<Integer> possible_values;


	public static final int INVALID_VAL = -1;
	public static final int NUM_SQUARES_ROW_COL = 9;
	public static final int MAX_SUDOKU_VAL=9;
	public static final int UNKNOWN = 0;
	public static final int MIN_SUDOKU_VAL=0; // 0 indicates a "blank" square
	public static final int MAX_ROW_COL = 8;
	public static final int MIN_ROW_COL = 0;
	public static final int NUM_SQUARES = (NUM_SQUARES_ROW_COL)*(NUM_SQUARES_ROW_COL);

	//default constructor
	public Square()
	{
		this(INVALID_VAL, INVALID_VAL);
	}

	public Square(int square_number, int val)
	{
		if(validate(square_number, val)) {
			this.row = get_row_idx_init(square_number);
			this.column = get_col_idx_init(this.row, square_number);
			this.region = get_region_from_row_col(this.row, this.column);
			this.value = val;
			this.square_no = square_number;
		}
		else
		{
			// System.out.println("Invalid values for constructor parameters!");
			this.column=INVALID_VAL;
			this.row=INVALID_VAL;
			this.region=INVALID_VAL;
			this.value=INVALID_VAL;
			this.square_no=INVALID_VAL;
		}

		this.possible_values = getInitPossibleValues(val);
	}

	private int get_row_idx_init(int square_num)
	{
		int row_idx = square_num/(this.NUM_SQUARES_ROW_COL);
		return row_idx;
	}

	private int get_col_idx_init(int row_idx, int square_num)
	{
		int col_idx=square_num-((this.NUM_SQUARES_ROW_COL)*row_idx);
		return col_idx;
	}

	// there are 9 regions in a sudoku board
	// 0 | 1 | 2
	// 3 | 4 | 5
	// 6 | 7 | 8
	//this method calculates a square's region based on its row and col
	private int get_region_from_row_col(int row, int col)
	{
		int region=0;
		int row_region=0;
		int col_region=0;

		if(row>=0 && row<=2)
		{
			row_region=0;
		}
		if(row>=3 && row<=5)
		{
			row_region=1;
		}
		if(row>=6 && row<=8)
		{
			row_region=2;
		}

		if(col>=0 && col<=2)
		{
			col_region=0;
		}
		if(col>=3 && col<=5)
		{
			col_region=1;
		}
		if(col>=6 && col<=8)
		{
			col_region=2;
		}

		region=(3*row_region)+col_region;
		return region;
	}

	// This method creates the set of possible values the square could be
	protected static Set<Integer> getInitPossibleValues(int val) {
		if(val == UNKNOWN) {
			return new HashSet<>(Arrays.asList(1,2,3,4,5,6,7,8,9));
		} else {
			return Collections.emptySet();
		}
	}

	//getters
	public int get_column()
	{
		return column;
	}

	public int get_row()
	{
		return row;

	}

	public int get_region()
	{
		return region;
	}

	public int get_value()
	{
		return value;
	}

	public void set_value(int potential_value)
	{
		if(validate(this.square_no, potential_value)==true)
		{
			this.value = potential_value;
		}
		else
		{
			this.value = INVALID_VAL;
		}
	}

	public void reset_possible_values()
	{
		for(int i=MIN_SUDOKU_VAL+1; i<=MAX_SUDOKU_VAL; i++)
		{
			this.possible_values.add(i);
		}
	}

	public int get_square_no()
	{
		return square_no;
	}

	// remove a number from the set of potential numbers the square could be
	public void remove_int(int value) {
		this.possible_values.remove(value);
	}

	public Set<Integer> get_possible_values() {
		return this.possible_values;
	}

	//square_num can be in the range 0 to 80 and values in set {0,...,9}
	public static boolean validate(int square_num, int val) {
		if((square_num<NUM_SQUARES) && (square_num>=MIN_ROW_COL) &&
			 (val>=MIN_SUDOKU_VAL && val<=MAX_SUDOKU_VAL))
		{
			return true;
		}

		return false;
	}

	// this method allows us to sort a list of squares by their square number
	public int compareTo(Square otherSquare) {
		return Integer.compare(this.square_no, otherSquare.get_square_no());
	}

	public String toString() {
		return String.format("Square Num: %d, Row: %d, Col: %d, Region: %d, Val: %d", square_no, row, column, region, value);
	}

}
