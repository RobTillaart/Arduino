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


unittest(test_constants)
{
  assertEqualFloat(PI / 180.0, DEG_TO_RAD, 0.00001);
  assertEqualFloat(180.0 / PI, RAD_TO_DEG, 0.00001);
  assertEqualFloat(PI / 200.0, GRAD_TO_RAD, 0.00001);
  assertEqualFloat(200.0 / PI, RAD_TO_GRAD, 0.00001);
}


unittest(test_constructor)
{
  fprintf(stderr, "AVERAGE_ANGLE_LIB_VERSION: %s\n", (char*) AVERAGE_ANGLE_LIB_VERSION);

  AverageAngle dd(AverageAngle::DEGREES);
  AverageAngle rr(AverageAngle::RADIANS);
  AverageAngle gg(AverageAngle::GRADIANS);

  assertEqual(AverageAngle::DEGREES, dd.type());
  assertEqual(AverageAngle::RADIANS, rr.type());
  assertEqual(AverageAngle::GRADIANS, gg.type());
}


unittest(test_degrees)
{
  fprintf(stderr, "AVERAGE_ANGLE_LIB_VERSION: %s\n", (char*) AVERAGE_ANGLE_LIB_VERSION);

  AverageAngle aa(AverageAngle::DEGREES);

  for (int i = 0; i < 10; i++)
  {
    int n = aa.add(i);
    assertEqual(i + 1, n);
  }
  fprintf(stderr, "%f\n", aa.getAverage());
  fprintf(stderr, "%f\n", aa.getTotalLength());
  fprintf(stderr, "%f\n", aa.getAverageLength());

  assertEqual(10,  aa.count());
  assertEqualFloat(4.5, aa.getAverage(), 0.001);
  assertEqualFloat(9.987438, aa.getTotalLength(), 0.001);
  assertEqualFloat(0.9987438, aa.getAverageLength(), 0.001);
}


unittest(test_radians)
{
  fprintf(stderr, "AVERAGE_ANGLE_LIB_VERSION: %s\n", (char*) AVERAGE_ANGLE_LIB_VERSION);

  AverageAngle aa(AverageAngle::RADIANS);

  for (int i = 0; i < 10; i++)
  {
    int n = aa.add(i);
    assertEqual(i + 1, n);
  }
  fprintf(stderr, "%f\n", aa.getAverage());
  fprintf(stderr, "%f\n", aa.getTotalLength());
  fprintf(stderr, "%f\n", aa.getAverageLength());

  assertEqual(10,  aa.count());
  assertEqualFloat(1.35841, aa.getAverage(), 0.001);
  assertEqualFloat(2.000152, aa.getTotalLength(), 0.001);
  assertEqualFloat(0.2000152, aa.getAverageLength(), 0.001);
}


unittest(test_gradians)
{
  fprintf(stderr, "AVERAGE_ANGLE_LIB_VERSION: %s\n", (char*) AVERAGE_ANGLE_LIB_VERSION);

  AverageAngle aa(AverageAngle::GRADIANS);

  for (int i = 0; i < 10; i++)
  {
    int n = aa.add(i);
    assertEqual(i + 1, n);
  }
  fprintf(stderr, "%f\n", aa.getAverage());
  fprintf(stderr, "%f\n", aa.getTotalLength());
  fprintf(stderr, "%f\n", aa.getAverageLength());

  assertEqual(10,  aa.count());
  assertEqualFloat(4.5, aa.getAverage(), 0.001);
  assertEqualFloat(9.98982, aa.getTotalLength(), 0.001);
  assertEqualFloat(0.998982, aa.getAverageLength(), 0.001);
}


unittest_main()

// --------
