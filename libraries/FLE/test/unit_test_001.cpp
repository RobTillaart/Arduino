//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-23
// PURPOSE: unit tests for the FLE
//          https://github.com/RobTillaart/FLE
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
#include "FLE.h"


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
  FLE zero;
  assertEqualFloat(0.0, zero.value(), 0.001);
  assertEqualFloat(0.0, zero.error(), 0.001);

  FLE one(1);
  assertEqualFloat(1.0, one.value(), 0.001);
  assertEqualFloat(0.0, one.error(), 0.001);

  FLE PIE(PI);
  assertEqualFloat(PI, PIE.value(), 0.001);
  assertEqualFloat(0.0, PIE.error(), 0.001);

  FLE PIEP(22.0 / 7.0, PI - 22.0 / 7.0);
  assertEqualFloat(PI, PIEP.value(), 0.01);
  assertEqualFloat(0.0, PIEP.error(), 0.01);

  FLE PIEQ(355.0 / 113.0, PI - 355.0 / 113.0);
  assertEqualFloat(PI, PIEQ.value(), 0.001);
  assertEqualFloat(0.0, PIEQ.error(), 0.001);

  FLE EE(EULER);
  assertEqualFloat(EULER, EE.value(), 0.001);
  assertEqualFloat(0.0, EE.error(), 0.001);

  FLE x(2, 0.1);
  assertEqualFloat(2.0, x.value(), 0.001);
  assertEqualFloat(0.1, x.error(), 0.001);

  FLE y(7, 0.3);
  assertEqualFloat(7.0, y.value(), 0.001);
  assertEqualFloat(0.3, y.error(), 0.001);
}

unittest(test_basic_math)
{

}

unittest_main()

// --------
