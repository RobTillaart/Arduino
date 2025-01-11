//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-11
// PURPOSE: unit tests for the AGS2616 Hydrogen H2 sensor.
//          https://github.com/RobTillaart/AGS2616
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
#include "AGS2616.h"

// writing to a virtual device does not work
// as millis() function is not implemented in 
// the Arduino-CI environment


unittest_setup()
{
  fprintf(stderr, "AGS2616_LIB_VERSION: %s\n", (char *) AGS2616_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(  0, AGS2616_OK);
  assertEqual(-10, AGS2616_ERROR);
  assertEqual(-11, AGS2616_ERROR_CRC);
  assertEqual(-12, AGS2616_ERROR_READ);
  assertEqual(-13, AGS2616_ERROR_NOT_READY);
}


unittest(test_base)
{
  AGS2616 AGS;
  Wire.begin();

  assertTrue(AGS.begin());
  assertTrue(AGS.isConnected());   // TODO - GODMODE

  assertFalse(AGS.isHeated());
  assertEqual(0, AGS.lastRead());

  assertEqual(26, AGS.getAddress());
  assertEqual(0, AGS.lastError());
  assertTrue(AGS.dataReady());
}


unittest_main()


//  -- END OF FILE --
