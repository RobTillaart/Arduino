//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the LineFormatter library
//          https://github.com/RobTillaart/LineFormatter
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "LineFormatter.h"


unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  LineFormatter L;

  assertEqual(0, L.getMaxLength());
  L.setMaxLength(80);
  assertEqual(80, L.getMaxLength());

  assertEqual(0, L.getAutoNewLine());
  L.setAutoNewLine(5);
  assertEqual(5, L.getAutoNewLine());
}


unittest(test_position)
{
  LineFormatter L;

  assertEqual(0, (int)L.getPos());
  assertEqual(20, (int)L.gotoPos(20));
  assertEqual(20, (int)L.gotoPos(15));

  L.repeat(10, '*');
  assertEqual(30, (int)L.getPos());
  L.repeat(10, "--");
  assertEqual(50, (int)L.getPos());
}

unittest(test_tab)
{
  LineFormatter L;

  fprintf(stderr, "tab setting\n");
  for (int i = 8; i <= 80; i += 8)
  {
    L.addTab(i);
  }
  assertEqual(10, L.getTabCount());
  for (int i = 0; i < L.getTabCount(); i++)
  {
    fprintf(stderr, "%d\t", 8 + i*8);
    assertEqual(8 + i*8, L.getTabStop(i));
  }

  fprintf(stderr, "tab test - !! cur pos is one before tab pos\n");
  for (int i = 0; i < L.getTabCount(); i++)
  {
    fprintf(stderr, "%d\t", 8 + i*8);  // tabpos
    L.write('\t');
    assertEqual(8 + i*8, (int)L.getPos() + 1 );  // current pos is just before 
  }

}


unittest_main()

// --------
