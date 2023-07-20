//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for the SHT31 temperature and humidity sensor
//          https://github.com/RobTillaart/SHT31_SWW
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
#include "SHT31_SWW.h"


int expect;  // TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;


unittest_setup()
{
  fprintf(stderr, "SHT31_SWW_LIB_VERSION: %s\n", (char *) SHT31_SWW_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_1)
{
  fprintf(stderr, "fields readStatus\n");
  assertEqual(SHT31_STATUS_ALERT_PENDING   , (1 << 15) );
  assertEqual(SHT31_STATUS_HEATER_ON       , (1 << 13) );
  assertEqual(SHT31_STATUS_HUM_TRACK_ALERT , (1 << 11) );
  assertEqual(SHT31_STATUS_TEMP_TRACK_ALERT, (1 << 10) );
  assertEqual(SHT31_STATUS_SYSTEM_RESET    , (1 << 4)  );
  assertEqual(SHT31_STATUS_COMMAND_STATUS  , (1 << 1)  );
  assertEqual(SHT31_STATUS_WRITE_CRC_STATUS, (1 << 0)  );
}


unittest(test_constants_2)
{
  fprintf(stderr, "error codes\n");
  assertEqual(SHT31_OK                 , 0x00);
  assertEqual(SHT31_ERR_WRITECMD       , 0x81);
  assertEqual(SHT31_ERR_READBYTES      , 0x82);
  assertEqual(SHT31_ERR_HEATER_OFF     , 0x83);
  assertEqual(SHT31_ERR_NOT_CONNECT    , 0x84);
  assertEqual(SHT31_ERR_CRC_TEMP       , 0x85);
  assertEqual(SHT31_ERR_CRC_HUM        , 0x86);
  assertEqual(SHT31_ERR_CRC_STATUS     , 0x87);
  assertEqual(SHT31_ERR_HEATER_COOLDOWN, 0x88);
  assertEqual(SHT31_ERR_HEATER_ON      , 0x89);
}

/*
unittest(test_begin)
{
  SHT31_SW sht;

  bool b = sht.begin(0x44);
  assertEqual(b, true);

  assertTrue(sht.reset());
  expect = SHT31_OK;
  assertEqual(expect, sht.getError());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());
  Serial.println(sht.getRawTemperature());
  Serial.println(sht.getRawHumidity());

  // default value == 0
  assertEqual(-45, sht.getTemperature());
  assertEqual(0, sht.getHumidity());
  assertEqual(0, sht.getRawTemperature());
  assertEqual(0, sht.getRawHumidity());
}


unittest(test_read)
{
  SHT31_SW sht;
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
*/


unittest_main()


//  -- END OF FILE --

