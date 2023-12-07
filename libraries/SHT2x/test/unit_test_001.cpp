//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-09-25
// PURPOSE: unit tests for the SHT2x temperature and humidity sensor
//          https://github.com/RobTillaart/SHT2x
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
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon

/*
  most unit tests will test for fail
  as there is no sensor connected
  and there is no mockup.

  It appears that Wire.write does not fail without sensor...
*/


//  TODO test for derives classes?


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "SHT2x.h"

int expect;  //  TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;


unittest_setup()
{
  fprintf(stderr, "SHT2x_LIB_VERSION: %s \n", (char *) SHT2x_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_1)
{
  fprintf(stderr, "fields getStatus\n");
  assertEqual(SHT2x_STATUS_OPEN_CIRCUIT  , 0x00);
  assertEqual(SHT2x_STATUS_TEMPERATURE   , 0x01);
  assertEqual(SHT2x_STATUS_HUMIDITY      , 0x02);
  assertEqual(SHT2x_STATUS_CLOSED_CIRCUIT, 0x03);
}


unittest(test_constants_2)
{
  fprintf(stderr, "error codes\n");
  assertEqual(SHT2x_OK                 , 0x00);
  assertEqual(SHT2x_ERR_WRITECMD       , 0x81);
  assertEqual(SHT2x_ERR_READBYTES      , 0x82);
  assertEqual(SHT2x_ERR_HEATER_OFF     , 0x83);
  assertEqual(SHT2x_ERR_NOT_CONNECT    , 0x84);
  assertEqual(SHT2x_ERR_CRC_TEMP       , 0x85);
  assertEqual(SHT2x_ERR_CRC_HUM        , 0x86);
  assertEqual(SHT2x_ERR_CRC_STATUS     , 0x87);
  assertEqual(SHT2x_ERR_HEATER_COOLDOWN, 0x88);
  assertEqual(SHT2x_ERR_HEATER_ON      , 0x89);
  assertEqual(SHT2x_ERR_RESOLUTION     , 0x8A);
}


unittest(test_constructor)
{
  SHT2x sht;

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);
}


unittest(test_begin)
{
  SHT2x sht;

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.reset());
  expect = SHT2x_OK;
  assertEqual(expect, sht.getError());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());
  Serial.println(sht.getRawTemperature());
  Serial.println(sht.getRawHumidity());

  // default value == 0
  assertEqualFloat(-46.85, sht.getTemperature(), 0.01);
  assertEqualFloat(-6, sht.getHumidity(), 0.01);
  assertEqual(0, sht.getRawTemperature());
  assertEqual(0, sht.getRawHumidity());
}


unittest(test_read)
{
  SHT2x sht;

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.isConnected());
  expect = SHT2x_OK;
  assertEqual(expect, sht.getError());

  // assertion wire.available fails ...
  // assertFalse(sht.read());
  // expect = SHT2x_ERR_READBYTES;
  // assertEqual(expect, sht.getError());

  // start = millis();
  // assertFalse(sht.read());
  // stop = millis();
  // Serial.println(stop - start);
  // expect = SHT2x_ERR_READBYTES;
  // assertEqual(expect, sht.getError());

  // start = millis();
  // assertFalse(sht.read());
  // stop = millis();
  // Serial.println(stop - start);
  // expect = SHT2x_ERR_READBYTES;
  // assertEqual(expect, sht.getError());
}


unittest(test_getStatus)
{
  SHT2x sht;

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  assertEqual(0x00, sht.getStatus());
  expect = SHT2x_OK;
  assertEqual(expect, sht.getError());
}


unittest(test_heater)
{
  SHT2x sht;

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  // assertion wire.available fails ...
  // assertFalse(sht.heatOn());
  // expect = SHT2x_ERR_READBYTES;
  // assertEqual(expect, sht.getError());

  // assertFalse(sht.heatOff());
  // expect = SHT2x_ERR_READBYTES;
  // assertEqual(expect, sht.getError());

  // assertFalse(sht.isHeaterOn());
  // expect = SHT2x_OK;
  // assertEqual(expect, sht.getError());
}


unittest(test_resolution)
{
  SHT2x sht;

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  //  not set yet
  assertEqual(0, sht.getResolution());
  //  out of range
  assertFalse(sht.setResolution(4));
}


unittest_main()


//  -- END OF FILE --

