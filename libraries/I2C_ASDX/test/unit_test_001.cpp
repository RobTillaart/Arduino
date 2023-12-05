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
  fprintf(stderr, "I2C_ASDX_VERSION: %s\n", (char *) I2C_ASDX_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  I2C_ASDX sensor(0x58, 100);

  assertEqual(I2C_ASDX_INIT, sensor.state());

  Wire.begin();
  assertTrue(sensor.begin());
  assertTrue(sensor.isConnected());    //  incorrect, keep build happy

  fprintf(stderr, "test state\n");
  assertEqual(0, sensor.errorCount());
  assertEqual(0, sensor.lastRead());
  assertEqual(I2C_ASDX_OK, sensor.state());
}


unittest(test_constants)
{
  fprintf(stderr, "Test conversion constants\n");
  assertEqualFloat(68.9475729,    PSI2MILLIBAR,    1e-4);
  assertEqualFloat(0.01450377377, MILLIBAR2PSI,    1e-4);
  assertEqualFloat(0.0689475729,  PSI2BAR,         1e-4);
  assertEqualFloat(14.503773773,  BAR2PSI,         1e-4);

  assertEqualFloat(0.001,         MILLIBAR2BAR,    1e-7);
  assertEqualFloat(9.872e-4,      MILLIBAR2ATM,    1e-7);
  assertEqualFloat(1000,          MILLIBAR2DYNES,  1);
  assertEqualFloat(2.9539e-2,     MILLIBAR2INHG,   1e-5);

  assertEqualFloat(0.4018,        MILLIBAR2INH2O,  1e-4);
  assertEqualFloat(100,           MILLIBAR2PASCAL, 1e-3);
  assertEqualFloat(0.75028,       MILLIBAR2TORR,   1e-5);
  assertEqualFloat(0.075028,      MILLIBAR2CMHG,   1e-6);

  assertEqualFloat(1.02056,       MILLIBAR2CMH2O,  1e-5);
  assertEqualFloat(100,           MILLIBAR2MSW,    1);

  fprintf(stderr, "Test state constants\n");
  assertEqual(1,  I2C_ASDX_OK);
  assertEqual(0,  I2C_ASDX_INIT);
  assertEqual(-1, I2C_ASDX_READ_ERROR);
  assertEqual(-2, I2C_ASDX_C000_ERROR);
  assertEqual(-3, I2C_ASDX_CONNECT_ERROR);
}


unittest(test_read_zero)
{
  I2C_ASDX sensor(0x58, 100);

  Wire.begin();
  assertTrue(sensor.begin());
  assertTrue(sensor.isConnected());  //  incorrect, keep build happy

  fprintf(stderr, "Test default pressure\n");
  assertEqual(0, sensor.getPressure());
  assertEqual(0, sensor.getMilliBar());
  assertEqual(0, sensor.getBar());
  assertEqual(0, sensor.getPSI());

  assertEqual(0, sensor.getATM());
  assertEqual(0, sensor.getDynes());
  assertEqual(0, sensor.getInchHg());
  assertEqual(0, sensor.getInchH2O());
  assertEqual(0, sensor.getPascal());
  assertEqual(0, sensor.getTORR());
  assertEqual(0, sensor.getCmHg());
  assertEqual(0, sensor.getCmH2O());
  assertEqual(0, sensor.getMSW());

  // assertEqual(I2C_ASDX_READ_ERROR, sensor.read());

  // fprintf(stderr, "Test after read\n");
  // assertEqual(0, sensor.getPressure());
  // assertEqual(0, sensor.getMilliBar());
  // assertEqual(0, sensor.getBar());
  // assertEqual(0, sensor.getPSI());
}


unittest_main()


//  -- END OF FILE --

