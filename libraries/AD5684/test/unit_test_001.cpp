//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-20
// PURPOSE: unit tests for the AD5684 DA convertor.
//          https://github.com/RobTillaart/AD5684
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
#include "AD5684.h"



unittest_setup()
{
  fprintf(stderr, "AD5684_LIB_VERSION: %s\n", (char *) AD5684_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constructors)
{
  AD5684 AD0(8, &SPI);
  AD5684 AD1(5, 6, 7);

  assertTrue(AD0.usesHWSPI());
  assertFalse(AD1.usesHWSPI());
}


unittest(get_type)
{
  AD5684 AD4(4);  //  implicit HW SPI
  AD5685 AD5(5);
  AD5686 AD6(6);
  assertEqual(12, AD4.getType());
  assertEqual(14, AD5.getType());
  assertEqual(16, AD6.getType());
}


unittest(get_setValue)
{
  AD5684 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (int v = 0; v < 2000; v += 100)
  {
    AD0.setValue(0, v);
    assertEqual(v, AD0.getValue(0));
  }
}


unittest(get_setPercentage)
{
  AD5684 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (float p = 0; p < 100; p += 9)
  {
    AD0.setPercentage(1, p);
    assertEqualFloat(p, AD0.getPercentage(1), 0.1);
  }
}


unittest_main()


//  -- END OF FILE --
