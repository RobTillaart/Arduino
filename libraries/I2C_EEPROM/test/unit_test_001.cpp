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
  Wire.begin();
  I2C_eeprom EE(0x50, 0x8000);

  assertTrue(EE.begin());
  assertTrue(EE.isConnected());

  assertEqual(0, EE.getLastWrite());
  assertEqual(64, EE.getPageSize());
}


unittest(test_constants)
{
  Wire.resetMocks();
  Wire.begin();
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
  Wire.resetMocks();
  Wire.begin();
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

  I2C_eeprom prom(0x50, 0x8123);
  assertEqual(prom.getDeviceSize(), 0x8000);
  assertEqual(prom.getPageSize(),   64);
}


unittest(test_setDeviceSize)
{
  Wire.resetMocks();
  Wire.begin();
  I2C_eeprom EE(0x50, 0x8000);

  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC512), I2C_DEVICESIZE_24LC512);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC256), I2C_DEVICESIZE_24LC256);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC128), I2C_DEVICESIZE_24LC128);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC64),  I2C_DEVICESIZE_24LC64);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC32),  I2C_DEVICESIZE_24LC32);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC16),  I2C_DEVICESIZE_24LC16);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC08),  I2C_DEVICESIZE_24LC08);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC04),  I2C_DEVICESIZE_24LC04);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC02),  I2C_DEVICESIZE_24LC02);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC01),  I2C_DEVICESIZE_24LC01);

  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC512 + 1), I2C_DEVICESIZE_24LC512);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC256 + 1), I2C_DEVICESIZE_24LC256);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC128 + 1), I2C_DEVICESIZE_24LC128);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC64 + 1),  I2C_DEVICESIZE_24LC64);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC32 + 1),  I2C_DEVICESIZE_24LC32);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC16 + 1),  I2C_DEVICESIZE_24LC16);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC08 + 1),  I2C_DEVICESIZE_24LC08);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC04 + 1),  I2C_DEVICESIZE_24LC04);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC02 + 1),  I2C_DEVICESIZE_24LC02);
  assertEqual(EE.setDeviceSize(I2C_DEVICESIZE_24LC01 + 1),  I2C_DEVICESIZE_24LC01);

}


unittest(test_setPageSize)
{
  Wire.resetMocks();
  Wire.begin();
  I2C_eeprom EE(0x50, 0x8000);

  assertEqual(EE.setPageSize(129), 128);
  assertEqual(EE.setPageSize(128), 128);
  assertEqual(EE.setPageSize(127), 64);
  assertEqual(EE.setPageSize(65),  64);
  assertEqual(EE.setPageSize(64),  64);
  assertEqual(EE.setPageSize(63),  32);
  assertEqual(EE.setPageSize(33),  32);
  assertEqual(EE.setPageSize(32),  32);
  assertEqual(EE.setPageSize(31),  16);
  assertEqual(EE.setPageSize(17),  16);
  assertEqual(EE.setPageSize(16),  16);
  assertEqual(EE.setPageSize(9),   8);
  assertEqual(EE.setPageSize(8),   8);
}


unittest_main()


//  -- END OF FILE --

