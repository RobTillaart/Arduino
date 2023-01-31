//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-12-03
// PURPOSE: unit tests for the Angle library
//          https://github.com/RobTillaart/AngleConvertor
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
#include "AngleConvertor.h"


unittest_setup()
{
  fprintf(stderr, "ANGLECONVERTOR_LIB_VERSION: %s\n", (char *) ANGLECONVERTOR_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_conversions)
{
  AngleConvertor conv;

  conv.setDegrees(1.0);
  assertEqualFloat(1.0, conv. getDegrees(), 0.00001);

  conv.setRadians(1.0);
  assertEqualFloat(1.0, conv. getRadians(), 0.00001);

  conv.setGradians(1.0);
  assertEqualFloat(1.0, conv. getGradians(), 0.00001);

  conv.setAngularMil(1.0);
  assertEqualFloat(1.0, conv. getAngularMil(), 0.00001);

  conv.setBinaryRadians(1.0);
  assertEqualFloat(1.0, conv. getBinaryRadians(), 0.00001);

  conv.setCentiTurn(1.0);
  assertEqualFloat(1.0, conv. getCentiTurn(), 0.00001);

  conv.setDiameterPart(1.0);
  assertEqualFloat(1.0, conv. getDiameterPart(), 0.00001);

  conv.setHexacontade(1.0);
  assertEqualFloat(1.0, conv. getHexacontade(), 0.00001);

  conv.setHourAngle(1.0);
  assertEqualFloat(1.0, conv. getHourAngle(), 0.00001);

  conv.setMilliTurn(1.0);
  assertEqualFloat(1.0, conv. getMilliTurn(), 0.00001);

  conv.setMinuteTime(1.0);
  assertEqualFloat(1.0, conv. getMinuteTime(), 0.00001);

  conv.setOctant(1.0);
  assertEqualFloat(1.0, conv. getOctant(), 0.00001);

  conv.setPechus(1.0);
  assertEqualFloat(1.0, conv. getPechus(), 0.00001);

  conv.setPoints(1.0);
  assertEqualFloat(1.0, conv. getPoints(), 0.00001);

  conv.setQuadrant(1.0);
  assertEqualFloat(1.0, conv. getQuadrant(), 0.00001);

  conv.setQuarterPoint(1.0);
  assertEqualFloat(1.0, conv. getQuarterPoint(), 0.00001);

  conv.setSecondsTime(1.0);
  assertEqualFloat(1.0, conv. getSecondsTime(), 0.00001);

  conv.setSextant(1.0);
  assertEqualFloat(1.0, conv. getSextant(), 0.00001);

  conv.setSign(1.0);
  assertEqualFloat(1.0, conv. getSign(), 0.00001);

  conv.setTurn(1.0);
  assertEqualFloat(1.0, conv. getTurn(), 0.00001);
}


unittest_main()


//  -- END OF FILE --

