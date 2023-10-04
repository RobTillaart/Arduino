//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the I2C mcp9808 temperature sensor
//          https://github.com/RobTillaart/MCP9808_RT
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)


#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "mcp9808.h"


unittest_setup()
{
  fprintf(stderr, "MCP9808_LIB_VERSION: %s\n", (char *) MCP9808_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MCP9808_THYSTERESIS , 0x0600);
  assertEqual(MCP9808_SHUTDOWN    , 0x0100);
  assertEqual(MCP9808_CRIT_LOCK   , 0x0080);
  assertEqual(MCP9808_WIN_LOCK    , 0x0040);
  assertEqual(MCP9808_INT_CLEAR   , 0x0020);
  assertEqual(MCP9808_ALERT_STATUS, 0x0010);
  assertEqual(MCP9808_ALERT_CTRL  , 0x0008);
  assertEqual(MCP9808_ALERT_SELECT, 0x0004);
  assertEqual(MCP9808_ALERT_POLAR , 0x0002);
  assertEqual(MCP9808_ALERT_MODE  , 0x0001);
}


//  TODO more can be tested if there is a Godmode->Wire stub
unittest(test_constructor)
{
  MCP9808 ts(24, &Wire);
  // assertTrue(ts.isConnected());
  assertEqual(1,1);
}


unittest(test_offset)
{
  MCP9808 ts(24);
  for (int i = -10; i < 10; i++)
  {
    ts.setOffset(i * 0.1);
    fprintf(stderr, "%f\t", i * 0.1);
    assertEqualFloat(i * 0.1, ts.getOffset(), 0.0001);
  }
}


unittest_main()


//  -- END OF FILE --

