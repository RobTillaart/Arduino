//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-20
// PURPOSE: unit tests for the DistanceTable library
//          https://github.com/RobTillaart/DistanceTable
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
#include "DistanceTable.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  DistanceTable dt(12);
  fprintf(stderr, "%s\n", DISTANCETABLE_LIB_VERSION);
  
  assertEqual(12, dt.dimension());
  assertEqual(60, dt.elements());
  assertEqual(240, dt.memoryUsed());
  
  for (int i = 0; i < 12; i += 4)
  {
    for (int j = i+1; j < 12; j += 3)
    {
      dt.set(i, j, i * j);
      assertEqual(i * j, dt.get(i, j));
      assertEqual(i * j, dt.get(j, i));
    }
  }
  
  dt.clear();
  for (int i = 0; i < 12; i += 4)
  {
    for (int j = i+1; j < 12; j += 3)
    {
      assertEqual(0, dt.get(j, i));
    }
  }

}


unittest_main()

// --------
