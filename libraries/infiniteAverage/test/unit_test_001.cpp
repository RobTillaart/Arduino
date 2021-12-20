//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-28
// PURPOSE: unit tests for the infiniteAverage
//          https://github.com/RobTillaart/infiniteAverage
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


#include "infiniteAverage.h"


unittest_setup()
{
  fprintf(stderr, "IAVG_LIB_VERSION: %s\n", (char *) IAVG_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  IAVG iavg;
  
  assertEqual(0, iavg.count());
  assertEqual(0, iavg.whole());
  assertEqualFloat(0, iavg.decimals(), 0.0001);
}


unittest(test_add)
{
  IAVG iavg;

  iavg.add(10000000);
  assertEqual(1, iavg.count());
  assertEqual(10000000, iavg.whole());
  assertEqualFloat(0, iavg.decimals(), 0.0001);
  assertEqualFloat(10000000, iavg.average(), 0.0001);

  iavg.add(1);
  assertEqual(2, iavg.count());
  assertEqual(10000001, iavg.whole());
  assertEqualFloat(0, iavg.decimals(), 0.0001);
  assertEqualFloat(5000000.5, iavg.average(), 0.5);  // as output is just a float ...
}


unittest(test_threshold)
{
  IAVG iavg;

  iavg.reset();
  for (int i = 0; i < 1000; i++)
  {
    iavg.add(1.0 * i);
  }
  fprintf(stderr, "%d \t%d \t%f\n", iavg.count(), iavg.whole(), iavg.average());


  // shows the effects of (relative) small thresholds with non-uniform data
  for (uint32_t th = 100000; th < 1000000; th += 100000)
  {
    iavg.reset();
    iavg.setDivideThreshold(th);
    for (int i = 0; i < 1000; i++)
    {
      iavg.add(1.0 * i);
    }
    fprintf(stderr, "%3d  %d \t%d \t%f\n", th, iavg.count(), iavg.whole(), iavg.average());
  }
}


unittest_main()


// --------
