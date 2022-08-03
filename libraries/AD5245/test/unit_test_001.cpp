//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for I2C digital PotentioMeter AD5241 AD5242
//          https://github.com/RobTillaart/AD524X
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

#include "AD5245.h"


unittest_setup()
{
  fprintf(stderr, "\nAD5245_LIB_VERSION %s\n", (char*) AD5245_LIB_VERSION);
}


unittest_teardown()
{
}

unittest(test_constants)
{
  assertEqual(000, AD5245_OK);
  assertEqual(100, AD5245_ERROR);
}


unittest(test_constructors)
{
  Wire.begin();

  AD5245 AD(0x2C);
  AD.begin();
  assertEqual(128, AD.read());
}


unittest(test_reset)
{
  Wire.begin();
  AD5245 AD(0x2C);

  assertEqual(128, AD.read());

  AD.write(0);
  assertEqual(0, AD.read());

  AD.reset();
  assertEqual(128, AD.read());
}


unittest(test_write_read)
{
  Wire.begin();
  AD5245 AD(0x2C);

  assertEqual(128, AD.read());

  AD.write(42);
  assertEqual(42, AD.read());
}


unittest_main()

// --------
