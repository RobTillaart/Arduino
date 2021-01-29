//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the AverageAngle class
//          https://github.com/RobTillaart/AverageAngle
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)

#include <ArduinoUnitTests.h>

#include "AverageAngle.h"


unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_constructor)
{
  AverageAngle dd(AverageAngle::DEGREES);
  AverageAngle rr(AverageAngle::RADIANS);
  
  assertEqual(AverageAngle::DEGREES, dd.type());
  assertEqual(AverageAngle::RADIANS, rr.type());
}

unittest(test_degrees)
{
  AverageAngle aa(AverageAngle::DEGREES);

  for (int i = 0; i < 10; i++)
  {
    int n = aa.add(i);
    assertEqual(i + 1, n);
  }
  assertEqual(10,  aa.count());
  assertEqual(4.5, aa.getAverage());

  fprintf(stderr, "getTotalLength()\n");
  float diff = abs(10 - aa.getTotalLength());
  assertMoreOrEqual(0.2, diff);
  
  fprintf(stderr, "getAverageLength()\n");
  diff = abs(1 - aa.getAverageLength());
  assertMoreOrEqual(0.01, diff);
}

unittest_main()

// --------
