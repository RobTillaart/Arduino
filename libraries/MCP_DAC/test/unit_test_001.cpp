//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-02-03
// PURPOSE: unit tests for the MCP_DAC
//          https://github.com/RobTillaart/MCP_DAC
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
#include "MCP_DAC.h"


unittest_setup()
{
  fprintf(stderr, "MCP_DAC_LIB_VERSION: %s\n", (char *) MCP_DAC_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  MCP4921 MCP;

  fprintf(stderr, "test default values\n");
  assertEqual(4095, MCP.maxValue());
  assertEqual(0, MCP.lastValue());
  assertEqual(1, MCP.channels());

}


unittest(test_gain)
{
  MCP4921 MCP;

  assertEqual(1, MCP.getGain());

  assertTrue(MCP.setGain(2));
  assertEqual(2, MCP.getGain());

  assertFalse(MCP.setGain(0));
  // fprintf(stderr, "GAIN: %d", MCP.getGain());
  assertEqual(2, MCP.getGain());

  assertFalse(MCP.setGain(3));
  assertEqual(2, MCP.getGain());

  assertTrue(MCP.setGain());
  assertEqual(1, MCP.getGain());
}


unittest(test_SPI_speed)
{
  MCP4921 MCP;

  MCP.setSPIspeed(1000000);
  assertEqual(1000000, MCP.getSPIspeed());

  MCP.setSPIspeed(2000000);
  assertEqual(2000000, MCP.getSPIspeed());

  MCP.setSPIspeed(3000000);
  assertEqual(3000000, MCP.getSPIspeed());

  MCP.setSPIspeed(4000000);
  assertEqual(4000000, MCP.getSPIspeed());
}


unittest(test_active)
{
  MCP4921 MCP;

  assertTrue(MCP.isActive());

  //  MCP.shutDown();
  //  assertFalse(MCP.isActive());

  MCP.reset();
  assertTrue(MCP.isActive());
}


unittest(test_buffered_mode)
{
  MCP4921 MCP;

  assertFalse(MCP.getBufferedMode());

  MCP.setBufferedMode(true);
  assertTrue(MCP.getBufferedMode());

  MCP.setBufferedMode(false);
  assertFalse(MCP.getBufferedMode());
}


unittest_main()


//  -- END OF FILE --

