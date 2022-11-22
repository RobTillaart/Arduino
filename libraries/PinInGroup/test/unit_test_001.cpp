//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-05
// PURPOSE: unit tests for the PinInGroup
//          https://github.com/RobTillaart/PinInGroup
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
#include "PinInGroup.h"


unittest_setup()
{
  fprintf(stderr, "PININGROUP_LIB_VERSION: %s\n", (char *) PININGROUP_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(16,   PININGROUP_MAXSIZE);
  assertEqual(0xFF, PININGROUP_ERROR_PIN);
}


unittest(test_constructor)
{
  PinInGroup PIG;
  assertEqual(0,  PIG.size());
  assertEqual(16, PIG.available());
  assertEqual(16, PIG.getMaxSize());
  assertEqual(0,  PIG.isInGroup(2));
}


unittest(test_isInGroup)
{
  PinInGroup PIG;
  uint8_t ar[8] = {2, 3, 4, 5, 6, 7, 4, 4};

  PIG.add(8, ar, INPUT_PULLUP);
  assertEqual(8,  PIG.size());
  assertEqual(8,  PIG.available());
  assertEqual(16, PIG.getMaxSize());

  assertEqual(0,  PIG.isInGroup(0));
  assertEqual(1,  PIG.isInGroup(2));
  assertEqual(1,  PIG.isInGroup(3));
  assertEqual(3,  PIG.isInGroup(4));
  assertEqual(1,  PIG.isInGroup(5));
  assertEqual(1,  PIG.isInGroup(6));
  assertEqual(1,  PIG.isInGroup(7));
  assertEqual(0,  PIG.isInGroup(8));
}


unittest(test_getIndex)
{
  PinInGroup PIG;
  uint8_t ar[8] = {2, 3, 4, 5, 6, 7, 4, 4};

  PIG.add(8, ar, INPUT_PULLUP);
  assertEqual(8,  PIG.size());
  assertEqual(8,  PIG.available());

  assertEqual(0xFF,  PIG.getIndex(0));  //  not in group
  assertEqual(0xFF,  PIG.getIndex(1));
  assertEqual(0,  PIG.getIndex(2));
  assertEqual(2,  PIG.getIndex(4));
  assertEqual(4,  PIG.getIndex(6));
  assertEqual(5,  PIG.getIndex(7));
}


unittest(test_getPin)
{
  PinInGroup PIG;
  uint8_t ar[8] = {2, 3, 4, 5, 6, 7, 4, 4};

  PIG.add(8, ar, INPUT_PULLUP);
  assertEqual(8,  PIG.size());
  assertEqual(8,  PIG.available());

  assertEqual(2,  PIG.getPin(0));
  assertEqual(3,  PIG.getPin(1));
  assertEqual(4,  PIG.getPin(2));
  assertEqual(6,  PIG.getPin(4));
  assertEqual(4,  PIG.getPin(6));
  assertEqual(4,  PIG.getPin(7));
  assertEqual(0xFF,  PIG.getPin(8));
}


unittest_main()

// --------
