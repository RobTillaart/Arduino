//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for the SHT31 temperature and humidity sensor
//          https://github.com/RobTillaart/ADS1X15
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
#include "ADS1X15.h"


unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "ADS1X15_LIB_VERSION: %s\n", (char *) ADS1X15_LIB_VERSION);

  assertEqual(0x48, ADS1015_ADDRESS);
  assertEqual(0x48, ADS1115_ADDRESS);
  assertEqual(   0, ADS1X15_OK);
  assertEqual(-100, ADS1X15_INVALID_VOLTAGE);
  assertEqual(0xFF, ADS1X15_INVALID_GAIN);
  assertEqual(0xFE, ADS1X15_INVALID_MODE);
}


unittest(test_begin)
{
  ADS1115 ADS(0x48);
  assertTrue(ADS.begin());
  assertTrue(ADS.isConnected());
  assertTrue(ADS.isBusy());
}


unittest(test_gain)
{
  ADS1115 ADS(0x48);
  assertTrue(ADS.begin());

  assertEqual(0, ADS.getGain());
  int gains[6] = { 0,1,2,4,8,16 };
  for (int i = 0; i < 6; i++)
  {
    ADS.setGain(gains[i]);
    assertEqual(gains[i], ADS.getGain());
  }

  ADS.setGain(42);
  assertEqual(0, ADS.getGain());
}


unittest(test_Voltage)
{
  ADS1115 ADS(0x48);
  assertTrue(ADS.begin());

  // should test all values?
  ADS.setGain(0);
  float volts = ADS.getMaxVoltage();
  float delta = abs(6.144 - volts);
  assertMoreOrEqual(0.001, delta);

  ADS.setGain(16);
  volts = ADS.getMaxVoltage();
  delta = abs(0.256 - volts);
  assertMoreOrEqual(0.001, delta);
}


unittest_main()


// --------
