//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-10-25
// PURPOSE: unit tests for the AD5660 DA convertor.
//          https://github.com/RobTillaart/AD5660
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
#include "AD5660.h"



unittest_setup()
{
  fprintf(stderr, "AD5660_LIB_VERSION: %s\n", (char *) AD5660_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constructor_AD5660)
{
  AD5660 AD0(8, &SPI);    //  16 bit
  AD5660 AD1(5, 6, 7);    //  16 bit

  assertTrue(AD0.usesHWSPI());
  assertFalse(AD1.usesHWSPI());
  assertEqual(65535, AD0.getMaxValue());
}


unittest(get_type)
{
  AD5660 AD0(8);  //  implicit HW SPI
  assertEqual(16, AD0.getType());
}


unittest(get_setValue_AD5660)
{
  AD5660 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (int v = 0; v < 2000; v += 100)
  {
    assertTrue(AD0.setValue(v));
    assertEqual(v, AD0.getValue());
  }
}


unittest(get_setPercentage_AD5660)
{
  AD5660 AD0(8);  //  implicit HW SPI

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
  AD5660 AD0(8);  //  implicit HW SPI

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
