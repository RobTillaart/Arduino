//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-01
// PURPOSE: unit tests for the dateTimeHelper functions
//          https://github.com/RobTillaart/dateTimeHelpers
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
#include "dateTimeHelpers.h"


unittest_setup()
{
    fprintf(stderr, "DATETIMEHELPER_LIB_VERSION: %s\n", (char *) DATETIMEHELPER_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(60,     SECONDS_MINUTE);
  assertEqual(3600,   SECONDS_HOUR);
  assertEqual(86400,  SECONDS_DAY);
  assertEqual(604800, SECONDS_WEEK);
}


//  TODO DISPLAY
/*
secondsSplit

seconds2duration
seconds2clock24
seconds2clock12
seconds2clockAMPM

millis2duration
millis2clock
*/




///////////////////////////////////////////////////////////////////////////
//
//  CONVERTORS
//
unittest(test_weeks)
{
  assertEqualFloat(1.653439153439e-6, seconds2weeks(1), 0.001);
  assertEqualFloat(0.5, seconds2weeks(302400), 0.001);
  assertEqualFloat(1.0, seconds2weeks(604800), 0.001);
}


unittest(test_days)
{
  assertEqualFloat(1.157407407407e-5, seconds2days(1), 0.001);
  assertEqualFloat(0.5, seconds2days(43200), 0.001);
  assertEqualFloat(1.0, seconds2days(86400), 0.001);
}


unittest(test_hours)
{
  assertEqualFloat(2.777777777778e-4, seconds2hours(1), 0.001);
  assertEqualFloat(0.5, seconds2hours(1800), 0.001);
  assertEqualFloat(1.0, seconds2hours(3600), 0.001);
}


unittest(test_minutes)
{
  assertEqualFloat(1.666666666667e-2, seconds2minutes(1), 0.001);
  assertEqualFloat(0.5, seconds2minutes(30), 0.001);
  assertEqualFloat(1.0, seconds2minutes(60), 0.001);
}



unittest_main()


//  -- END OF FILE --

