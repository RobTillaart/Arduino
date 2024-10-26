//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-10-25
// PURPOSE: unit tests for the AD5620 DA convertor.
//          https://github.com/RobTillaart/AD5620
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


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "AD5620.h"



unittest_setup()
{
  fprintf(stderr, "AD5620_LIB_VERSION: %s\n", (char *) AD5620_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constructor_AD5620)
{
  AD5620 AD0(8, &SPI);    //  12 bit
  AD5620 AD1(5, 6, 7);    //  12 bit

  assertTrue(AD0.usesHWSPI());
  assertFalse(AD1.usesHWSPI());
  assertEqual(4095, AD0.getMaxValue());
}


unittest(constructor_AD5640)
{
  AD5640 AD2(8, &SPI);    //  14 bit
  AD5640 AD3(5, 6, 7);    //  14 bit

  assertTrue(AD2.usesHWSPI());
  assertFalse(AD3.usesHWSPI());
  assertEqual(16383, AD2.getMaxValue());
}


unittest(get_type)
{
  AD5620 AD0(8);  //  implicit HW SPI
  assertEqual(12, AD0.getType());

  AD5640 AD1(8);  //  implicit HW SPI
  assertEqual(14, AD1.getType());
}


unittest(get_setValue_AD5620)
{
  AD5620 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (int v = 0; v < 2000; v += 100)
  {
    assertTrue(AD0.setValue(v));
    assertEqual(v, AD0.getValue());
  }
  assertFalse(AD0.setValue(4096));
}


unittest(get_setValue_AD5640)
{
  AD5640 AD1(8);  //  implicit HW SPI

  AD1.begin();
  for (int v = 0; v < 2000; v += 100)
  {
    assertTrue(AD1.setValue(v));
    assertEqual(v, AD1.getValue());
  }
   assertFalse(AD1.setValue(16384));
}


unittest(get_setPercentage_AD5620)
{
  AD5620 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (float p = 0; p < 100; p += 9)
  {
    assertTrue(AD0.setPercentage(p));
    assertEqualFloat(p, AD0.getPercentage(), 0.1);
  }
  assertFalse(AD0.setPercentage(101));
}


unittest(get_setPercentage_AD5640)
{
  AD5640 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (float p = 0; p < 100; p += 9)
  {
    assertTrue(AD0.setPercentage(p));
    assertEqualFloat(p, AD0.getPercentage(), 0.1);
  }
  assertFalse(AD0.setPercentage(101));
}


unittest(get_setPowerMode)
{
  AD5620 AD0(8);  //  implicit HW SPI

  AD0.begin();

  // default
  assertEqual(0, AD0.getPowerDownMode());
  for (float pm = 0; pm < 4; pm++)
  {
    assertTrue(AD0.setPowerDownMode(pm));
    assertEqual(pm, AD0.getPowerDownMode());
  }
  //  out of range
  assertFalse(AD0.setPowerDownMode(4));
}


unittest_main()


//  -- END OF FILE --
