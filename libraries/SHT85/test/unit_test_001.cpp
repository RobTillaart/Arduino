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
  and there is no mock-up.

  It appears that Wire.write does not fail without sensor...
*/


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "SHT85.h"


int expect;  //  TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;


unittest_setup()
{
  fprintf(stderr, "SHT_LIB_VERSION: %s\n", (char *) SHT_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_1)
{
  assertEqual(SHT_DEFAULT_ADDRESS, 0x44);

  fprintf(stderr, "fields readStatus\n");
  assertEqual(SHT_STATUS_ALERT_PENDING   , (1 << 15) );
  assertEqual(SHT_STATUS_HEATER_ON       , (1 << 13) );
  assertEqual(SHT_STATUS_HUM_TRACK_ALERT , (1 << 11) );
  assertEqual(SHT_STATUS_TEMP_TRACK_ALERT, (1 << 10) );
  assertEqual(SHT_STATUS_SYSTEM_RESET    , (1 << 4)  );
  assertEqual(SHT_STATUS_COMMAND_STATUS  , (1 << 1)  );
  assertEqual(SHT_STATUS_WRITE_CRC_STATUS, (1 << 0)  );
}


unittest(test_constants_2)
{
  fprintf(stderr, "error codes\n");
  assertEqual(SHT_OK                 , 0x00);
  assertEqual(SHT_ERR_WRITECMD       , 0x81);
  assertEqual(SHT_ERR_READBYTES      , 0x82);
  assertEqual(SHT_ERR_HEATER_OFF     , 0x83);
  assertEqual(SHT_ERR_NOT_CONNECT    , 0x84);
  assertEqual(SHT_ERR_CRC_TEMP       , 0x85);
  assertEqual(SHT_ERR_CRC_HUM        , 0x86);
  assertEqual(SHT_ERR_CRC_STATUS     , 0x87);
  assertEqual(SHT_ERR_HEATER_COOLDOWN, 0x88);
  assertEqual(SHT_ERR_HEATER_ON      , 0x89);
}


unittest(test_begin)
{
  SHT85 sht(0x44);

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.reset());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());

  Serial.println(sht.getTemperature());
  Serial.println(sht.getHumidity());
  Serial.println(sht.getRawTemperature());
  Serial.println(sht.getRawHumidity());

  //  default value == 0
  assertEqual(-45, sht.getTemperature());
  assertEqual(-49, sht.getFahrenheit());
  assertEqual(0, sht.getHumidity());
  assertEqual(0, sht.getRawTemperature());
  assertEqual(0, sht.getRawHumidity());
}


unittest(test_read)
{
  SHT85 sht(0x44);

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  assertTrue(sht.isConnected());
  expect = SHT_OK;
  assertEqual(expect, sht.getError());
}


unittest(test_readStatus)
{
  SHT85 sht(0x44);

  Wire.begin();
  bool b = sht.begin();
  assertEqual(b, true);

  assertEqual(0xFFFF, sht.readStatus());
  expect = SHT_ERR_READBYTES;
  assertEqual(expect, sht.getError());
}


unittest(test_heater)
{
  SHT85 sht(0x44);

  Wire.begin();
  bool b = sht.begin();
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
  SHT85 sht(0x44);

  Wire.begin();
  bool b = sht.begin();
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



unittest(test_offset)
{
  SHT85 sht(0x44);

  Wire.begin();
  bool b = sht.begin();
  fprintf(stderr, "temperature\n");
  for (int i = -5; i < 6; i++)
  {
    sht.setTemperatureOffset(i);
    assertEqual(i, sht.getTemperatureOffset());
  }
  fprintf(stderr, "humidity\n");
  for (int i = -5; i < 6; i++)
  {
    sht.setHumidityOffset(i);
    assertEqual(i, sht.getHumidityOffset());
  }
}


//////////////////////////////////////////
//
//  Test derived types
//
unittest(test_getType)
{
  SHT   sht(0x44);
  SHT30 sht0(0x44);
  SHT31 sht1(0x44);
  SHT35 sht2(0x44);
  SHT85 sht3(0x44);

  assertEqual(00, sht.getType());
  assertEqual(30, sht0.getType());
  assertEqual(31, sht1.getType());
  assertEqual(35, sht2.getType());
  assertEqual(85, sht3.getType());
}


unittest_main()


//  -- END OF FILE --

