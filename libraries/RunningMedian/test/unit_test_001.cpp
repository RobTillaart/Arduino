//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-03
// PURPOSE: unit tests for the RunningMedian
//          https://github.com/RobTillaart/RunningMedian
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
#include "RunningMedian.h"



unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", RUNNING_MEDIAN_VERSION);

  RunningMedian samples = RunningMedian(5);
  assertEqual(5, samples.getSize());
  assertEqual(0, samples.getCount());

  // TODO default values?
}


unittest(test_basic_add)
{
  fprintf(stderr, "VERSION: %s\n", RUNNING_MEDIAN_VERSION);

  RunningMedian samples = RunningMedian(5);

  int cnt = 0;
  for (int i = 0, cnt = 0; i < 50; i+=10)
  {
    samples.add(i);
    cnt++;
    assertEqual(cnt, samples.getCount());
  }
  assertEqual(5, samples.getSize());
  assertEqualFloat(20, samples.getMedian(), 0.0001);
  assertEqualFloat(20, samples.getAverage(), 0.0001);
  assertEqualFloat(00, samples.getLowest(), 0.0001);
  assertEqualFloat(40, samples.getHighest(), 0.0001);
  
  samples.add(100);  // 6th element
  assertEqual(5, samples.getSize());
  assertEqual(5, samples.getCount());

  assertEqualFloat(30, samples.getMedian(), 0.0001);
  assertEqualFloat(40, samples.getAverage(), 0.0001);
  assertEqualFloat(10, samples.getLowest(), 0.0001);
  assertEqualFloat(100, samples.getHighest(), 0.0001);
  
  samples.clear();
  assertEqual(5, samples.getSize());
  assertEqual(0, samples.getCount());
}


unittest(test_big)
{
  fprintf(stderr, "VERSION: %s\n", RUNNING_MEDIAN_VERSION);

  RunningMedian samples = RunningMedian(100);
  assertEqual(100, samples.getSize());
  assertEqual(0, samples.getCount());

  for (int i = 0; i < 110; i++)
  {
    samples.add(i);
  }
  assertEqual(100, samples.getSize());
  assertEqual(100, samples.getCount());

  assertEqualFloat(59.5, samples.getMedian(), 0.0001);
  assertEqualFloat(59.5, samples.getAverage(), 0.0001);
  assertEqualFloat(10, samples.getLowest(), 0.0001);
  assertEqualFloat(109, samples.getHighest(), 0.0001);

  samples.clear();
  assertEqual(100, samples.getSize());
  assertEqual(0, samples.getCount());
}


unittest_main()

// --------
