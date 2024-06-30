//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-06-30
// PURPOSE: unit tests for RunAvgWeight
//          https://github.com/RobTillaart/RunAvgWeight
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
#include "RunAvgWeight.h"


unittest_setup()
{
  fprintf(stderr, "RUNAVGWEIGHT_LIB_VERSION: %s\n", (char *) RUNAVGWEIGHT_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_zero_elements)
{
  RunAvgWeight myRA(10);
  myRA.clear();

  int size = myRA.getSize();
  assertEqual(10, size);

  int cnt = myRA.getCount();
  assertEqual(0, cnt);

  float x = myRA.getAverage();
  assertNAN(x);
}


unittest(test_min_max)
{
  RunAvgWeight myRA(10);
  myRA.clear();

  for (int i = -5; i < 6; i++)
  {
    myRA.addValue(i);
  }

  float mi = myRA.getMin();
  assertEqual(-5, mi);
  float ma = myRA.getMax();
  assertEqual(5, ma);

  mi = myRA.getMinInBuffer();
  assertEqual(-4, mi);
  ma = myRA.getMaxInBuffer();
  assertEqual(5, ma);
}


unittest(test_buffer_full)
{
  RunAvgWeight myRA(10);
  myRA.clear();
  assertFalse(myRA.bufferIsFull());

  for (int i = 0; i < 9; i++)
  {
    myRA.addValue(i);
    assertFalse(myRA.bufferIsFull());
  }

  myRA.addValue(42);
  assertTrue(myRA.bufferIsFull());
}


unittest(test_large)
{
  RunAvgWeight myRA(300);
  myRA.clear();
  assertFalse(myRA.bufferIsFull());

  for (int i = 0; i < 299; i++)
  {
    myRA.addValue(i);
    assertFalse(myRA.bufferIsFull());
  }

  myRA.addValue(42);
  assertTrue(myRA.bufferIsFull());
}


unittest_main()


// --------
