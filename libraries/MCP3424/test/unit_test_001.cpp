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


unittest(test_constructors)
{
  MCP3421 mcp1;
  MCP3422 mcp2;
  MCP3423 mcp3;
  MCP3424 mcp4;
  MCP3426 mcp6;
  MCP3427 mcp7;
  MCP3428 mcp8;

  //  base class
  assertEqual(0,  mcp4.getChannel());
  assertEqual(4,  mcp4.getMaxChannels());
  assertEqual(1,  mcp4.getGain());
  assertEqual(12, mcp4.getResolution());
  assertEqual(1,  mcp4.getMode());

  //  check MAX channels derived classes
  assertEqual(1, mcp1.getMaxChannels());
  assertEqual(2, mcp2.getMaxChannels());
  assertEqual(2, mcp3.getMaxChannels());
  assertEqual(4, mcp4.getMaxChannels());
  assertEqual(2, mcp6.getMaxChannels());
  assertEqual(2, mcp7.getMaxChannels());
  assertEqual(4, mcp8.getMaxChannels());
}


unittest(test_channel)
{
  MCP3424 mcp;

  assertEqual(0, mcp.getChannel());

  assertTrue(mcp.setChannel(1));
  assertEqual(1, mcp.getChannel());

  assertTrue(mcp.setChannel(2));
  assertEqual(2, mcp.getChannel());

  assertTrue(mcp.setChannel(3));
  assertEqual(3, mcp.getChannel());

  // default
  assertTrue(mcp.setChannel());
  assertEqual(0, mcp.getChannel());

  //  out of range
  assertFalse(mcp.setChannel(5));
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

  //  default
  assertTrue(mcp.setGain());
  assertEqual(1, mcp.getGain());

  //  out of range
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

  //  default
  assertTrue(mcp.setResolution());
  assertEqual(12, mcp.getResolution());

  //  out of range
  assertFalse(mcp.setResolution(13));
}


unittest(test_mode)
{
  MCP3424 mcp;

  assertEqual(1, mcp.getMode());

  mcp.setSingleShotMode();
  assertEqual(0, mcp.getMode());

  mcp.setContinuousMode();
  assertEqual(1, mcp.getMode());
}


unittest_main()


//  -- END OF FILE --

