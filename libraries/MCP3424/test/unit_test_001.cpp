//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-09-15
// PURPOSE: unit tests for the MCP3424 sensor
//     URL: https://github.com/RobTillaart/MCP3424
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
#include "MCP3424.h"


unittest_setup()
{
  fprintf(stderr, "MCP3424_LIB_VERSION: %s\n", (char *) MCP3424_LIB_VERSION);
  
  Wire.begin();
  //  Wire.setTimeout(10000);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(1, 1, 0.001);
}


unittest(test_constructor)
{
  MCP3424 mcp;

  assertEqual(0, mcp.getChannel());
  assertEqual(4, mcp.getMaxChannels());
  assertEqual(1, mcp.getGain());
  assertEqual(12, mcp.getResolution());
  //  mode
}


unittest(test_gain)
{
  MCP3424 mcp;

  assertEqual(1, mcp.getGain());

  assertTrue(mcp.setGain(2));
  assertEqual(2, mcp.getGain());

  assertTrue(mcp.setGain(4));
  assertEqual(4, mcp.getGain());

  assertTrue(mcp.setGain(8));
  assertEqual(8, mcp.getGain());

  assertTrue(mcp.setGain());
  assertEqual(1, mcp.getGain());

  assertFalse(mcp.setGain(0));
}


unittest(test_resolution)
{
  MCP3424 mcp;

  assertEqual(12, mcp.getResolution());

  assertTrue(mcp.setResolution(14));
  assertEqual(14, mcp.getResolution());

  assertTrue(mcp.setResolution(16));
  assertEqual(16, mcp.getResolution());

  assertTrue(mcp.setResolution(18));
  assertEqual(18, mcp.getResolution());

  assertTrue(mcp.setResolution());
  assertEqual(12, mcp.getResolution());

  assertFalse(mcp.setResolution(13));
}


unittest_main()


//  -- END OF FILE --

