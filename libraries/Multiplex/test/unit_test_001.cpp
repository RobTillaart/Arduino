//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the XXXXXX
//          https://github.com/RobTillaart/
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


#include "Arduino.h"
#include "Multiplex.h"



unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", MULTIPLEX_LIB_VERSION);

  Multiplex mp;
  assertEqual(0, mp.count());
  assertEqual(4, mp.size());

  assertTrue(mp.add(&Serial));
  assertTrue(mp.add(&Serial));
  assertEqual(2, mp.count());
  assertEqual(4, mp.size());
  
  mp.reset();
  assertEqual(0, mp.count());
  assertEqual(4, mp.size());
}

unittest(test_enable)
{
  fprintf(stderr, "VERSION: %s\n", MULTIPLEX_LIB_VERSION);

  Multiplex mp;
  assertTrue(mp.add(&Serial));
  assertTrue(mp.add(&Serial));

  for (int i = 0; i < mp.count(); i++)
  {
    assertTrue(mp.isEnabled(i));
    mp.disable(i);
    assertFalse(mp.isEnabled(i));
    mp.enable(i);
    assertTrue(mp.isEnabled(i));
  }

}

unittest_main()

// --------
