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
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", MCP_DAC_LIB_VERSION);
  MCP4921 MCP;

  fprintf(stderr, "test default values\n");
  assertEqual(4095, MCP.maxValue());
  assertEqual(0, MCP.lastValue());

  fprintf(stderr, "test start\n");

}


unittest_main()

// --------
