//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-07
// PURPOSE: unit tests for the runningAngle library
//          https://github.com/RobTillaart/runningAngle
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

#include "runningAngle.h"


unittest_setup()
{
  fprintf(stderr, "RUNNING_ANGLE_LIB_VERSION: %s\n", (char *) RUNNING_ANGLE_LIB_VERSION );
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(0.800, RA_DEFAULT_WEIGHT, 0.0001);
  assertEqualFloat(0.001, RA_MIN_WEIGHT,     0.0001);
  assertEqualFloat(1.000, RA_MAX_WEIGHT,     0.0001);
}


unittest(test_constructor_1)
{
  runningAngle heading(runningAngle::DEGREES);
  assertEqualFloat(0.80, heading.getWeight(),  0.0001);
  assertEqualFloat(0.00, heading.getAverage(), 0.0001);
}


unittest(test_constructor_2)
{
  runningAngle heading(runningAngle::RADIANS);
  assertEqualFloat(0.80, heading.getWeight(),  0.0001);
  assertEqualFloat(0.00, heading.getAverage(), 0.0001);
}


unittest(test_constructor_3)
{
  runningAngle heading(runningAngle::GRADIANS);
  assertEqualFloat(0.80, heading.getWeight(),  0.0001);
  assertEqualFloat(0.00, heading.getAverage(), 0.0001);
}


unittest(test_getAverage)
{
  runningAngle heading(runningAngle::DEGREES);

  for (int angle = 0; angle < 10; angle++)
  {
    heading.add(angle);
    fprintf(stderr, "%d\t%f\n", angle, heading.getAverage());
  }
  assertEqualFloat(8.750000, heading.getAverage(), 0.0001);
  fprintf(stderr, "\treset()\n");
  heading.reset();
  assertEqualFloat(0, heading.getAverage(), 0.0001);
}


unittest(test_weight)
{
  runningAngle heading(runningAngle::DEGREES);
  assertEqualFloat(0.80, heading.getWeight(), 0.0001);

  assertTrue(heading.setWeight(0.85));
  assertEqualFloat(0.85, heading.getWeight(), 0.0001);

  assertFalse(heading.setWeight(2));
  assertEqualFloat(1, heading.getWeight(), 0.0001);

  assertFalse(heading.setWeight(-5));
  assertEqualFloat(0.001, heading.getWeight(), 0.0001);

  assertTrue(heading.setWeight());    // use default
  assertEqualFloat(0.80, heading.getWeight(), 0.0001);

  fprintf(stderr, "\treset()\n");
  heading.reset();
  assertEqualFloat(0.80, heading.getWeight(), 0.0001);
}


unittest(test_wrap)
{
  runningAngle heading(runningAngle::DEGREES);

  heading.setMode0();

  assertEqualFloat(0, heading.wrap(0), 0.0001);
  assertEqualFloat(0, heading.wrap(360), 0.0001);
  assertEqualFloat(1, heading.wrap(361), 0.0001);
  assertEqualFloat(179, heading.wrap(179), 0.0001);
  assertEqualFloat(-180, heading.wrap(180), 0.0001);
  assertEqualFloat(-179, heading.wrap(181), 0.0001);
  assertEqualFloat(-179, heading.wrap(-179), 0.0001);
  assertEqualFloat(-180, heading.wrap(-180), 0.0001);
  assertEqualFloat(179, heading.wrap(-181), 0.0001);
  assertEqualFloat(1, heading.wrap(721), 0.0001);
  assertEqualFloat(-1, heading.wrap(-1), 0.0001);
  assertEqualFloat(-1, heading.wrap(-361), 0.0001);
  assertEqualFloat(-1, heading.wrap(-721), 0.0001);
}


unittest(test_mode_0)
{
  runningAngle heading(runningAngle::DEGREES);

  for (int i = 0; i < 360; i+= 20)
  {
    heading.reset();
    heading.setMode0();
    if (i < 180) assertEqualFloat(i, heading.add(i), 0.0001);
    else         assertEqualFloat(i-360, heading.add(i), 0.0001);
  }
}


unittest(test_mode_1)
{
  runningAngle heading(runningAngle::DEGREES);

  for (int i = 0; i < 360; i+= 20)
  {
    heading.reset();
    heading.setMode1();
    assertEqualFloat(i, heading.add(i), 0.0001);
  }
}


unittest_main()


//  -- END OF FILE --

