//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-12-02
// PURPOSE: unit tests for the SD2405 RTC
//          https://github.com/RobTillaart/SD2405
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

#include "SD2405.h"


unittest_setup()
{
  fprintf(stderr, "SD2405_LIB_VERSION: %s\n", (char *) SD2405_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0,   SD2405_OK);
  assertEqual(-10, SD2405_ERROR_ADDR);
  assertEqual(-11, SD2405_ERROR_I2C);
  assertEqual(-12, SD2405_ERROR_CONNECT);
}


unittest(test_registers)
{
  assertEqual(0x00, SD2405_TIME_BASE);
  assertEqual(0x07, SD2405_ALARM_BASE);
  assertEqual(0x0E, SD2405_ALARM_ENABLE);
  assertEqual(0x0F, SD2405_CONTROL_1);
  assertEqual(0x10, SD2405_CONTROL_2);
  assertEqual(0x11, SD2405_CONTROL_3);
  assertEqual(0x12, SD2405_TIME_TRIMMING);
  assertEqual(0x13, SD2405_COUNTDOWN);
  assertEqual(0x14, SD2405_SRAM_BASE);
}


unittest(test_getAddress)
{
  SD2405 rtc1;

  assertEqual(0x32, rtc1.getAddress());
}


unittest(test_getters_setters)
{
  SD2405 rtc;

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
