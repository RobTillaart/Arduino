//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-05-26
// PURPOSE: unit tests for SIMON library
//          https://github.com/RobTillaart/SIMON
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
#include "simon.h"


unittest_setup()
{
  fprintf(stderr, "SIMON_LIB_VERSION: %s\n", (char *) SIMON_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(10, SIMON_MAXSIZE);
}


unittest(test_constructor)
{
  SIMON simon;

  assertEqual(0, simon.length());
  assertEqual(0, simon.size());
  assertTrue(simon.verify());
}


unittest(test_setSequence)
{
  uint8_t seq[7] = { 0, 1, 2, 3, 4, 5, 6 };

  SIMON simon;
  assertEqual(0, simon.size());
  for (int i = 0; i < 8; i++)
  {
    assertTrue(simon.setSequence(seq, i));
    assertEqual(i, simon.size());
  }

  assertFalse(simon.setSequence(seq, 12));
  assertEqual(0, simon.size());
  assertFalse(simon.setSequence(NULL, 5));
  assertEqual(0, simon.size());
}


unittest(test_generateSequence)
{
  uint8_t seq[10];

  SIMON simon;
  assertEqual(0, simon.size());
  assertTrue(simon.generateSequence(10, 1, 6));

  int len = simon.getSequence(seq);
  assertEqual(len, simon.size());

  fprintf(stderr, "%d\t", len);
  for (int i = 0; i < len; i++)
  {
    fprintf(stderr, "%d\t", seq[i]);
    assertTrue(simon.setSequence(seq, i));
  }
  fprintf(stderr, "\n\n");
}


unittest(test_getSequence)
{
  uint8_t seq[7] = { 0, 1, 2, 3, 4, 5, 6 };
  uint8_t xxx[7];

  SIMON simon;
  assertTrue(simon.setSequence(seq, 7));
  assertEqual(7, simon.getSequence(xxx));
  for (uint8_t i = 0; i < 7; i++)
  {
    assertEqual(xxx[i], seq[i]);
  };
}


unittest(test_add_OK)
{
  uint8_t seq[7] = { 0, 1, 2, 3, 4, 5, 6 };

  SIMON simon;

  assertTrue(simon.setSequence(seq, 7));
  for (int i = 0; i < 7; i++)
  {
    simon.add(i);
    assertEqual(i + 1, simon.length());
  }
  assertTrue(simon.verify());
}


unittest(test_add_FAIL)
{
  uint8_t seq[7] = { 0, 1, 2, 3, 4, 5, 6 };

  SIMON simon;

  assertTrue(simon.setSequence(seq, 7));
  for (int i = 0; i < 7; i++)
  {
    simon.add(1);  // all wrong codes
    assertEqual(i + 1, simon.length());
    assertFalse(simon.verify());
  }
  assertFalse(simon.verify());
}


unittest(test_verify)
{
  uint8_t seq[7] = { 0, 1, 2, 3, 4, 5, 6 };
  uint8_t xxx[7] = { 0, 1, 2, 3, 4, 5, 6 };

  SIMON simon;

  assertTrue(simon.setSequence(seq, 7));
  assertTrue(simon.verify(xxx, 7));
  xxx[3] = 0;
  assertFalse(simon.verify(xxx, 7));
}


unittest_main()


//  -- END OF FILE --

