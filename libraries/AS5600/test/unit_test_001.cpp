//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-05-28
// PURPOSE: unit tests for the SHEX Serial HEX library
//          https://github.com/RobTillaart/SHEX
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>

#include "AS5600.h"
#include "Wire.h"


unittest_setup()
{
  fprintf(stderr, "AS5600_LIB_VERSION: %s\n", (char *) AS5600_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, AS5600_CLOCK_WISE);
  assertEqual(1, AS5600_COUNTERCLOCK_WISE);
  assertEqual(0, AS5600_MODE_DEGREES);
  assertEqual(1, AS5600_MODE_RADIANS);

  assertEqualFloat(360.0/4095, AS5600_RAW_TO_DEGREES, 0.0001);
  assertEqualFloat((PI*2.0)/4095, AS5600_RAW_TO_RADIANS, 0.0001);

  assertEqual(0, AS5600_OUTMODE_ANALOG_100);
  assertEqual(1, AS5600_OUTMODE_ANALOG_90);
  assertEqual(2, AS5600_OUTMODE_PWM);

  assertEqual(0, AS5600_POWERMODE_NOMINAL);
  assertEqual(1, AS5600_POWERMODE_LOW1);
  assertEqual(2, AS5600_POWERMODE_LOW2);
  assertEqual(3, AS5600_POWERMODE_LOW3);

  assertEqual(0, AS5600_PWM_115);
  assertEqual(1, AS5600_PWM_230);
  assertEqual(2, AS5600_PWM_460);
  assertEqual(3, AS5600_PWM_920);

  assertEqual(0, AS5600_WATCHDOG_OFF);
  assertEqual(1, AS5600_WATCHDOG_ON);
}


unittest(test_constructor)
{
  AS5600 as5600;

  as5600.begin(4);
  assertTrue(as5600.isConnected());  // keep CI happy
}


unittest(test_address)
{
  AS5600 as5600;

  as5600.begin(4);
  assertEqual(0x36, as5600.getAddress());
}


unittest(test_direction)
{
  AS5600 as5600;

  as5600.begin(4);

  as5600.setDirection();
  assertEqual(AS5600_CLOCK_WISE, as5600.getDirection());

  as5600.setDirection(AS5600_COUNTERCLOCK_WISE);
  assertEqual(AS5600_COUNTERCLOCK_WISE, as5600.getDirection());

  as5600.setDirection(AS5600_CLOCK_WISE);
  assertEqual(AS5600_CLOCK_WISE, as5600.getDirection());
}

// FOR REMAINING ONE NEED A STUB

unittest_main()

// --------
