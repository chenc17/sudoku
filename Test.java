public class Test
{
	public static void main(String[] args)
	{
		Square mySquare = new Square(6, 8, 5);
		System.out.println(mySquare.get_column() +
			" " + mySquare.get_row() + " " + mySquare.get_region() + 
			" " + mySquare.get_value() + " " + mySquare.get_square_no());
	}
	
}