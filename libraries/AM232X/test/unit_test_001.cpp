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
