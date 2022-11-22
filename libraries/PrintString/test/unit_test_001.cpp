//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the PrintString library
//          https://github.com/RobTillaart/PrintString
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
#include "PrintString.h"


char buffer[100];


unittest_setup()
{
  fprintf(stderr, "PRINTSTRING_VERSION: %s\n", (char *) PRINTSTRING_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  PrintString ps;

  assertEqual(0,   ps.size());

  //  not so nice but best I could do on short term
  ps.print("Hello World");
  ps.getString().toCharArray(buffer, 100);
  fprintf(stderr, "%s\n", buffer);
  assertEqual(11, ps.size());

  ps.print(" and moon");
  ps.getString().toCharArray(buffer, 100);
  fprintf(stderr, "%s\n", buffer);
  assertEqual(20, ps.size());

  ps.clear();
  assertEqual(0, ps.size());
}


unittest_main()


// --------
