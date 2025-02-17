//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-17
// PURPOSE: unit tests for the PCF85263 RTC library
//     URL: https://github.com/RobTillaart/PCF85263
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
#include "PCF85263.h"


unittest_setup()
{
  fprintf(stderr, "PCF85263_LIB_VERSION: %s\n", (char *) PCF85263_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PCF85263_DEFAULT_ADDRESS, 0x51);

  //  error codes
  assertEqual(PCF85263_OK           , 0  );
  assertEqual(PCF85263_ERROR_ADDR   , -10);
  assertEqual(PCF85263_ERROR_I2C    , -11);
  assertEqual(PCF85263_ERROR_CONNECT, -12);
}


unittest(test_constructor)
{
  PCF85263 rtc;

  assertEqual(rtc.getAddress(), PCF85263_DEFAULT_ADDRESS);
  assertEqual(rtc.lastRead(), 0);
}


unittest_main()


//  -- END OF FILE --

