//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-10-06
// PURPOSE: unit tests for the CHT8305 temperature and humidity sensor
//          https://github.com/RobTillaart/CH8305
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

#include "Arduino.h"
#include "CHT8305.h"

#define A0      0


unittest_setup()
{
  fprintf(stderr, "CHT8305_LIB_VERSION: %s\n", (char *) CHT8305_LIB_VERSION);
}

unittest_teardown()
{
}

#define CHT8305_OK                       0
#define CHT8305_ERROR_ADDR               -10
#define CHT8305_ERROR_I2C                -11
#define CHT8305_ERROR_CONNECT            -12

#define CHT8305_ERROR_LASTREAD           -20



unittest(test_constants)
{
  assertEqual(0,   CHT8305_OK);
  assertEqual(-10, CHT8305_ERROR_ADDR);
  assertEqual(-11, CHT8305_ERROR_I2C);
  assertEqual(-12, CHT8305_ERROR_CONNECT);
  assertEqual(-20, CHT8305_ERROR_LASTREAD);
}


unittest(test_offset)
{
  CHT8305 cht;

  //  default hum = 0
  assertEqualFloat(0.0, cht.getHumOffset(), 0.01);
  cht.setHumOffset(12.34);
  assertEqualFloat(12.34, cht.getHumOffset(), 0.01);
  cht.setHumOffset(0.0);
  assertEqualFloat(0.0, cht.getHumOffset(), 0.01);

  //  default temp = 0
  assertEqualFloat(0.0, cht.getTempOffset(), 0.01);
  cht.setTempOffset(12.34);
  assertEqualFloat(12.34, cht.getTempOffset(), 0.01);
  cht.setTempOffset(0.0);
  assertEqualFloat(0.0, cht.getTempOffset(), 0.01);
}




unittest_main()


// -- END OF FILE --
