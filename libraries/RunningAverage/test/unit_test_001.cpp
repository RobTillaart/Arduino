//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for runningAverage
//          https://github.com/RobTillaart/RunningAverage
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
#include "RunningAverage.h"


unittest_setup()
{
  fprintf(stderr, "RUNNINGAVERAGE_LIB_VERSION: %s\n", (char *) RUNNINGAVERAGE_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_zero_elements)
{
  RunningAverage myRA(10);
  myRA.clear();

  int size = myRA.getSize();
  assertEqual(10, size);

  int cnt = myRA.getCount();
  assertEqual(0, cnt);

  float x = myRA.getAverage();
  assertNAN(x);
}


unittest(test_min_max_sum)
{
  RunningAverage myRA(10);
  myRA.clear();

  for (int i = -5; i < 6; i++)
  {
    myRA.addValue(i);
  }

  float mi = myRA.getMin();
  assertEqualFloat(-5, mi, 0.001);
  float ma = myRA.getMax();
  assertEqualFloat(5, ma, 0.001);

  mi = myRA.getMinInBuffer();
  assertEqualFloat(-4, mi, 0.001);
  ma = myRA.getMaxInBuffer();
  assertEqualFloat(5, ma, 0.001);

  float sum = myRA.getSum();
  assertEqualFloat(5, sum, 0.001);
}


unittest(test_buffer_full)
{
  RunningAverage myRA(10);
  myRA.clear();
  assertFalse(myRA.bufferIsFull());

  for (int i = 0; i < 9; i++)
  {
    myRA.addValue(i);
  }
  assertFalse(myRA.bufferIsFull());

  myRA.addValue(42);
  assertTrue(myRA.bufferIsFull());
}


unittest(test_large)
{
  RunningAverage myRA(300);
  myRA.clear();
  assertFalse(myRA.bufferIsFull());

  for (int i = 0; i < 299; i++)
  {
    myRA.addValue(i);
  }
  assertFalse(myRA.bufferIsFull());

  myRA.addValue(42);
  assertTrue(myRA.bufferIsFull());
}


unittest(test_partial)
{
  RunningAverage myRA(100);
  myRA.clear();
  assertFalse(myRA.bufferIsFull());

  myRA.setPartial(10);
  for (int i = 0; i < 100; i++)
  {
    myRA.addValue(i);
  }
  assertEqualFloat(94.5, myRA.getAverage(), 0.001);

  myRA.setPartial(20);
  for (int i = 0; i < 100; i++)
  {
    myRA.addValue(i);
  }
  assertEqualFloat(89.5, myRA.getAverage(), 0.001);
}


unittest(test_last)
{
  RunningAverage myRA(300);
  myRA.clear();
  assertFalse(myRA.bufferIsFull());

  for (int i = 0; i < 1000; i++)
  {
    myRA.addValue(i);
  }

  fprintf(stderr, "\nPARTIAL: 0\n");
  assertNAN(myRA.getMinInBufferLast(0));
  assertNAN(myRA.getAverageLast(0));
  assertNAN(myRA.getMaxInBufferLast(0));
  assertNAN(myRA.getStandardDeviationLast(0));

  fprintf(stderr, "\nPARTIAL: 1\n");
  assertEqualFloat(999.0, myRA.getMinInBufferLast(1), 0.001);
  assertEqualFloat(999.0, myRA.getAverageLast(1), 0.001);
  assertEqualFloat(999.0, myRA.getMaxInBufferLast(1), 0.001);
  assertEqualFloat(0, myRA.getStandardDeviationLast(1), 0.001);

  fprintf(stderr, "\nPARTIAL: 10\n");
  assertEqualFloat(990.0, myRA.getMinInBufferLast(10), 0.001);
  assertEqualFloat(994.5, myRA.getAverageLast(10), 0.001);
  assertEqualFloat(999.0, myRA.getMaxInBufferLast(10), 0.001);
  assertEqualFloat(3.02765, myRA.getStandardDeviationLast(10), 0.001);

  fprintf(stderr, "\nPARTIAL: 100\n");
  assertEqualFloat(900.0, myRA.getMinInBufferLast(100), 0.001);
  assertEqualFloat(949.5, myRA.getAverageLast(100), 0.001);
  assertEqualFloat(999.0, myRA.getMaxInBufferLast(100), 0.001);
  assertEqualFloat(29.0115, myRA.getStandardDeviationLast(100), 0.001);

  fprintf(stderr, "\nPARTIAL: 1000\n");
  assertEqualFloat(700.0, myRA.getMinInBufferLast(1000), 0.001);
  assertEqualFloat(849.5, myRA.getAverageLast(1000), 0.001);
  assertEqualFloat(999.0, myRA.getMaxInBufferLast(1000), 0.001);
  assertEqualFloat(86.7468, myRA.getStandardDeviationLast(1000), 0.001);

}


unittest_main()


// --------
