//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the DHT2pin library
//          https://github.com/RobTillaart/
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
#include "DHT2pin.h"



unittest_setup()
{
  fprintf(stderr, "DHT2PIN_LIB_VERSION: %s\n", (char *) DHT2PIN_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  DHT2pin DHT(2, 3);

  assertEqualFloat(0, DHT.temperature, 0.001);
  assertEqualFloat(0, DHT.humidity, 0.001);

  int chk = DHT.read22();
  // Nothing connected so timeout expected
  assertEqual(DHTLIB_ERROR_TIMEOUT, chk);  
  
  // This will set the temperature and humidity to -999
  assertEqualFloat(-999, DHT.temperature, 0.001);
  assertEqualFloat(-999, DHT.humidity, 0.001);
}


unittest_main()

// --------
