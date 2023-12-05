//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-10-06
// PURPOSE: unit tests for the CHT8305 temperature and humidity sensor
//          https://github.com/RobTillaart/CHT8305
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


unittest_setup()
{
  fprintf(stderr, "CHT8305_LIB_VERSION: %s\n", (char *) CHT8305_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_I)
{
  assertEqual(0x40, CHT8305_DEFAULT_ADDRESS);

  assertEqual(0,    CHT8305_OK);
  assertEqual(-10,  CHT8305_ERROR_ADDR);
  assertEqual(-11,  CHT8305_ERROR_I2C);
  assertEqual(-12,  CHT8305_ERROR_CONNECT);
  assertEqual(-20,  CHT8305_ERROR_LASTREAD);
}


unittest(test_constants_II)
{
  assertEqual(0x00, CHT8305_REG_TEMPERATURE);
  assertEqual(0x01, CHT8305_REG_HUMIDITY);
  assertEqual(0x02, CHT8305_REG_CONFIG);
  assertEqual(0x03, CHT8305_REG_ALERT);
  assertEqual(0x04, CHT8305_REG_VOLTAGE);
  assertEqual(0xFE, CHT8305_REG_MANUFACTURER);
  assertEqual(0xFF, CHT8305_REG_VERSION);
}


unittest(test_constants_III)
{
  assertEqual(0x8000, CHT8305_CFG_SOFT_RESET);
  assertEqual(0x4000, CHT8305_CFG_CLOCK_STRETCH);
  assertEqual(0x2000, CHT8305_CFG_HEATER);
  assertEqual(0x1000, CHT8305_CFG_MODE);
  assertEqual(0x0800, CHT8305_CFG_VCCS);
  assertEqual(0x0400, CHT8305_CFG_TEMP_RES);
  assertEqual(0x0300, CHT8305_CFG_HUMI_RES);
  assertEqual(0x00C0, CHT8305_CFG_ALERT_MODE);
  assertEqual(0x0020, CHT8305_CFG_ALERT_PENDING);
  assertEqual(0x0010, CHT8305_CFG_ALERT_HUMI);
  assertEqual(0x0008, CHT8305_CFG_ALERT_TEMP);
  assertEqual(0x0004, CHT8305_CFG_VCC_ENABLE);
  assertEqual(0x0003, CHT8305_CFG_VCC_RESERVED);
}


unittest(test_offset)
{
  CHT8305 cht(0x40);

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
  CHT8305 cht;

  Wire.begin();

  assertEqual(0, cht.lastRead());
}


unittest(test_AlertTriggerMode)
{
  CHT8305 cht;

  Wire.begin();

  //  test range check only false can be checked
  for (int mode = 4; mode < 10; mode++)
  {
    assertFalse(cht.setAlertTriggerMode(mode));
  }
  assertFalse(cht.setAlertTriggerMode(-1));
}


unittest(test_setAlertLevels)
{
  CHT8305 cht;

  Wire.begin();

  //  temp range check only false can be checked
  assertFalse(cht.setAlertLevels(-41, 50));
  assertFalse(cht.setAlertLevels(126, 50));
  //  humi range check
  assertFalse(cht.setAlertLevels(50, -1));
  assertFalse(cht.setAlertLevels(50, 101));
  //  both range check
  assertFalse(cht.setAlertLevels(126, -1));
  assertFalse(cht.setAlertLevels(-41, 101));
}


unittest_main()


//  -- END OF FILE --
