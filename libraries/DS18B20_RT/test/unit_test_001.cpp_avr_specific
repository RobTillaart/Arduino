//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-20
// PURPOSE: unit tests for the DS18B20 library
//          https://github.com/RobTillaart/DS18B20_RT
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
#include "DS18B20.h"



unittest_setup()
{
  fprintf(stderr, "DS18B20_LIB_VERSION: %s\n", (char *) DS18B20_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(-127, DEVICE_DISCONNECTED);
  assertEqual(-128, DEVICE_CRC_ERROR);
  assertEqual(0x00, DS18B20_CLEAR);
  assertEqual(0x01, DS18B20_CRC);
}


unittest(test_constructor)
{
  OneWire oneWire(4);
  DS18B20 sensor(&oneWire);

  sensor.begin();
  
  assertEqual(DS18B20_CLEAR, sensor.getConfig());
  
  sensor.setConfig(DS18B20_CRC);
  assertEqual(DS18B20_CRC, sensor.getConfig());
  
  sensor.setConfig(DS18B20_CLEAR);
  assertEqual(DS18B20_CLEAR, sensor.getConfig());
}


unittest(test_try_read)
{
  OneWire oneWire(4);
  DS18B20 sensor(&oneWire);

  sensor.begin();
  for (int resolution = 9; resolution < 13; resolution++)
  {
    sensor.setResolution(resolution);
    sensor.requestTemperatures();
    delay(750);
    assertFalse(sensor.isConversionComplete());
    assertEqual(DEVICE_DISCONNECTED, sensor.getTempC());
  }
}


unittest_main()

// --------
