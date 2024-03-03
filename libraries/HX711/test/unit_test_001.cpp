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
#include "HX711.h"


uint8_t dataPin = 6;
uint8_t clockPin = 7;


unittest_setup()
{
  fprintf(stderr, "HX711_LIB_VERSION: %s\n", (char *) HX711_LIB_VERSION);
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
  HX711 scale;
  scale.begin(dataPin, clockPin);

  //  pins are default LOW apparently.
  assertTrue(scale.is_ready()); 
  //  default not read
  assertEqual(0, scale.last_read());
}


unittest(test_gain)
{
  HX711 scale;
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


unittest(test_scale)
{
  HX711 scale;
  scale.begin(dataPin, clockPin);

  // default
  assertEqualFloat(1.0, scale.get_scale(), 0.001);

  for (float sc = 0.1; sc < 2.0; sc += 0.1)
  {
    scale.set_scale(sc);
    assertEqualFloat(sc, scale.get_scale(), 0.001);
  }
  scale.set_scale();
  assertEqualFloat(1.0, scale.get_scale(), 0.001);
}


unittest(test_offset)
{
  HX711 scale;
  scale.begin(dataPin, clockPin);

  // default offset
  assertEqual(0, scale.get_offset());

  for (long of = -100; of < 100; of += 13)
  {
    scale.set_offset(of);
    assertEqual(of, scale.get_offset() );
  }
  scale.set_offset();
  assertEqual(0, scale.get_offset());
}


unittest(test_tare)
{
  HX711 scale;
  scale.begin(dataPin, clockPin);

  // default tare
  assertEqual(0, scale.get_tare());
  assertFalse(scale.tare_set());

  scale.set_offset(123);
  assertTrue(scale.tare_set());
}


unittest(test_unit_price)
{
  HX711 scale;
  scale.begin(dataPin, clockPin);

  assertEqual(0, scale.get_unit_price());

  for (float up = 0.10; up < 10; up += 1.23)
  {
    scale.set_unit_price(up);
    assertEqualFloat(up, scale.get_unit_price(), 0.001);
  }
  scale.set_unit_price();
  assertEqualFloat(1.0, scale.get_unit_price(), 0.001);
}


unittest(test_operational_mode)
{
  HX711 scale;
  scale.begin(dataPin, clockPin);

  assertEqual(0x00, scale.get_mode());
  scale.set_medavg_mode();
  assertEqual(0x02, scale.get_mode());
  scale.set_median_mode();
  assertEqual(0x01, scale.get_mode());
  scale.set_average_mode();
  assertEqual(0x00, scale.get_mode());
}


unittest_main()


//  -- END OF FILE --

