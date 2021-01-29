//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the I2C_ASDX pressure sensor library
//          https://github.com/RobTillaart/I2C_ASDX
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
#include "I2C_ASDX.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", I2C_ASDX_VERSION);

  I2C_ASDX sensor(0x58, 100);
  sensor.begin();
  assertTrue(sensor.available());

  fprintf(stderr, "Test default pressure\n");

  assertEqual(0, sensor.getPressure());
  assertEqual(0, sensor.getMilliBar());
  assertEqual(0, sensor.getBar());
  assertEqual(0, sensor.getPSI());

  fprintf(stderr, "tes state\n");
  assertEqual(0, sensor.errorCount());
  assertEqual(0, sensor.lastRead());
  assertEqual(I2C_ASDX_INIT, sensor.state());

  fprintf(stderr, "Test conversion constants\n");
  assertEqualFloat(68.9475729, PSI2MILLIBAR, 0.0001);
  assertEqualFloat(0.01450377377, MILLIBAR2PSI, 0.0001);
  assertEqualFloat(0.0689475729, PSI2BAR, 0.0001);
  assertEqualFloat(14.503773773, BAR2PSI, 0.0001);
}


unittest(test_read)
{
  fprintf(stderr, "VERSION: %s\n", I2C_ASDX_VERSION);

  I2C_ASDX sensor(0x58, 100);
  sensor.begin();
  assertTrue(sensor.available());

  fprintf(stderr, "Test default pressure\n");
  assertEqual(0, sensor.getPressure());
  assertEqual(0, sensor.getMilliBar());
  assertEqual(0, sensor.getBar());
  assertEqual(0, sensor.getPSI());

  // assertEqual(I2C_ASDX_READ_ERROR, sensor.read());

  // fprintf(stderr, "Test after read\n");
  // assertEqual(0, sensor.getPressure());
  // assertEqual(0, sensor.getMilliBar());
  // assertEqual(0, sensor.getBar());
  // assertEqual(0, sensor.getPSI());
}


unittest_main()

// --------
