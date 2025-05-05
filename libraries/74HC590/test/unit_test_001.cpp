//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-04-30
// PURPOSE: unit tests for the 74HC590 library
//     URL: https://github.com/RobTillaart/74HC590
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
#include "74HC590.h"


unittest_setup()
{
  fprintf(stderr, "LIB_74HC590_VERSION: %s\n", (char *) LIB_74HC590_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


unittest(test_constructor)
{
  #define OE        4
  #define CCLR      5
  #define CCKEN     6
  #define CCLK      7
  #define RCLK      8
  #define RCO       9

  DEV_74HC590 count0(OE, CCLR, CCKEN, CCLK, RCLK, RCO);
  DEV_74HC590 count1(OE, CCLR, CCKEN, CCLK, RCLK);
  DEV_74HC590 count2(OE, CCLR, CCKEN, CCLK);

  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --

