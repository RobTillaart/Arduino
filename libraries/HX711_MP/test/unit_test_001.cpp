//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-28
// PURPOSE: unit tests for the HX711 library (24 bit ADC for loadcells)
//          https://github.com/RobTillaart/HX711
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
#include "HX711_MP.h"


uint8_t dataPin = 6;
uint8_t clockPin = 7;


unittest_setup()
{
  fprintf(stderr, "HX711_MP_LIB_VERSION: %s\n", (char *) HX711_MP_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, HX711_AVERAGE_MODE);
  assertEqual(0x01, HX711_MEDIAN_MODE);
  assertEqual(0x02, HX711_MEDAVG_MODE);
  assertEqual(0x03, HX711_RUNAVG_MODE);
  assertEqual(0x04, HX711_RAW_MODE);

  assertEqual(128,  HX711_CHANNEL_A_GAIN_128);
  assertEqual(64,   HX711_CHANNEL_A_GAIN_64);
  assertEqual(32,   HX711_CHANNEL_B_GAIN_32);
}


unittest(test_constructor)
{
  HX711_MP scale(5);
  scale.begin(dataPin, clockPin);

  //  pins are default LOW apparently.
  assertTrue(scale.is_ready()); 
  //  default not read
  assertEqual(0, scale.last_read());
}


unittest(test_gain)
{
  HX711_MP scale(5);
  scale.begin(dataPin, clockPin);

  //  rewrite with constants?
  //  HX711_CHANNEL_A_GAIN_128
  //  HX711_CHANNEL_A_GAIN_64
  //  HX711_CHANNEL_B_GAIN_32

  //  default
  assertEqual(128, scale.get_gain());

  assertTrue(scale.set_gain(32));
  assertEqual(32, scale.get_gain());

  assertTrue(scale.set_gain());
  assertEqual(128, scale.get_gain());

  assertTrue(scale.set_gain(64));
  assertEqual(64, scale.get_gain());

  assertTrue(scale.set_gain(128));
  assertEqual(128, scale.get_gain());

  //  failing invalid parameter
  assertFalse(scale.set_gain(100));
  assertEqual(128, scale.get_gain());
  
  //  failing invalid parameter
  //  0x40 == 64 so it will fail to fail.
  //  assertFalse(scale.set_gain(0xFF40));  
  //  assertEqual(128, scale.get_gain());
}



unittest(test_operational_mode)
{
  HX711_MP scale(5);
  scale.begin(dataPin, clockPin);

  assertEqual(0x00, scale.get_mode());
  scale.set_medavg_mode();
  assertEqual(0x02, scale.get_mode());
  scale.set_median_mode();
  assertEqual(0x01, scale.get_mode());
  scale.set_average_mode();
  assertEqual(0x00, scale.get_mode());
}



unittest(test_calibration)
{
  HX711_MP scale(5);
  HX711_MP scale1(11);
  HX711_MP scale2(1);

  //  check getCalibrateSize
  assertEqual(5, scale.getCalibrateSize());
  assertEqual(10, scale1.getCalibrateSize());
  assertEqual(2, scale2.getCalibrateSize());

  //  check setCalibrate()
  assertTrue(scale.setCalibrate(0, 1000, -10000));
  assertTrue(scale.setCalibrate(1, 1300, 0));
  assertTrue(scale.setCalibrate(2, 2000, 20000));
  assertTrue(scale.setCalibrate(3, 4000, 30000));
  assertTrue(scale.setCalibrate(4, 5000, 40000));
  assertFalse(scale.setCalibrate(5, 6000, 50000));

  //  check getCalibrateRaw()
  assertEqual(1000, scale.getCalibrateRaw(0));
  assertEqual(1300, scale.getCalibrateRaw(1));
  assertEqual(2000, scale.getCalibrateRaw(2));
  assertEqual(4000, scale.getCalibrateRaw(3));
  assertEqual(5000, scale.getCalibrateRaw(4));
  assertEqual(0, scale.getCalibrateRaw(5));
  
  //  check getCalibrateWeight
  assertEqual(-10000, scale.getCalibrateWeight(0));
  assertEqual(000000, scale.getCalibrateWeight(1));
  assertEqual( 20000, scale.getCalibrateWeight(2));
  assertEqual( 30000, scale.getCalibrateWeight(3));
  assertEqual( 40000, scale.getCalibrateWeight(4));
  assertEqual(0, scale.getCalibrateWeight(5));
}


unittest_main()


//  -- END OF FILE --

