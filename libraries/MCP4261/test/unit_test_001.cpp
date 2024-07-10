//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-01
// PURPOSE: unit tests for the A1301 magnetic sensor
//     URL: https://github.com/RobTillaart/A1301
//          https://www.adafruit.com/product/2857
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
#include "MCP4261.h"


unittest_setup()
{
    fprintf(stderr, "MCP4261_LIB_VERSION: %s\n", (char *) MCP4261_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(64,  MCP41XX_MIDDLE_VALUE);
  assertEqual(128, MCP41XX_MAX_VALUE);
  assertEqual(128, MCP42XX_MIDDLE_VALUE);
  assertEqual(256, MCP42XX_MAX_VALUE);
}


unittest(test_constructor)
{
  MCP4261 mcp(10, 6);
  //  before begin.
  assertEqual(2, mcp.pmCount());
  assertEqual(0, mcp.getValue());

}


/*
  TODO
  setValue false test
  setValue, getValue
  incrValue
  decrValue
*/

unittest_main()


//  -- END OF FILE --

