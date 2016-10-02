#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <set>
#include <assert.h>
#include "Square.h"


using namespace std;


//Test
//This class mainly contains tests that verify
//the robustness and accuracy of the Square class
//setter methods

//@authors Matt Hino and Christine Chen
//@date 10/1/2016

class Test
{
  private:
     static const int TOO_BIG = 81;
	   static const int TOO_SMALL = -1;
	   static const int VALID = 5;

  public:
    static void validateHandlesAllValidParametersTest(void);
    static void validateHandlesTooLargeSquareNumTest(void);
    static void testToString(void);
    int main(int argc, char **argv);


};

int main(int argc, char **argv)
{
  cout << "Tests for Square.cpp:\n";
  Test::validateHandlesAllValidParametersTest();

  Test::validateHandlesTooLargeSquareNumTest();
  Test::testToString();

  return 0;
}

void Test::validateHandlesAllValidParametersTest() {
  cout << "validateHandlesAllValidParametersTest\n";
  bool result = Square::validate(Test::VALID, Test::VALID);
  assert(result==true);
  cout << "\n";
}

void Test::validateHandlesTooLargeSquareNumTest() {
  cout << "validateHandlesTooLargeSquareNumTest\n";
  bool result = Square::validate(Test::TOO_BIG, Test::VALID);
  assert(result==false);
  cout << "\n";
}

void Test::testToString() {
  cout << "testToString\n";
  Square test_sq = Square::Square(3, 2);
  cout << "Result: " << test_sq.toString() << "\n";


}
