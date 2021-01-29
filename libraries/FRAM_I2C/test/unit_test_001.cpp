//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-23
// PURPOSE: unit tests for the FRAM library
//          https://github.com/RobTillaart/FRAM_I2C
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "FRAM.h"



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
  fprintf(stderr, "VERSION: %s\n", FRAM_LIB_VERSION);
  FRAM fram49;
  FRAM fram50;
  FRAM fram52;
  FRAM fram57;

  Wire.begin();

  fprintf(stderr, "\ndifferent constructors\n");
  assertEqual(FRAM_ERROR_ADDR, fram49.begin(0x49));
  assertEqual(FRAM_OK, fram50.begin());
  assertEqual(FRAM_OK, fram52.begin(0x52));
  assertEqual(FRAM_OK, fram57.begin(0x57, 4));

  fprintf(stderr, "\nno writeProtect pin defined\n");
  assertFalse(fram50.setWriteProtect(true));
  assertFalse(fram50.getWriteProtect());
  assertFalse(fram50.setWriteProtect(false));
  assertFalse(fram50.getWriteProtect());

  fprintf(stderr, "\nwriteProtect pin defined\n");
  assertTrue(fram57.setWriteProtect(true));
  assertTrue(fram57.getWriteProtect());
  assertTrue(fram57.setWriteProtect(false));
  assertFalse(fram57.getWriteProtect());

  fprintf(stderr, "\nall fail as nothing connected\n");
  assertEqual(65535, fram50.getManufacturerID());
  assertEqual(65535, fram50.getProductID());
  assertEqual(0, fram50.getSize());
}

unittest_main()

// --------
