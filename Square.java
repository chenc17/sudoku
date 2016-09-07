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
	private int value; //1 to 9
	private int square_no; //0 based (0 to 80)
	
	public static final int INVALID_VAL = -1;
	public static final int MAX_SUDOKU_VAL=9;
	public static final int MIN_SUDOKU_VAL=1;
	
	
	//default constructor 
	public Square()
	{
		this(INVALID_VAL, INVALID_VAL, INVALID_VAL);
	}
	
	
	public Square(int row_index, int col_index, int val)
	{
		//remember that row and col are 0-based
		if((row_index<MAX_SUDOKU_VAL && row_index>=MIN_SUDOKU_VAL-1) &&
			(col_index<MAX_SUDOKU_VAL && col_index>=MIN_SUDOKU_VAL-1)&&
			(val<=MAX_SUDOKU_VAL && val>=MIN_SUDOKU_VAL))
		{
			column=col_index;
			row=row_index;
			region=get_region_from_row_col(row_index, col_index);
			value=val;
			square_no=(MAX_SUDOKU_VAL*(row_index))+col_index;
		}
		else
		{

			System.out.println("Invalid values for constructor parameters!");
			column=INVALID_VAL;
			row=INVALID_VAL;
			region=INVALID_VAL;
			value=INVALID_VAL;
			square_no=INVALID_VAL;
		}
		
	}
	
	//there are 9 regions in a sudoku board
	//0 | 1 | 2
	//3 | 4 | 5 
	//6 | 7 | 8
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
	
}