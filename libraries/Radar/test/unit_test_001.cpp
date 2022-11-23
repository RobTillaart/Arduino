//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-07
// PURPOSE: unit tests for the RADAR class
//          https://github.com/RobTillaart/RADAR
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


#include "radar.h"


unittest_setup()
{
  fprintf(stderr, "RADAR_LIB_VERSION: %s\n", (char *) RADAR_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(10, RADAR_POSITIONS);
}


unittest(test_constructor)
{
  RADAR radar(10, 11);

  assertEqual(10, radar.getMaxPositions());

  radar.setPanPerSecond(100);
  assertEqualFloat(100, radar.getPanPerSecond(), 0.0001);
  radar.setTiltPerSecond(100);
  assertEqualFloat(100, radar.getTiltPerSecond(), 0.0001);
}


unittest(test_positions)
{
  RADAR radar(10, 11);

  assertEqual(10, radar.getMaxPositions());

  for (int pos = 0; pos < 10; pos++)
  {
    fprintf(stderr, "%d\n", pos);
    int16_t x = random(360);
    int16_t y = random(180);
    assertTrue(radar.setPosition(pos, x, y));
    int16_t a, b;
    assertTrue(radar.getPosition(pos, a, b));
    assertEqual(x, a);
    assertEqual(y, b);
  }
}


unittest_main()

// --------
