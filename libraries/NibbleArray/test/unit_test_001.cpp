//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-02
// PURPOSE: unit tests for the nibbleArray
//          https://github.com/RobTillaart/nibbleArray
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
#include "nibbleArray.h"


unittest_setup()
{
}

unittest_teardown()
{
  fprintf(stderr, "\n");
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

unittest(test_all)
{
  fprintf(stderr, "VERSION: %s\n", NIBBLEARRAY_LIB_VERSION);

  nibbleArray na(500);
  assertEqual(500, na.size());

  fprintf(stderr, "get / set\n");
  for (int i = 0; i < 500; i += 23)
  {
    fprintf(stderr, "%d\t", i);
    int x = random(16);
    na.set(i, x);
    assertEqual(x, na.get(i));
  }
  assertEqual(NIBBLEARRAY_ERROR_INDEX, na.set(542, 10));
  assertEqual(NIBBLEARRAY_ERROR_INDEX, na.get(542));

  na.clear();
  for (int i = 0; i < 500; i += 23)
  {
    fprintf(stderr, "%d\t", i);
    assertEqual(0, na.get(i));
  }
  
  na.setAll(15);
  uint32_t sum = 0;
  for (int i = 0; i < 500; i += 23)
  {
    fprintf(stderr, "%d\t", i);
    assertEqual(15, na.get(i));
    sum += na.get(i);
  }
  assertEqual(330, sum);  // not all 500 all summed!

}

unittest_main()

// --------
