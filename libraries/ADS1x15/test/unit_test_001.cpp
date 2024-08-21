//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
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
  fprintf(stderr, "ADS1X15_LIB_VERSION: %s\n", (char *) ADS1X15_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_I)
{
  assertEqual(0x48, ADS1015_ADDRESS);
  assertEqual(0x48, ADS1115_ADDRESS);

  assertEqual(   0, ADS1X15_OK);
  assertEqual(-100, ADS1X15_INVALID_VOLTAGE);
  assertEqual(-101, ADS1X15_ERROR_TIMEOUT);
  assertEqual(-102, ADS1X15_ERROR_I2C);
  assertEqual(0xFF, ADS1X15_INVALID_GAIN);
  assertEqual(0xFE, ADS1X15_INVALID_MODE);
}


unittest(test_begin)
{
  ADS1115 ADS(0x48);

  Wire.begin();

  assertTrue(ADS.begin());
  assertTrue(ADS.isConnected());
  assertTrue(ADS.isBusy());
}


unittest(test_gain)
{
  ADS1115 ADS(0x48);

  Wire.begin();

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


//  For issue #68, #2
unittest(test_gain_ADS1113)
{
  ADS1113 ADS(0x48);

  Wire.begin();

  assertTrue(ADS.begin());

  assertEqual(2, ADS.getGain());
  int gains[6] = { 0,1,2,4,8,16 };
  for (int i = 0; i < 6; i++)
  {
    ADS.setGain(gains[i]);
    assertEqual(2, ADS.getGain());
    assertEqualFloat(2.048, ADS.getMaxVoltage(), 0.001);
  }

  ADS.setGain(42);
  assertEqual(2, ADS.getGain());
  assertEqualFloat(2.048, ADS.getMaxVoltage(), 0.001);
}


unittest(test_voltage)
{
  ADS1115 ADS(0x48);

  Wire.begin();

  assertTrue(ADS.begin());

  //  should test all values?
  ADS.setGain(0);
  float volts = ADS.getMaxVoltage();
  float delta = abs(6.144 - volts);
  assertMoreOrEqual(0.001, delta);

  ADS.setGain(1);
  volts = ADS.getMaxVoltage();
  delta = abs(4.096 - volts);
  assertMoreOrEqual(0.001, delta);

  ADS.setGain(2);
  volts = ADS.getMaxVoltage();
  delta = abs(2.048 - volts);
  assertMoreOrEqual(0.001, delta);

  ADS.setGain(4);
  volts = ADS.getMaxVoltage();
  delta = abs(1.024 - volts);
  assertMoreOrEqual(0.001, delta);

  ADS.setGain(8);
  volts = ADS.getMaxVoltage();
  delta = abs(0.512 - volts);
  assertMoreOrEqual(0.001, delta);

  ADS.setGain(16);
  volts = ADS.getMaxVoltage();
  delta = abs(0.256 - volts);
  assertMoreOrEqual(0.001, delta);
}


unittest(test_mode)
{
  ADS1115 ADS(0x48);

  Wire.begin();
  assertTrue(ADS.begin());

  //  test default
  assertEqual(1, ADS.getMode());
  //  test valid values
  ADS.setMode(0);
  assertEqual(0, ADS.getMode());
  ADS.setMode(1);
  assertEqual(1, ADS.getMode());
   //  test out of range
  ADS.setMode(2);
  assertEqual(1, ADS.getMode());
}


unittest(test_datarate)
{
  ADS1115 ADS(0x48);

  Wire.begin();
  assertTrue(ADS.begin());

  //  test default
  assertEqual(4, ADS.getDataRate());
  //  test valid values
  for (int i = 0; i < 8; i++)
  {
    ADS.setDataRate(i);
    assertEqual(i, ADS.getDataRate());
  }
  //  test out of range
  ADS.setDataRate(8);
  assertEqual(4, ADS.getDataRate());
}


unittest(test_comparator_mode)
{
  ADS1115 ADS(0x48);

  Wire.begin();
  assertTrue(ADS.begin());

  //  test default
  assertEqual(0, ADS.getComparatorMode());
  //  test valid values
  ADS.setComparatorMode(0);
  assertEqual(0, ADS.getComparatorMode());
  ADS.setComparatorMode(1);
  assertEqual(1, ADS.getComparatorMode());
   //  test out of range
  ADS.setComparatorMode(2);
  assertEqual(1, ADS.getComparatorMode());
}


unittest(test_comparator_polarity)
{
  ADS1115 ADS(0x48);

  Wire.begin();
  assertTrue(ADS.begin());

  //  test default
  assertEqual(1, ADS.getComparatorPolarity());
  //  test valid values
  ADS.setComparatorPolarity(0);
  assertEqual(0, ADS.getComparatorPolarity());
  ADS.setComparatorPolarity(1);
  assertEqual(1, ADS.getComparatorPolarity());
   //  test out of range
  ADS.setComparatorPolarity(2);
  assertEqual(1, ADS.getComparatorPolarity());
}


unittest(test_comparator_latch)
{
  ADS1115 ADS(0x48);

  Wire.begin();
  assertTrue(ADS.begin());

  //  test default
  assertEqual(0, ADS.getComparatorLatch());
  //  test valid values
  ADS.setComparatorLatch(0);
  assertEqual(0, ADS.getComparatorLatch());
  ADS.setComparatorLatch(1);
  assertEqual(1, ADS.getComparatorLatch());
   //  test out of range
  ADS.setComparatorLatch(2);
  assertEqual(1, ADS.getComparatorLatch());
}


unittest(test_comparator_que_convert)
{
  ADS1115 ADS(0x48);

  Wire.begin();
  assertTrue(ADS.begin());

  //  test default
  assertEqual(3, ADS.getComparatorQueConvert());
  //  test valid values
  for (int i = 0; i < 4; i++)
  {
    ADS.setComparatorQueConvert(i);
    assertEqual(i, ADS.getComparatorQueConvert());
  }
  //  test out of range
  ADS.setComparatorQueConvert(4);
  assertEqual(3, ADS.getComparatorQueConvert());
}



unittest_main()


//  -- END OF FILE --

