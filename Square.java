import java.util.HashSet;
import java.util.Set;
import java.util.Arrays;
import java.util.Collections;

//Square Class
//A square object is one box in a Sudoku grid
//It has a column, row, 3x3 region, value, and square number
//@authors Christine Chen and Matt Hino
//@date 9/6/2016
public class Square
{
	private int column; //0 based
	private int row; //0 based
	private int region; //0 based
	private int value; //1 to 9, 0 if unknown
	private int square_no; //0 based (0 to 80)
	private Set<Integer> possible_values;

	public static final int INVALID_VAL = -1;
	public static final int MAX_SUDOKU_VAL=9;
	public static final int UNKNOWN = 0;
	public static final int MIN_SUDOKU_VAL=0; // 0 indicates a "blank" square
	public static final int MAX_ROW_COL = 9;
	public static final int MIN_ROW_COL = 1;

	//default constructor
	public Square()
	{
		this(INVALID_VAL, INVALID_VAL, INVALID_VAL);
	}

	public Square(int row_index, int col_index, int val)
	{
		if( validate(row_index, col_index, val) ) {
			this.column = col_index;
			this.row = row_index;
			this.region = get_region_from_row_col(row_index, col_index);
			this.value = val;
			this.square_no = (MAX_SUDOKU_VAL*(row_index)) + col_index;
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

	public static boolean validate(int row_index, int col_index, int val) {
		if((row_index<MAX_ROW_COL && row_index>=MIN_ROW_COL) &&
			 (col_index<MAX_ROW_COL && col_index>=MIN_ROW_COL)&&
			 (val<=MAX_SUDOKU_VAL && val>=MIN_SUDOKU_VAL))
		{
			return true;
		}

		return false;
	}

}
