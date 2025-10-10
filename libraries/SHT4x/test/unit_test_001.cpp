//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-09-23
// PURPOSE: unit tests for the SHT4x temperature and humidity sensor
//          https://github.com/RobTillaart/SHT4x
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
#include "SHT4x.h"


int expect;  // TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;


unittest_setup()
{
  fprintf(stderr, "SHT4x_LIB_VERSION: %s\n", (char *) SHT4x_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_1)
{
  fprintf(stderr, "SHT4x measurement commands\n");
  assertEqual(SHT4x_MEASUREMENT_SLOW        , 0xFD);
  assertEqual(SHT4x_MEASUREMENT_MEDIUM      , 0xF6);
  assertEqual(SHT4x_MEASUREMENT_FAST        , 0xE0);

  fprintf(stderr, "SHT4x measurement commands with heater\n");
  assertEqual(SHT4x_MEASUREMENT_LONG_HIGH_HEAT    , 0x39);
  assertEqual(SHT4x_MEASUREMENT_SHORT_HIGH_HEAT   , 0x32);
  assertEqual(SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT  , 0x2F);
  assertEqual(SHT4x_MEASUREMENT_SHORT_MEDIUM_HEAT , 0x24);
  assertEqual(SHT4x_MEASUREMENT_LONG_LOW_HEAT     , 0x1E);
  assertEqual(SHT4x_MEASUREMENT_SHORT_LOW_HEAT    , 0x15);
}


unittest(test_constants_2)
{
  fprintf(stderr, "error codes\n");
  assertEqual(SHT4x_OK                 , 0x00);
  assertEqual(SHT4x_ERR_WRITECMD       , 0x81);
  assertEqual(SHT4x_ERR_READBYTES      , 0x82);
  assertEqual(SHT4x_ERR_HEATER_OFF     , 0x83);
  assertEqual(SHT4x_ERR_NOT_CONNECT    , 0x84);
  assertEqual(SHT4x_ERR_CRC_TEMP       , 0x85);
  assertEqual(SHT4x_ERR_CRC_HUM        , 0x86);
  assertEqual(SHT4x_ERR_CRC_STATUS     , 0x87);
  assertEqual(SHT4x_ERR_HEATER_COOLDOWN, 0x88);
  assertEqual(SHT4x_ERR_HEATER_ON      , 0x89);
}


unittest(test_begin)
{
  SHT4x sht(0x44);

  Wire.begin();

  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.reset());
  expect = SHT4x_OK;
  assertEqual(expect, sht.getError());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());
  Serial.println(sht.getRawTemperature());
  Serial.println(sht.getRawHumidity());

  // default value == 0
  assertEqual(-45, sht.getTemperature());
  assertEqual(0,  sht.getHumidity());
  assertEqual(0, sht.getRawTemperature());
  assertEqual(0, sht.getRawHumidity());
}


unittest(test_read)
{
  SHT4x sht(0x44);

  Wire.begin();

  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.isConnected());
  expect = SHT4x_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.read());
  expect = SHT4x_ERR_READBYTES;
  assertEqual(expect, sht.getError());

/*
  TODO - can this be converted to SHT4x call
  start = millis();
  assertFalse(sht.read(false));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT4x_ERR_READBYTES;
  assertEqual(expect, sht.getError());
*/

/*
  TODO - can this be converted to SHT4x call
  start = millis();
  assertFalse(sht.read(true));
  stop = millis();
  Serial.println(stop - start);
  expect = SHT4x_ERR_READBYTES;
  assertEqual(expect, sht.getError());
  */
}



/*
  TODO - can this be converted to SHT4x call
unittest(test_heater)
{
  SHT4x sht(0x44);

  Wire.begin();

  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.heatOn());
  expect = SHT4x_OK;
  assertEqual(expect, sht.getError());

  assertTrue(sht.heatOff());
  expect = SHT4x_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.isHeaterOn());
  expect = SHT4x_OK;
  assertEqual(expect, sht.getError());
}
*/


unittest(test_async)
{
  SHT4x sht(0x44);

  Wire.begin();

  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.requestData());
  expect = SHT4x_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.dataReady());
  expect = SHT4x_OK;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData());
  expect = SHT4x_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData(true));
  expect = SHT4x_ERR_READBYTES;
  assertEqual(expect, sht.getError());

  assertFalse(sht.readData(false));
  expect = SHT4x_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}


unittest_main()

//  -- END OF FILE --