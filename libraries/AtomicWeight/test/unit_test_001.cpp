//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// PURPOSE: unit tests for the AtomicWeight library
//          https://github.com/RobTillaart/AtomicWeight
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


#include "AtomicWeight.h"


unittest_setup()
{
  fprintf(stderr, "ATOMIC_WEIGHT_LIB_VERSION: %s\n", (char *) ATOMIC_WEIGHT_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{

}


unittest(test_constructor)
{
  PTOE ptoe;
  
  assertEqual(118, ptoe.size());
}


unittest(test_find)
{
  PTOE ptoe;
  
  assertEqual(1, ptoe.find("H"));
}



unittest_main()

// --------
