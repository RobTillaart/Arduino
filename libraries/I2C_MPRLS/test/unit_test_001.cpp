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
#include "I2C_MPRLS.h"


unittest_setup()
{
  fprintf(stderr, "I2C_MPRLS_LIB_VERSION: %s\n", (char *) I2C_MPRLS_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  I2C_MPRLS sensor(0x58);

  assertEqual(I2C_MPRLS_INIT, sensor.getLastError());

  Wire.begin();
  assertTrue(sensor.begin(16, 0));
  assertTrue(sensor.isConnected());    //  incorrect, keep build happy

  fprintf(stderr, "test state\n");
  assertEqual(0, sensor.errorCount());
  assertEqual(0, sensor.lastRead());
  assertEqual(I2C_MPRLS_OK, sensor.getLastError());
}


unittest(test_constants)
{
  fprintf(stderr, "Test state constants\n");
  assertEqual(1,  I2C_MPRLS_OK);
  assertEqual(0,  I2C_MPRLS_INIT);
  assertEqual(-1, I2C_MPRLS_READ_ERROR);
  assertEqual(-2, I2C_MPRLS_WRITE_ERROR);
  assertEqual(-3, I2C_MPRLS_CONNECT_ERROR);
}


unittest(test_read_zero)
{
  I2C_MPRLS sensor(0x58);

  Wire.begin();
  assertTrue(sensor.begin(25));
  assertTrue(sensor.isConnected());  //  incorrect, keep build happy

  fprintf(stderr, "Test default pressure\n");
  assertEqualFloat(0, sensor.getPressure(), 0.01);
}


unittest_main()


//  -- END OF FILE --

