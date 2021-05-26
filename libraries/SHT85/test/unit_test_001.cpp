//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-02-10
// PURPOSE: unit tests for the SHT85 temperature and humidity sensor
//          https://github.com/RobTillaart/SHT85
//          https://nl.rs-online.com/web/p/temperature-humidity-sensor-ics/1826530
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

/*
  most unit tests will test for fail 
  as there is no sensor connected
  and there is no mockup.
  
  It appears that Wire.write does not fail without sensor...
*/

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "SHT85.h"

int expect;  // TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;

unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_begin)
{
  SHT85 sht;

  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertTrue(sht.reset());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());

  // default value == 0
  assertEqual(0, sht.getTemperature());
  assertEqual(0, sht.getHumidity());
}

unittest(test_read)
{
  SHT85 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertTrue(sht.isConnected());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.read());
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  start = millis();
  assertFalse(sht.read(false));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  start = millis();
  assertFalse(sht.read(true));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}

unittest(test_readStatus)
{
  SHT85 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertEqual(0xFFFF, sht.readStatus());
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}

unittest(test_heater)
{
  SHT85 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertTrue(sht.heatOn());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());

  assertTrue(sht.heatOff());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.isHeaterOn());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());
}

unittest(test_async)
{
  SHT85 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertTrue(sht.requestData());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.dataReady());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData());
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData(true));
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData(false));
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}

unittest_main()

// --------