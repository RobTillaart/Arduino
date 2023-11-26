//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-19
// PURPOSE: unit tests for the AD5680 DA convertor.
//          https://github.com/RobTillaart/AD5680
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
#include "AD5680.h"



unittest_setup()
{
  fprintf(stderr, "AD5680_LIB_VERSION: %s\n", (char *) AD5680_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constructors)
{
  AD5680 AD0(8, &SPI);    //  18 bit
  AD5680 AD1(5, 6, 7);    //  18 bit

  assertTrue(AD0.usesHWSPI());
  assertFalse(AD1.usesHWSPI());
}


unittest(get_type)
{
  AD5680 AD0(8);  //  implicit HW SPI
  assertEqual(18, AD0.getType());
}


unittest(get_setValue)
{
  AD5680 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (int v = 0; v < 2000; v += 100)
  {
    AD0.setValue(v);
    assertEqual(v, AD0.getValue());
  }
}


unittest(get_setPercentage)
{
  AD5680 AD0(8);  //  implicit HW SPI

  AD0.begin();
  for (float p = 0; p < 100; p += 9)
  {
    AD0.setPercentage(p);
    assertEqualFloat(p, AD0.getPercentage(), 0.1);
  }
}


unittest_main()


//  -- END OF FILE --
