//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-29
// PURPOSE: unit tests for the WaterMix library
//          https://github.com/RobTillaart/WaterMix
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
#include "WaterMix.h"


unittest_setup()
{
  fprintf(stderr, "WATERMIX_LIB_VERSION: %s\n", (char *) WATERMIX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  WaterMix WM;

  WM.begin();

  assertEqualFloat(0, WM.volume(), 0.01);
  assertEqualFloat(0, WM.temperature(), 0.01);
}


unittest(test_add_sub)
{
  WaterMix WM;

  WM.begin();

  assertEqualFloat(0, WM.volume(), 0.01);
  assertEqualFloat(0, WM.temperature(), 0.01);
  
  WM.add(100, 10);
  assertEqualFloat(100, WM.volume(), 0.01);
  assertEqualFloat(10, WM.temperature(), 0.01);

  WM.add(100, 20);
  assertEqualFloat(200, WM.volume(), 0.01);
  assertEqualFloat(15, WM.temperature(), 0.01);
  
  WM.sub(50);
  assertEqualFloat(150, WM.volume(), 0.01);
  assertEqualFloat(15, WM.temperature(), 0.01);
}


unittest(test_div_mul)
{
  WaterMix WM;

  WM.begin();

  assertEqualFloat(0, WM.volume(), 0.01);
  assertEqualFloat(0, WM.temperature(), 0.01);
  
  WM.add(100, 10);
  assertEqualFloat(100, WM.volume(), 0.01);
  assertEqualFloat(10, WM.temperature(), 0.01);

  WM.mul(3);
  assertEqualFloat(300, WM.volume(), 0.01);
  assertEqualFloat(10, WM.temperature(), 0.01);
  
  WM.div(2);
  assertEqualFloat(150, WM.volume(), 0.01);
  assertEqualFloat(10, WM.temperature(), 0.01);
}


unittest_main()


//  -- END OF FILE --

