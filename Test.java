public class Test
{
	private static int TOO_BIG = 10;
	private static int TOO_SMALL = -1;
	private static int JUST_RIGHT = 1;

	public static void main(String[] args)
	{
			validateHandlesAllValidParametersTest();
			validateHandlesTooLargeRowTest();
			validateHandlesTooBigColTest();
			validateHandlesTooBigValTest();

			validateHandlesTooSmallRowTest();
			validateHandlesTooSmallColTest();
			validateHandlesTooSmallValTest();
	}

	// *** add tests to ensure that the get region method works properly

	// *** add some tests to test that the square number is being set properly

	/**
	*	The following tests are used to verify that our validate method is
	* accepting and rejecting the correct sets of values
	**/
	public static void validateHandlesAllValidParametersTest() {
		System.out.println("validateHandlesAllValidParametersTest");
		boolean result = Square.validate(JUST_RIGHT, JUST_RIGHT, JUST_RIGHT);
		assertEquals("Expected validate to return true", true, result);
	}

	public static void validateHandlesTooLargeRowTest() {
		System.out.println("validateHandlesTooLargeRowTest");
		boolean result = Square.validate(TOO_BIG, JUST_RIGHT, JUST_RIGHT);
		assertEquals("Expected validate to return false", false, result);
	}
	public static void validateHandlesTooBigColTest() {
		System.out.println("validateHandlesTooBigColTest");
		boolean result = Square.validate(JUST_RIGHT, TOO_BIG, JUST_RIGHT);
		assertEquals("Expected validate to return false", false, result);
	}
	public static void validateHandlesTooBigValTest() {
		System.out.println("validateHandlesTooBigValTest");
		boolean result = Square.validate(JUST_RIGHT, JUST_RIGHT, TOO_BIG);
		assertEquals("Expected validate to return false", false, result);
	}

	public static void validateHandlesTooSmallRowTest() {
		System.out.println("validateHandlesTooSmallRowTest");
		boolean result = Square.validate(TOO_SMALL, JUST_RIGHT, JUST_RIGHT);
		assertEquals("Expected validate to return false", false, result);
	}
	public static void validateHandlesTooSmallColTest() {
		System.out.println("validateHandlesTooSmallColTest");
		boolean result = Square.validate(JUST_RIGHT, TOO_SMALL, JUST_RIGHT);
		assertEquals("Expected validate to return false", false, result);
	}
	public static void validateHandlesTooSmallValTest() {
		System.out.println("validateHandlesTooSmallValTest");
		boolean result = Square.validate(JUST_RIGHT, JUST_RIGHT, TOO_SMALL);
		assertEquals("Expected validate to return false", false, result);
	}

	// helper method to check that a square has all invalid values
	public static void verifySquareIsInvalid(Square mySquare) {
		assertEquals("Expected -1, but row was " + mySquare.get_row(), Square.INVALID_VAL, mySquare.get_row());
		assertEquals("Expected -1, but col was " + mySquare.get_column(), Square.INVALID_VAL, mySquare.get_column());
		assertEquals("Expected -1, but val was " + mySquare.get_value(), Square.INVALID_VAL, mySquare.get_value());
		assertEquals("Expected -1, but val was " + mySquare.get_value(), Square.INVALID_VAL, mySquare.get_region());
		assertEquals("Expected -1, but val was " + mySquare.get_value(), Square.INVALID_VAL, mySquare.get_square_no());
	}

	// Barebones method to test if two objects are equal
	public static void assertEquals(String message, Object expectedVal, Object actualVal) {
		boolean equal = expectedVal.equals(actualVal);

		if(!equal) {
			System.out.println(message);
		}
	}

}
