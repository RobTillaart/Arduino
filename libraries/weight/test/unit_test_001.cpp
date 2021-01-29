//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-09
// PURPOSE: unit tests for the weight conversion functions
//          https://github.com/RobTillaart/weight
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
#include "weight.h"



unittest_setup()
{
}

unittest_teardown()
{
  fprintf(stderr, "\n");
}

unittest(test_lbs2kilo)
{
  fprintf(stderr, "VERSION: %s\n", WEIGHT_LIB_VERSION);

  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, lbs2kilo(kilo2lbs(val)), 0.0001);
  }
}


unittest(test_ounce2gram)
{
  fprintf(stderr, "VERSION: %s\n", WEIGHT_LIB_VERSION);

  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, ounce2gram(gram2ounce(val)), 0.0001);
  }
}


unittest(test_gram2kilo)
{
  fprintf(stderr, "VERSION: %s\n", WEIGHT_LIB_VERSION);

  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, gram2kilo(kilo2gram(val)), 0.0001);
  }
}


unittest(test_lbs2ounce)
{
  fprintf(stderr, "VERSION: %s\n", WEIGHT_LIB_VERSION);

  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, lbs2ounce(ounce2lbs(val)), 0.0001);
  }
}


unittest(test_stone2lbs)
{
  fprintf(stderr, "VERSION: %s\n", WEIGHT_LIB_VERSION);

  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, stone2lbs(lbs2stone(val)), 0.0001);
  }
}


unittest(test_stone2kilo)
{
  fprintf(stderr, "VERSION: %s\n", WEIGHT_LIB_VERSION);

  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, stone2kilo(kilo2stone(val)), 0.0001);
  }
}


unittest(test_US2metric)
{
  fprintf(stderr, "VERSION: %s\n", WEIGHT_LIB_VERSION);

  for (int i = 0; i < 10; i++)
  {
    float stone = random(10);
    float lbs   = random(10);
    float ounce = random(10);
    float kilo  = US2metric(stone, lbs, ounce);
    float val   = kilo2lbs(kilo);    
    assertEqualFloat(val, metric2US(kilo, stone, lbs, ounce), 0.0001);
    fprintf(stderr, "\t\t%f kilo = ", kilo);
    fprintf(stderr, "%f stone + ", stone);
    fprintf(stderr, "%f lbs + ", lbs);
    fprintf(stderr, "%f ounce\n", ounce);
  }
}


unittest_main()

// --------
