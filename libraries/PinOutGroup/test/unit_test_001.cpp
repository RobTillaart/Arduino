//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-05
// PURPOSE: unit tests for the PinOutGroup
//          https://github.com/RobTillaart/PinOutGroup
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
#include "PinOutGroup.h"


unittest_setup()
{
  fprintf(stderr, "PINOUTGROUP_LIB_VERSION: %s\n", (char *) PINOUTGROUP_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(16,   PINOUTGROUP_MAXSIZE);
  assertEqual(0xFF, PINOUTGROUP_ERROR_PIN);
}


unittest(test_all)
{
  PinOutGroup POG;
  uint8_t ar[16] = {2, 3, 4, 5, 6, 7};
  
  assertEqual(0,  POG.size());
  assertEqual(16, POG.available());
  assertEqual(16, POG.getMaxSize());
  assertEqual(0,  POG.isInGroup(2));

  POG.add(6, ar, LOW);
  assertEqual(6,  POG.size());
  assertEqual(10, POG.available());
  assertEqual(16, POG.getMaxSize());
  assertEqual(1,  POG.isInGroup(2));
}


unittest(test_getPin)
{
  PinOutGroup POG;
  uint8_t ar[16] = {2, 3, 4, 5, 6, 7};
  POG.add(6, ar, LOW);

  assertEqual(2,    POG.getPin(0));
  assertEqual(3,    POG.getPin(1));
  assertEqual(4,    POG.getPin(2));
  assertEqual(5,    POG.getPin(3));
  assertEqual(6,    POG.getPin(4));
  assertEqual(7,    POG.getPin(5));
  assertEqual(0xFF, POG.getPin(6));  
}


unittest(test_getIndex)
{
  PinOutGroup POG;
  uint8_t ar[16] = {2, 3, 4, 5, 6, 7};
  POG.add(6, ar, LOW);

  assertEqual(0xFF, POG.getIndex(0));  //  pin 0 is not in group
  assertEqual(0xFF, POG.getIndex(1));
  assertEqual(0,    POG.getIndex(2));
  assertEqual(1,    POG.getIndex(3));
  assertEqual(2,    POG.getIndex(4));
  assertEqual(3,    POG.getIndex(5));
  assertEqual(0xFF, POG.getIndex(8));
}




unittest_main()


// --------
