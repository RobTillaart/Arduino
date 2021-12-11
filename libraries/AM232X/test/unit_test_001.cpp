//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the AM232X temperature and humidity sensor
//          https://github.com/RobTillaart/
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
#include "AM232X.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "AM232X_LIB_VERSION: %s\n", (char *) AM232X_LIB_VERSION);

  assertEqual(  0, AM232X_OK                  );
  assertEqual(-10, AM232X_ERROR_UNKNOWN       );
  assertEqual(-11, AM232X_ERROR_CONNECT       );
  assertEqual(-12, AM232X_ERROR_FUNCTION      );
  assertEqual(-13, AM232X_ERROR_ADDRESS       );
  assertEqual(-14, AM232X_ERROR_REGISTER      );
  assertEqual(-15, AM232X_ERROR_CRC_1         );
  assertEqual(-16, AM232X_ERROR_CRC_2         );
  assertEqual(-17, AM232X_ERROR_WRITE_DISABLED);
  assertEqual(-18, AM232X_ERROR_WRITE_COUNT   );
  assertEqual(-19, AM232X_MISSING_BYTES       );
}


unittest(test_demo)
{
  AM232X AM;
  Wire.begin();

  assertTrue(AM.begin());
  assertTrue(AM.isConnected());   // TODO - GODMODE

  // assertEqual(-10, AM.read());
}


unittest_main()

// --------
