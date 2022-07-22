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
  fprintf(stderr, "DISTANCETABLE_LIB_VERSION: %s\n", (char *) DISTANCETABLE_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  DistanceTable dt0(0);

  assertEqual(0, dt0.dimension());
  assertEqual(0, dt0.elements());
  assertEqual(0, dt0.memoryUsed());

  DistanceTable dt1(1);

  assertEqual(1, dt1.dimension());
  assertEqual(0, dt1.elements());
  assertEqual(0, dt1.memoryUsed());

  DistanceTable dt2(2);

  assertEqual(2, dt2.dimension());
  assertEqual(1, dt2.elements());
  assertEqual(4, dt2.memoryUsed());

  DistanceTable dt11(11);

  assertEqual(11, dt11.dimension());
  assertEqual(55, dt11.elements());
  assertEqual(220, dt11.memoryUsed());

  DistanceTable dt12(12);

  assertEqual(12, dt12.dimension());
  assertEqual(66, dt12.elements());
  assertEqual(264, dt12.memoryUsed());

}


unittest(test_get_set_clear)
{
  DistanceTable dt(12);

  for (int i = 0; i < 12; i += 4)
  {
    for (int j = i + 1; j < 12; j += 3)
    {
      dt.set(i, j, i * j);
      assertEqual(i * j, dt.get(i, j));
      assertEqual(i * j, dt.get(j, i));
    }
  }

  fprintf(stderr, "\n");
  dt.clear();
  for (int i = 0; i < 12; i += 4)
  {
    for (int j = i + 1; j < 12; j += 3)
    {
      assertEqual(0, dt.get(j, i));
    }
  }
}


unittest(test_invert)
{
  DistanceTable dt(12);

  assertFalse(dt.getInvert());
  dt.setInvert(true);
  assertTrue(dt.getInvert());
  dt.setInvert();
  assertFalse(dt.getInvert());
  dt.setInvert(true);

  dt.set(3, 2, 10);
  assertEqualFloat( 10, dt.get(3, 2), 0.001);
  assertEqualFloat(-10, dt.get(2, 3), 0.001);

  dt.setAll(25);
  assertEqualFloat( 25, dt.get(3, 2), 0.001);
  assertEqualFloat(-25, dt.get(2, 3), 0.001);

  dt.set(2, 3, 10);
  assertEqualFloat(-10, dt.get(3, 2), 0.001);
  assertEqualFloat( 10, dt.get(2, 3), 0.001);
}


unittest(test_min_max)
{
  DistanceTable dt(12);

  for (int i = 0; i < 12; i++)
  {
    for (int j = i + 1; j < 12; j++)
    {
      dt.set(i, j, i * j);
    }
  }

  uint8_t x, y;

  fprintf(stderr, "CNT: %d\n", dt.count(30, 0.001));
  fprintf(stderr, "MIN: %f\t", dt.minimum(x, y));
  fprintf(stderr, "%d\t", x);
  fprintf(stderr, "%d\n", y);
  fprintf(stderr, "MAX: %f\t", dt.maximum(x, y));
  fprintf(stderr, "%d\t", x);
  fprintf(stderr, "%d\n", y);
  fprintf(stderr, "SUM: %f\t", dt.sum());
  fprintf(stderr, "AVG: %f\t", dt.average());
}


unittest_main()

// --------
