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

#include "DS3232.h"


unittest_setup()
{
  fprintf(stderr, "DS3232_LIB_VERSION: %s\n", (char *) DS3232_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0,   DS3232_OK);
  assertEqual(-10, DS3232_ERROR_ADDR);
  assertEqual(-11, DS3232_ERROR_I2C);
  assertEqual(-12, DS3232_ERROR_CONNECT);
}


unittest(test_registers)
{
  assertEqual(0x00, DS3232_SECONDS);
  assertEqual(0x07, DS3232_ALARM1);
  assertEqual(0x0B, DS3232_ALARM2);
  assertEqual(0x0E, DS3232_CONTROL);
  assertEqual(0x10, DS3232_AGING_OFFSET);
  assertEqual(0x11, DS3232_TEMPERATURE);
  assertEqual(0x14, DS3232_SRAM_BASE);
}


unittest(test_getType_getAddress)
{
  DS3231 rtc1;
  DS3232 rtc2;

  assertEqual(3231, rtc1.getType());
  assertEqual(3232, rtc2.getType());

  assertEqual(0x68, rtc1.getAddress());
  assertEqual(0x68, rtc2.getAddress());
}


unittest(test_getters_setters)
{
  DS3232 rtc;

  assertEqual(0, rtc.seconds());
  assertEqual(0, rtc.minutes());
  assertEqual(0, rtc.hours());
  assertEqual(0, rtc.weekDay());
  assertEqual(0, rtc.day());
  assertEqual(0, rtc.month());
  assertEqual(0, rtc.year());

  rtc.setSeconds(1);
  rtc.setMinutes(2);
  rtc.setHours(3);
  rtc.setDay(4);
  rtc.setMonth(5);
  rtc.setYear(6);

  assertEqual(1, rtc.seconds());
  assertEqual(2, rtc.minutes());
  assertEqual(3, rtc.hours());
  assertEqual(0, rtc.weekDay());
  assertEqual(4, rtc.day());
  assertEqual(5, rtc.month());
  assertEqual(6, rtc.year());
}


unittest_main()


//  -- END OF FILE --
