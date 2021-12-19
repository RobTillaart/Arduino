//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-22
// PURPOSE: unit tests for the I2C_EEPROM library
//          https://github.com/RobTillaart/
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
#include "I2C_eeprom.h"


unittest_setup()
{
  fprintf(stderr, "I2C_EEPROM_VERSION: %s\n", ( char * ) I2C_EEPROM_VERSION);
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
  Wire.resetMocks();

  I2C_eeprom EE(0x50, 0x8000);

  assertTrue(EE.begin());
  assertTrue(EE.isConnected());

  assertEqual(0, EE.getLastWrite());
  assertEqual(64, EE.getPageSize());
}


unittest(test_constants)
{
  I2C_eeprom EE(0x50, 0x8000);

  assertEqual(I2C_DEVICESIZE_24LC512, 65536);
  assertEqual(I2C_DEVICESIZE_24LC256, 32768);
  assertEqual(I2C_DEVICESIZE_24LC128, 16384);
  assertEqual(I2C_DEVICESIZE_24LC64,  8192);
  assertEqual(I2C_DEVICESIZE_24LC32,  4096);
  assertEqual(I2C_DEVICESIZE_24LC16,  2048);
  assertEqual(I2C_DEVICESIZE_24LC08,  1024);
  assertEqual(I2C_DEVICESIZE_24LC04,  512);
  assertEqual(I2C_DEVICESIZE_24LC02,  256);
  assertEqual(I2C_DEVICESIZE_24LC01,  128);

}


unittest(test_getPageSize)
{
  I2C_eeprom EE(0x50, 0x8000);

  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC512), 128);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC256), 64);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC128), 64);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC64),  32);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC32),  32);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC16),  16);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC08),  16);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC04),  16);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC02),  8);
  assertEqual(EE.getPageSize(I2C_DEVICESIZE_24LC01),  8);
}


unittest_main()

// --------
