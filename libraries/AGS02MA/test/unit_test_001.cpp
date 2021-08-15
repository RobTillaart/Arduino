//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-08-12
// PURPOSE: unit tests for the AGS02NA tvoc sensor
//          https://github.com/RobTillaart/AGS02MA
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
#include "AGS02MA.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_base)
{
  AGS02MA AGS(26);
  Wire.begin();
  
  fprintf(stderr, "AGS02MA_LIB_VERSION: %s", AGS02MA_LIB_VERSION);

  assertTrue(AGS.begin());
  assertTrue(AGS.isConnected());   // TODO - GODMODE

  assertFalse(AGS.isHeated());
  assertEqual(0, AGS.lastRead());

  assertEqual(26, AGS.getAddress());
  assertTrue(AGS.setAddress(42));
  assertEqual(42, AGS.getAddress());

  assertEqual(100000, AGS.getI2CResetSpeed());
  AGS.setI2CResetSpeed(400000);
  assertEqual(400000, AGS.getI2CResetSpeed());

  assertEqual(0, AGS.lastError());
  assertEqual(0, AGS.lastStatus());

}


unittest(test_mode)
{
  AGS02MA AGS(26);
  Wire.begin();
  
  fprintf(stderr, "AGS02MA_LIB_VERSION: %s", AGS02MA_LIB_VERSION);

  assertTrue(AGS.begin());
  assertTrue(AGS.isConnected());   // TODO - GODMODE

  assertEqual(255, AGS.getMode());

  assertTrue(AGS.setPPBMode());
  assertEqual(0, AGS.getMode());

  assertTrue(AGS.setUGM3Mode());
  assertEqual(1, AGS.getMode());
}



unittest_main()

// --------
