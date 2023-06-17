//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-05-18
// PURPOSE: unit tests for the TOPMAX library
//          https://github.com/RobTillaart/TOPMAX
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
#include "TOPMAX.h"



unittest_setup()
{
  fprintf(stderr, "TOPMAX_LIB_VERSION: %s\n", (char *) TOPMAX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  TOPMAX tm(5);
  assertEqual(5, tm.size());
  assertEqual(0, tm.count());
}


unittest(test_add)
{
  TOPMAX tm(5);
  assertEqual(5, tm.size());

  for (int i = 0; i < 5; i++)
  {
    assertEqual(i, tm.count());
    tm.add(i);
  }
  for (int i = 0; i < 5; i++)
  {
    assertEqual(5, tm.count());
    tm.add(i);
  }
}


unittest(test_getValue_I)
{
  TOPMAX tm(5);
  assertEqual(5, tm.size());

  for (int i = 0; i < 10; i++)
  {
    assertNAN(tm.getValue(i));
  }

  for (int i = 0; i < 5; i++)
  {
    tm.add(i);
    assertNotNAN(tm.getValue(i));
  }
  assertNAN(tm.getValue(5));
}


unittest(test_getValue_II)
{
  TOPMAX tm(5);
  assertEqual(5, tm.size());

  for (int i = 0; i < 10; i++)
  {
    tm.add(i);
    assertEqualFloat(i, tm.getValue(0), 0.001);
  }

  for (int i = 0; i < tm.count(); i++)
  {
    fprintf(stderr, "%f\t", tm.getValue(i));
  }
  fprintf(stderr, "\n");
}


unittest(test_reset)
{
  TOPMAX tm(5);
  assertEqual(5, tm.size());
  assertEqual(0, tm.count());

  for (int i = 0; i < 5; i++)
  {
    tm.add(i);
  }
  assertEqual(5, tm.count());

  tm.reset();
  assertEqual(0, tm.count());
}


unittest_main()


//  -- END OF FILE --


