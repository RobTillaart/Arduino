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
  fprintf(stderr, "GAMMA_LIB_VERSION: %s\n", (char *) GAMMA_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual( 32, GAMMA_DEFAULT_SIZE);
  assertEqual(256, GAMMA_MAX_SIZE);
}


unittest(test_constructor)
{
  GAMMA gt0;  // uses default 32 size
  assertTrue(gt0.begin());
  assertEqual(33, gt0.size());
  assertEqualFloat(2.8, gt0.getGamma(), 0.0001);
  assertEqual(29,  gt0.distinct());

  GAMMA gt1(256);
  assertTrue(gt1.begin());
  assertEqual(257, gt1.size());
  assertEqualFloat(2.8, gt1.getGamma(), 0.0001);
  assertEqual(163, gt1.distinct());

  GAMMA gt2(128);
  assertTrue(gt2.begin());
  assertEqual(129, gt2.size());
  assertEqualFloat(2.8, gt2.getGamma(), 0.0001);
  assertEqual(97,  gt2.distinct());

  GAMMA gt3(64);
  assertTrue(gt3.begin());
  assertEqual(65, gt3.size());
  assertEqualFloat(2.8, gt3.getGamma(), 0.0001);
  assertEqual(54,  gt3.distinct());

  GAMMA gt4(32);    // default
  assertTrue(gt4.begin());
  assertEqual(33, gt4.size());
  assertEqualFloat(2.8, gt4.getGamma(), 0.0001);
  assertEqual(29,  gt4.distinct());

  GAMMA gt5(16);
  assertTrue(gt5.begin());
  assertEqual(17, gt5.size());
  assertEqualFloat(2.8, gt5.getGamma(), 0.0001);
  assertEqual(16, gt5.distinct());

  GAMMA gt6(8);
  assertTrue(gt6.begin());
  assertEqual(9, gt6.size());
  assertEqualFloat(2.8, gt6.getGamma(), 0.0001);
  assertEqual(9, gt6.distinct());
}


unittest(test_get_set)
{
  GAMMA gt;  // uses default 32 size

  assertTrue(gt.begin());
  for (int i = 1; i < 20; i++)
  {
     assertTrue(gt.setGamma(i * 0.1));
     assertEqualFloat(i * 0.1, gt.getGamma(), 0.001);
  }
}


unittest(test_gamma_fail)
{
  GAMMA gt;  // uses default 32 size

  //  do not call begin() to force allocate error
  assertFalse(gt.setGamma(3.14));
  assertEqualFloat(1.0, gt.getGamma(), 0.001);
  
  assertEqualFloat(0.0, gt[63], 0.0001);
  assertFalse(gt.dump());
  assertFalse(gt.dumpArray());

  //  allocate
  assertTrue(gt.begin());
  //  still fails.
  assertFalse(gt.setGamma(-2.0));
  //  this works now
  assertTrue(gt.setGamma(3.14));
  assertEqualFloat(3.14, gt.getGamma(), 0.001);
}


unittest_main()

// --------
