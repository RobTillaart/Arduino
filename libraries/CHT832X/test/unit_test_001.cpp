//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-04
// PURPOSE: unit tests for the CHT832X temperature and humidity sensor
//          https://github.com/RobTillaart/CHT832X
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

#include "CHT832X.h"


unittest_setup()
{
  fprintf(stderr, "CHT832X_LIB_VERSION: %s\n", (char *) CHT832X_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_I)
{
  assertEqual(0x44, CHT832X_DEFAULT_ADDRESS);

  assertEqual(0,    CHT832X_OK);
  assertEqual(-10,  CHT832X_ERROR_ADDR);
  assertEqual(-11,  CHT832X_ERROR_I2C);
  assertEqual(-12,  CHT832X_ERROR_CONNECT);
  assertEqual(-20,  CHT832X_ERROR_LASTREAD);
}


unittest(test_constructor)
{
  CHT832X cht;

  assertEqual(0x44, cht.getAddress());
  assertEqual(0, cht.lastRead());
}


unittest(test_offset)
{
  CHT832X cht;

  Wire.begin();

  //  default hum = 0
  assertEqualFloat(0.0, cht.getHumidityOffset(), 0.01);
  cht.setHumidityOffset(12.34);
  assertEqualFloat(12.34, cht.getHumidityOffset(), 0.01);
  cht.setHumidityOffset(0.0);
  assertEqualFloat(0.0, cht.getHumidityOffset(), 0.01);

  //  default temp = 0
  assertEqualFloat(0.0, cht.getTemperatureOffset(), 0.01);
  cht.setTemperatureOffset(12.34);
  assertEqualFloat(12.34, cht.getTemperatureOffset(), 0.01);
  cht.setTemperatureOffset(0.0);
  assertEqualFloat(0.0, cht.getTemperatureOffset(), 0.01);
}


unittest_main()


//  -- END OF FILE --
