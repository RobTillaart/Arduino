//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for the SHT31 temperature and humidity sensor
//          https://github.com/RobTillaart/SHT31
//          https://www.adafruit.com/product/2857
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
#include "SHT31.h"

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
  SHT31 sht;

  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertTrue(sht.reset());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());

  // default value == 0
  assertEqual(0, sht.getTemperature());
  assertEqual(0, sht.getHumidity());
}

unittest(test_read)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertTrue(sht.isConnected());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.read());
  expect = SHT31_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  start = millis();
  assertFalse(sht.read(false));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT31_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  start = millis();
  assertFalse(sht.read(true));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT31_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}

unittest(test_readStatus)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertEqual(0xFFFF, sht.readStatus());
  expect = SHT31_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}

unittest(test_heater)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertTrue(sht.heatOn());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());

  assertTrue(sht.heatOff());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.isHeaterOn());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());
}

unittest(test_async)
{
  SHT31 sht;
  bool b = sht.begin(0x44);
  assertEqual(b, true);
  
  assertTrue(sht.requestData());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.dataReady());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData());
  expect = SHT31_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData(true));
  expect = SHT31_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData(false));
  expect = SHT31_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}

unittest_main()

// --------