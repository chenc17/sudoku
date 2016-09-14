import java.util.HashSet;
import java.util.Set;
import java.util.Arrays;
import java.util.Collections;

//Test
//This class mainly contains tests that verify
//the the robustness and accuracy of the Square class
//setter methods 

//@authors Matt Hino and Christine Chen
//@date 9/13/2016
public class Test
{
	private static final int TOO_BIG = 81;
	private static final int TOO_SMALL = -1;
	private static final int VALID = 5;

	public static void main(String[] args)
	{
			System.out.println("Tests for Square Class:");
			validateHandlesAllValidParametersTest();

			validateHandlesTooLargeSquareNumTest();
			validateHandlesTooBigValTest();

			validateHandlesTooSmallSquareNumTest();
			validateHandlesTooSmallValTest();

			initPossibleValuesHandlesInvalidValTest();
			initPossibleValuesHandlesKnownValTest();
			initPossibleValuesHandlesUnknownValTest();

			System.out.println();
	}

	// *** add tests to ensure that the get region method works properly

	// *** add some tests to test that the square number is being set properly

	/**
	*	The following tests are used to verify that our validate method is
	* accepting and rejecting the correct sets of values
	**/
	public static void validateHandlesAllValidParametersTest() {
		System.out.println("validateHandlesAllValidParametersTest");
		boolean result = Square.validate(VALID, VALID);
		assertEquals("Expected validate to return true", true, result);
	}

	public static void validateHandlesTooLargeSquareNumTest() {
		System.out.println("validateHandlesTooLargeSquareNumTest");
		boolean result = Square.validate(TOO_BIG, VALID);
		assertEquals("Expected validate to return false", false, result);
	}

	public static void validateHandlesTooBigValTest() {
		System.out.println("validateHandlesTooBigValTest");
		boolean result = Square.validate(VALID, TOO_BIG);
		assertEquals("Expected validate to return false", false, result);
	}

	public static void validateHandlesTooSmallSquareNumTest() {
		System.out.println("validateHandlesTooSmallSquareNumTest");
		boolean result = Square.validate(TOO_SMALL, VALID);
		assertEquals("Expected validate to return false", false, result);
	}

	public static void validateHandlesTooSmallValTest() {
		System.out.println("validateHandlesTooSmallValTest");
		boolean result = Square.validate(VALID, TOO_SMALL);
		assertEquals("Expected validate to return false", false, result);
	}

	/**
	* The following tests that the initialization of the possible values set is
	* working properly
	**/
	public static void initPossibleValuesHandlesInvalidValTest() {
		System.out.println("initPossibleValuesHandlesInvalidValTest");
		Set<Integer> actual = Square.getInitPossibleValues(-1);
		Set<Integer> expected = Collections.emptySet();
		assertEquals("Sets were not equal, expected empty but got " + actual, expected, actual);
	}

	public static void initPossibleValuesHandlesKnownValTest() {
		System.out.println("initPossibleValuesHandlesKnownValTest");
		Set<Integer> actual = Square.getInitPossibleValues(1);
		Set<Integer> expected = Collections.emptySet();
		assertEquals("Sets were not equal, expected empty but got " + actual, expected, actual);
	}

	public static void initPossibleValuesHandlesUnknownValTest() {
		System.out.println("initPossibleValuesHandlesUnknownValTest");
		Set<Integer> actual = Square.getInitPossibleValues(0);
		Set<Integer> expected = new HashSet<>(Arrays.asList(1,2,3,4,5,6,7,8,9));
		assertEquals("Sets were not equal, expected empty but got " + actual, expected, actual);
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
