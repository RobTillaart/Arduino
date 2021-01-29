//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the BH1750FVI_RT (GY-30) lux sensor library
//          https://github.com/RobTillaart/BH1750FVI_RT
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

#include "BH1750FVI.h"


unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_constructor)
{
  BH1750FVI myLux(0x23);

  myLux.setContHigh2Res();
  assertEqual(2, myLux.getMode());
  myLux.setContHighRes();
  assertEqual(1, myLux.getMode());
  myLux.setContLowRes();
  assertEqual(0, myLux.getMode());

  assertFalse(myLux.isReady());

  myLux.setOnceHigh2Res();
  assertEqual(2, myLux.getMode());
  myLux.setOnceHighRes();
  assertEqual(1, myLux.getMode());
  myLux.setOnceLowRes();
  assertEqual(0, myLux.getMode());

  assertFalse(myLux.isReady());
}


unittest(test_read)
{
  BH1750FVI myLux(0x23);

  assertEqual(0, myLux.getError());
  assertEqual(0, myLux.getRaw());
  assertEqual(0, myLux.getLux());
}



unittest(test_parameters)
{
  BH1750FVI myLux(0x23);

  // 0.45 .. 3.68
  fprintf(stderr, "myLux.getCorrectionFactor()\n");
  myLux.setCorrectionFactor(3.14);
  float diff = abs(3.14 - myLux.getCorrectionFactor());
  assertMoreOrEqual(0.01, diff);

  // -89 - 89
  myLux.setAngle(30);
  assertEqual(30, myLux.getAngle());

  // 
  myLux.setTemperature(42);
  assertEqual(42, myLux.getTemperature());

  // 400 - 715
  myLux.setWaveLength(700);
  assertEqual(700, myLux.getWaveLength());
}

unittest_main()

// --------
