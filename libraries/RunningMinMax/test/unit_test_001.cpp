//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-02-01
// PURPOSE: unit tests for the RunningMinMax
//          https://github.com/RobTillaart/RunningMinMax
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
#include "RunningMinMax.h"


unittest_setup()
{
  fprintf(stderr, "RUNNING_MINMAX_LIB_VERSION: %s\n", (char *) RUNNING_MINMAX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  RunningMinMax samples = RunningMinMax(5);
  assertEqual(5, samples.getSize());
  assertEqual(0, samples.getCount());
}


unittest(test_basic_add)
{
  RunningMinMax samples = RunningMinMax(5);

  int cnt = 0;
  for (int i = 0, cnt = 0; i < 50; i+=10)
  {
    samples.add(i);
    cnt++;
    assertEqual(cnt, samples.getCount());
  }
  assertEqual(5, samples.getSize());
  assertEqualFloat(0, samples.getMinimum(), 0.0001);
  assertEqualFloat(20, samples.getAverage(), 0.0001);
  assertEqualFloat(40, samples.getMaximum(), 0.0001);


  samples.add(100);  //  6th element
  assertEqual(5, samples.getSize());
  assertEqual(5, samples.getCount());

  assertEqualFloat(10, samples.getMinimum(), 0.0001);
  assertEqualFloat(40, samples.getAverage(), 0.0001);
  assertEqualFloat(100, samples.getMaximum(), 0.0001);

  samples.reset();
  assertEqual(5, samples.getSize());
  assertEqual(0, samples.getCount());
}


unittest_main()


//  -- END OF FILE --
