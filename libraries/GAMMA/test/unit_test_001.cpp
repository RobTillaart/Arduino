//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-24
// PURPOSE: unit tests for the GAMMA library
//          https://github.com/RobTillaart/GAMMA
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
#include "gamma.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  GAMMA gt0;  // uses default 32 size
  assertEqual(33, gt0.size());
  assertEqualFloat(2.8, gt0.getGamma(), 0.0001);
  assertEqual(28,  gt0.distinct());

  GAMMA gt1(256);
  assertEqual(257, gt1.size());
  assertEqualFloat(2.8, gt1.getGamma(), 0.0001);
  assertEqual(163, gt1.distinct());

  GAMMA gt2(128);
  assertEqual(129, gt2.size());
  assertEqualFloat(2.8, gt2.getGamma(), 0.0001);
  assertEqual(97,  gt2.distinct());
  
  GAMMA gt3(64);
  assertEqual(65, gt3.size());
  assertEqualFloat(2.8, gt3.getGamma(), 0.0001);
  assertEqual(53,  gt3.distinct());
  
  GAMMA gt4(32);    // default
  assertEqual(33, gt4.size());
  assertEqualFloat(2.8, gt4.getGamma(), 0.0001);
  assertEqual(28,  gt4.distinct());
  
  GAMMA gt5(16);
  assertEqual(17, gt5.size());
  assertEqualFloat(2.8, gt5.getGamma(), 0.0001);
  assertEqual(15, gt5.distinct());
  
  GAMMA gt6(8);
  assertEqual(9, gt6.size());
  assertEqualFloat(2.8, gt6.getGamma(), 0.0001);
  assertEqual(8, gt6.distinct());
}

unittest(test_get_set)
{
  GAMMA gt;  // uses default 32 size

  for (int i = 1; i < 20; i++)
  {
     gt.setGamma(i * 0.1);
     assertEqualFloat(i * 0.1, gt.getGamma(), 0.001);
  }
}

unittest_main()

// --------
