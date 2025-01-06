//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-08-12
// PURPOSE: unit tests for the AGS02NA TVOC sensor
//          https://github.com/RobTillaart/AGS3871
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
#include "AGS3871.h"

// writing to a virtual device does not work
// as millis() function is not implemented in 
// the Arduino-CI environment


unittest_setup()
{
  fprintf(stderr, "AGS3871_LIB_VERSION: %s\n", (char *) AGS3871_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(  0, AGS3871_OK);
  assertEqual(-10, AGS3871_ERROR);
  assertEqual(-11, AGS3871_ERROR_CRC);
  assertEqual(-12, AGS3871_ERROR_READ);
  assertEqual(-13, AGS3871_ERROR_NOT_READY);
}


unittest(test_base)
{
  AGS3871 AGS;
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
