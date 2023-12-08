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
  fprintf(stderr, "MCP4725_VERSION: %s\n", (char *) MCP4725_VERSION);
}


unittest_teardown()
{
}


//  MCP.begin() has blocking calls
//  cannot be tested without stub
unittest(test_constructor)
{
  MCP4725 MCP(0x62);
  Wire.begin();

  assertEqual(0x62, MCP.getAddress());

  assertEqual(0, MCP.getValue());
  assertEqual(0, MCP.getLastWriteEEPROM());

  fprintf(stderr, "test start\n");
  assureTrue(MCP.isConnected());
  // assertTrue(MCP.begin());
}


unittest(test_invalid_address)
{
  MCP4725 MCP_F(0x22);
  assertFalse(MCP_F.begin());
}


unittest(test_constant)
{
  fprintf(stderr, "test default values\n");
  assertEqual(MCP4725_MAXVALUE, 4095);
  assertEqual(MCP4725_OK, 0);
  assertEqual(MCP4725_VALUE_ERROR, -999);
  assertEqual(MCP4725_REG_ERROR, -998);
  assertEqual(MCP4725_NOT_CONNECTED, -997);

  fprintf(stderr, "test mode values\n");
  assertEqual(MCP4725_PDMODE_NORMAL, 0);
  assertEqual(MCP4725_PDMODE_1K, 1);
  assertEqual(MCP4725_PDMODE_100K, 2);
  assertEqual(MCP4725_PDMODE_500K, 3);

  fprintf(stderr, "other\n");
  assertEqual(MCP4725_MIDPOINT, 2048);
}


unittest(test_get_setValue)
{
  MCP4725 MCP(0x62);

  assertEqual(MCP4725_VALUE_ERROR, MCP.setValue(65535));
  assertEqual(MCP4725_VALUE_ERROR, MCP.setValue(4096));
}


unittest(test_get_setPercentage)
{
  MCP4725 MCP(0x62);

  assertEqual(MCP4725_VALUE_ERROR, MCP.setPercentage(345));
  assertEqual(MCP4725_VALUE_ERROR, MCP.setPercentage(100.1));
}


unittest(test_writeDAC)
{
  MCP4725 MCP(0x62);

  assertEqual(MCP4725_VALUE_ERROR, MCP.writeDAC(4096, false));
  assertEqual(MCP4725_VALUE_ERROR, MCP.writeDAC(4096, true));
}


unittest_main()


//  -- END OF FILE --

