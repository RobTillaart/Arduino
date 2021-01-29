//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-27
// PURPOSE: unit tests for the MCP4725
//          https://github.com/RobTillaart/MCP4725
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
#include "MCP4725.h"



unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", MCP4725_VERSION);
  MCP4725 MCP(0x62);
  Wire.begin();

  fprintf(stderr, "test default values\n");
  assertEqual(MCP4725_MAXVALUE, 4095);
  assertEqual(0, MCP.getValue());
  assertEqual(0, MCP.getLastWriteEEPROM());

  fprintf(stderr, "test start\n");

  assureTrue(MCP.isConnected());
  // assertTrue(MCP.begin());
  // assertTrue(MCP.isConnected());

}


unittest(test_get_setValue)
{
  MCP4725 MCP(0x62);
  Wire.begin();
  assureTrue(MCP.isConnected());

  // assertTrue(MCP.begin());
  // assertTrue(MCP.isConnected());

  // fprintf(stderr, "test start\n");
  // uint16_t last = MCP.getValue();
  // assertEqual(0, last);
  // assertEqual(0, MCP.setValue(last));
  // assertEqual(MCP4725_VALUE_ERROR, MCP.setValue(65535));
  // assertEqual(MCP4725_VALUE_ERROR, MCP.setValue(4096));
}


unittest(test_get_setPercentage)
{
  MCP4725 MCP(0x62);
  assureTrue(MCP.isConnected());
  
  // assertTrue(MCP.begin());
  // assertTrue(MCP.isConnected());
  // float last = MCP.getPercentage();
  // assertEqual(0, last);
  // assertEqual(0, MCP.setPercentage(last));
  // assertEqual(MCP4725_VALUE_ERROR, MCP.setPercentage(345));
  // assertEqual(MCP4725_VALUE_ERROR, MCP.setPercentage(100.1));
}

unittest_main()

// --------
