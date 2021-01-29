//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the DHT temperature and humidity sensor
//          https://github.com/RobTillaart/DHTNew
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
#include "dhtnew.h"


unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_constructor)
{
  DHTNEW dht(4);

  // verify default flags
  // assertEqual(0, dht.getType());     // calls read which blocks.
  assertEqual(0, dht.getHumOffset());
  assertEqual(0, dht.getTempOffset());
  #if defined(__AVR__)
  fprintf(stderr, "__AVR__ defined.");
  assertFalse(dht.getDisableIRQ());
  #else
  fprintf(stderr, "__AVR__ not defined.");
  assertTrue(dht.getDisableIRQ());
  #endif
  assertFalse(dht.getWaitForReading());
  assertEqual(0, dht.getReadDelay());
  assertFalse(dht.getSuppressError());
}

unittest(test_hum_temp)
{
  DHTNEW dht(4);

  assertEqual(0, dht.getHumidity());
  assertEqual(0, dht.getHumOffset());
  dht.setHumOffset(1.5);
  assertEqual(1.5, dht.getHumOffset());
  
  assertEqual(0, dht.getTemperature());
  assertEqual(0, dht.getTempOffset());
  dht.setTempOffset(-1.5);
  assertEqual(-1.5, dht.getTempOffset());
}

unittest(test_process_flags)
{
  DHTNEW dht(4);

  dht.setType(11);
  assertEqual(11, dht.getType());
  dht.setType(22);
  assertEqual(22, dht.getType());
  
  dht.setDisableIRQ(true);
  assertTrue(dht.getDisableIRQ());
  dht.setDisableIRQ(false);
  assertFalse(dht.getDisableIRQ());
  
  dht.setWaitForReading(true);
  assertTrue(dht.getWaitForReading());
  dht.setWaitForReading(false);
  assertFalse(dht.getWaitForReading());
  
  dht.setReadDelay(1500);
  assertEqual(1500, dht.getReadDelay());
  dht.setType(11);
  dht.setReadDelay();
  assertEqual(0, dht.getReadDelay());
  dht.setType(22);
  dht.setReadDelay();
  assertEqual(0, dht.getReadDelay());
  
  dht.setSuppressError(true);
  assertTrue(dht.getSuppressError());
  dht.setSuppressError(false);
  assertFalse(dht.getSuppressError());
}

unittest(test_read)
{
  DHTNEW dht(4);

  fprintf(stderr, "\tread() cannot be tested\n");
  // int rc = dht.read();
  // fprintf(stderr, "%d\n", rc);
  
  long lr = dht.lastRead();
  fprintf(stderr, "\ttime since lastRead %ld\n", lr);
}

unittest_main()

// --------
