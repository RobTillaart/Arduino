//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-08
// PURPOSE: unit tests for the HX710 A/B library
//     URL: https://github.com/RobTillaart/HX710AB
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
#include "HX710AB.h"


unittest_setup()
{
  fprintf(stderr, "HX710AB_LIB_VERSION: %s\n", (char *) HX710AB_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  HX710AB hx(4, 5);
  HX710A hxa(6, 7);
  HX710B hxb(8, 9);

  assertEqual(1,1);
}


unittest(test_calibrate)
{
  HX710B hx(8, 9);

  hx.calibrate(50, 50, 80, 100);
  fprintf(stderr, "offset %f\n", hx.get_offset());
  fprintf(stderr, "scale %f\n", hx.get_scale());
  assertEqualFloat(20.000, hx.get_offset(), 0.01);
  assertEqualFloat(0.6, hx.get_scale(), 0.01);
}


unittest(test_offset)
{
  HX710B hx(8, 9);

  for (int i = -1000; i < 1000; i += 173)
  {
    hx.set_offset(i);
    assertEqualFloat(float(i), hx.get_offset(), 0.01);
  }
}


unittest(test_scale)
{
  HX710B hx(8, 9);

  for (int i = -1000; i < 1000; i += 173)
  {
    hx.set_scale(i);
    assertEqualFloat(float(i), hx.get_scale(), 0.01);
  }
}


unittest_main()


//  -- END OF FILE --

