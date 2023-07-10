//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-07
// PURPOSE: unit tests for the Gauss library
//          https://github.com/RobTillaart/Gauss
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
#include "Gauss.h"


unittest_setup()
{
    fprintf(stderr, "GAUSS_LIB_VERSION: %s\n", (char *) GAUSS_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Gauss G;
 
  assertEqualFloat(0.0, G.getMean(), 0.0001);
  assertEqualFloat(1.0, G.getStdDev(), 0.0001);
  assertEqualFloat(0.5, G.P_smaller(0), 0.0001);

  G.begin(10, 3);
  assertEqualFloat(10.0, G.getMean(), 0.0001);
  assertEqualFloat(3.0,  G.getStdDev(), 0.0001);
}


unittest(test_P_smaller)
{
  Gauss G;

  G.begin(0, 1);

  assertEqualFloat(0.0000, G.P_smaller(-6.0), 0.0001);
  assertEqualFloat(0.0001, G.P_smaller(-4.0), 0.0001);
  assertEqualFloat(0.0013, G.P_smaller(-3.0), 0.0001);
  assertEqualFloat(0.0228, G.P_smaller(-2.0), 0.0001);
  assertEqualFloat(0.1587, G.P_smaller(-1.0), 0.0001);
  assertEqualFloat(0.5000, G.P_smaller(0.0), 0.0001);
  assertEqualFloat(0.8413, G.P_smaller(1.0), 0.0001);
  assertEqualFloat(0.9772, G.P_smaller(2.0), 0.0001);
  assertEqualFloat(0.9987, G.P_smaller(3.0), 0.0001);
  assertEqualFloat(0.9999, G.P_smaller(4.0), 0.0001);
  assertEqualFloat(1.0000, G.P_smaller(6.0), 0.0001);
}


unittest(test_P_larger)
{
  Gauss G;

  G.begin(0, 1);

  assertEqualFloat(0.9987, G.P_larger(-3.0), 0.0001);
  assertEqualFloat(0.9772, G.P_larger(-2.0), 0.0001);
  assertEqualFloat(0.8413, G.P_larger(-1.0), 0.0001);
  assertEqualFloat(0.5000, G.P_larger(0.0), 0.0001);
  assertEqualFloat(0.1587, G.P_larger(1.0), 0.0001);
  assertEqualFloat(0.0228, G.P_larger(2.0), 0.0001);
  assertEqualFloat(0.0013, G.P_larger(3.0), 0.0001);
}


unittest(test_P_between)
{
  Gauss G;

  G.begin(0, 1);

  assertEqualFloat(0.4987, G.P_between(-3.0, 0.0), 0.0001);
  assertEqualFloat(0.4772, G.P_between(-2.0, 0.0), 0.0001);
  assertEqualFloat(0.3413, G.P_between(-1.0, 0.0), 0.0001);
  assertEqualFloat(0.0000, G.P_between(0.0, 0.0), 0.0001);
  assertEqualFloat(0.3413, G.P_between(0.0, 1.0), 0.0001);
  assertEqualFloat(0.4772, G.P_between(0.0, 2.0), 0.0001);
  assertEqualFloat(0.4987, G.P_between(0.0, 3.0), 0.0001);
}


unittest(test_P_outside)
{
  Gauss G;

  G.begin(0, 1);

  assertEqualFloat(0.5013, G.P_outside(-3.0, 0.0), 0.0001);
  assertEqualFloat(0.5228, G.P_outside(-2.0, 0.0), 0.0001);
  assertEqualFloat(0.6587, G.P_outside(-1.0, 0.0), 0.0001);
  assertEqualFloat(1.0000, G.P_outside(0.0, 0.0),  0.0001);
  assertEqualFloat(0.6587, G.P_outside(0.0, 1.0), 0.0001);
  assertEqualFloat(0.5228, G.P_outside(0.0, 2.0), 0.0001);
  assertEqualFloat(0.5013, G.P_outside(0.0, 3.0), 0.0001);
}


unittest(test_P_equal)
{
  Gauss G;

  G.begin(0, 1);

  assertEqualFloat(0.004432, G.P_equal(-3.0), 0.0001);
  assertEqualFloat(0.053991, G.P_equal(-2.0), 0.0001);
  assertEqualFloat(0.241971, G.P_equal(-1.0), 0.0001);
  assertEqualFloat(0.398942, G.P_equal(0.0), 0.0001);
  assertEqualFloat(0.241971, G.P_equal(1.0), 0.0001);
  assertEqualFloat(0.053991, G.P_equal(2.0), 0.0001);
  assertEqualFloat(0.004432, G.P_equal(3.0), 0.0001);
}


unittest(test_normailze)
{
  Gauss G;

  G.begin(100, 25);

  assertEqualFloat(-3.0, G.normalize(25), 0.0001);
  assertEqualFloat(-2.0, G.normalize(50), 0.0001);
  assertEqualFloat(-1.0, G.normalize(75), 0.0001);
  assertEqualFloat(0.0, G.normalize(100), 0.0001);
  assertEqualFloat(1.0, G.normalize(125), 0.0001);
  assertEqualFloat(2.0, G.normalize(150), 0.0001);
  assertEqualFloat(3.0, G.normalize(175), 0.0001);

  assertEqualFloat(25, G.denormalize(-3.0), 0.0001);
  assertEqualFloat(50, G.denormalize(-2.0), 0.0001);
  assertEqualFloat(75, G.denormalize(-1.0), 0.0001);
  assertEqualFloat(100, G.denormalize(0.0), 0.0001);
  assertEqualFloat(125, G.denormalize(1.0), 0.0001);
  assertEqualFloat(150, G.denormalize(2.0), 0.0001);
  assertEqualFloat(175, G.denormalize(3.0), 0.0001);
}


unittest_main()


//  -- END OF FILE --

