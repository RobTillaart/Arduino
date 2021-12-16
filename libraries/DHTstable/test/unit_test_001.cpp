//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-20
// PURPOSE: unit tests for the DHT temperature and humidity sensor
//          https://github.com/RobTillaart/DHTstable
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
#include "DHTStable.h"


unittest_setup()
{
  fprintf(stderr, "DHTSTABLE_LIB_VERSION %s\n", (char *) DHTSTABLE_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  DHTStable dht;

  assertFalse(dht.getDisableIRQ());

  dht.setDisableIRQ(true);
  assertTrue(dht.getDisableIRQ());

  dht.setDisableIRQ(false);
  assertFalse(dht.getDisableIRQ());

  fprintf(stderr, "reset() IRQ flag\n");
  dht.setDisableIRQ(true);
  assertTrue(dht.getDisableIRQ());
  dht.reset();
  assertFalse(dht.getDisableIRQ());
}


unittest(test_read)
{
  DHTStable dht;

  assertEqual(0, dht.getHumidity());
  assertEqual(0, dht.getTemperature());
  
  assertEqual(-2, dht.read(4));  // DHTLIB_ERROR_TIMEOUT
  assertEqual(-999, dht.getHumidity());
  assertEqual(-999, dht.getTemperature());

  fprintf(stderr, "reset()\n");
  dht.reset();
  assertEqual(0, dht.getHumidity());
  assertEqual(0, dht.getTemperature());
  
  assertEqual(-2, dht.read11(5));  // DHTLIB_ERROR_TIMEOUT
  assertEqual(-999, dht.getHumidity());
  assertEqual(-999, dht.getTemperature());
}


unittest_main()

// --------
