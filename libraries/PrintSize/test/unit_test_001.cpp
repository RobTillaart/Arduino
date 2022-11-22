//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the PrintSize library
//          https://github.com/RobTillaart/PrintSize
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
#include "PrintSize.h"


unittest_setup()
{
  fprintf(stderr, "PRINTSIZE_VERSION: %s\n", (char *) PRINTSIZE_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  PrintSize ps;

  assertEqual(0, ps.total());
}



unittest(test_print)
{
  PrintSize ps;

  assertEqual(0,  ps.total());
  assertEqual(11, ps.print("Hello World"));
  assertEqual(11, ps.total());
  assertEqual(6,  ps.print(PI, 4));
  assertEqual(17, ps.total());

  ps.reset();
  assertEqual(0,  ps.total());
  assertEqual(13, ps.println("Hello World"));
  assertEqual(13, ps.total());
  assertEqual(8,  ps.println(PI, 4));
  assertEqual(21, ps.total());
}



unittest(test_write)
{
  PrintSize ps;

  assertEqual(0,  ps.total());
  assertEqual(1, ps.write('c'));

  ps.reset();
  assertEqual(0,  ps.total());
  char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed mattis eget odio ut";
  assertEqual(strlen(str), ps.write((uint8_t *)str, strlen(str)));
  assertEqual(strlen(str), ps.total());
}


unittest_main()

// --------
