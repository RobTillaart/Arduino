//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the DHT2pin library
//          https://github.com/RobTillaart/dht2pin
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


unittest(test_constants)
{
  assertEqual(00, DHTLIB_OK);
  assertEqual(-1, DHTLIB_ERROR_CHECKSUM);
  assertEqual(-2, DHTLIB_ERROR_TIMEOUT);
  assertEqual(-3, DHTLIB_ERROR_CONNECT);
  assertEqual(-4, DHTLIB_ERROR_ACK_L);
  assertEqual(-5, DHTLIB_ERROR_ACK_H);
  assertEqual(-999, DHTLIB_INVALID_VALUE);

  assertEqual(18, DHTLIB_DHT11_WAKEUP);
  assertEqual(01, DHTLIB_DHT_WAKEUP);

  //  just printing.
  fprintf(stderr, "DHTLIB_TIMEOUT: %d\n", DHTLIB_TIMEOUT);
}


unittest(test_constructor)
{
  DHT2pin DHT(2, 3);

  assertEqualFloat(0, DHT.temperature(), 0.001);
  assertEqualFloat(0, DHT.humidity(), 0.001);

  int chk = DHT.read();
  //  Nothing connected so timeout expected
  assertEqual(DHTLIB_ERROR_TIMEOUT, chk);

  //  This will set the temperature and humidity to -999
  assertEqualFloat(-999, DHT.temperature(), 0.001);
  assertEqualFloat(-999, DHT.humidity(), 0.001);
}


unittest_main()


//  -- END OF FILE --

