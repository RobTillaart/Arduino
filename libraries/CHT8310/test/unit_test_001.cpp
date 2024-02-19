//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-02-04
// PURPOSE: unit tests for the CHT8310 temperature and humidity sensor
//          https://github.com/RobTillaart/CHT8310
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

#include "CHT8310.h"


unittest_setup()
{
  fprintf(stderr, "CHT8310_LIB_VERSION: %s\n", (char *) CHT8310_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_I)
{
  assertEqual(0x40, CHT8310_DEFAULT_ADDRESS);

  assertEqual(0,    CHT8310_OK);
  assertEqual(-10,  CHT8310_ERROR_ADDR);
  assertEqual(-11,  CHT8310_ERROR_I2C);
  assertEqual(-12,  CHT8310_ERROR_CONNECT);
  assertEqual(-20,  CHT8310_ERROR_LASTREAD);
}


unittest(test_offset)
{
  CHT8310 cht(0x40);

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


unittest(test_lastRead)
{
  CHT8310 cht;

  Wire.begin();

  assertEqual(0, cht.lastRead());
}



unittest_main()


//  -- END OF FILE --
