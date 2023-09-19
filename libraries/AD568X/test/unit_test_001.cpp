//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-18
// PURPOSE: unit tests for the AD568X DA convertor.
//          https://github.com/RobTillaart/AD568X
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
#include "AD568X.h"



unittest_setup()
{
  fprintf(stderr, "AD568X_LIB_VERSION: %s\n", (char *) AD568X_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constant)
{
  assertEqual(0x00, AD568X_PWR_NORMAL    );
  assertEqual(0x01, AD568X_PWR_1K        );
  assertEqual(0x02, AD568X_PWR_100K      );
  assertEqual(0x03, AD568X_PWR_TRI_STATE );
}


unittest(constructors)
{
  AD5681R AD0(8);           //  12 bit  0..4096
  AD5681R AD1(8, 9, 10);    //  12 bit  0..4096

  assertTrue(AD0.usesHWSPI());
  assertFalse(AD1.usesHWSPI());
}


unittest(get_type)
{
  AD568X  ADX(8);
  AD5681R AD1R(8);
  AD5682R AD2R(8);
  AD5683  AD3(8);
  AD5683R AD3R(8);

  assertEqual(00, ADX.getType());
  assertEqual(12, AD1R.getType());
  assertEqual(14, AD2R.getType());
  assertEqual(16, AD3.getType());
  assertEqual(16, AD3R.getType());
}


unittest(get_setValue)
{
  AD5681R AD1R(8);

  AD1R.begin();
  for (int v = 0; v < 2000; v += 100)
  {
    AD1R.setValue(v);
    assertEqual(v, AD1R.getValue());
  }
}


unittest(get_setPercentage)
{
  AD5681R AD1R(8);

  AD1R.begin();
  for (float p = 0; p < 100; p += 9)
  {
    AD1R.setPercentage(p);
    assertEqualFloat(p, AD1R.getPercentage(), 0.1);
  }
}


unittest_main()


//  -- END OF FILE --
