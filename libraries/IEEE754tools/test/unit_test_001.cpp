//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the IEEE754tools.h
//          https://github.com/RobTillaart/IEEE754tools
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
#include "IEEE754tools.h"



unittest_setup()
{
  fprintf(stderr, "IEEE754_LIB_VERSION: %s\n", (char*) IEEE754_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_all)
{
  fprintf(stderr, "Convert PI to double and back\n");
  uint8_t ar[8];
  float p = PI;
  float2DoublePacked(p, ar);
  float q = doublePacked2Float(ar);
  assertEqualFloat(p, q, 0.0001);

  fprintf(stderr, "IEEE_NAN %f\n", 0.0 / 0.0);
  // assertTrue(IEEE_NAN(0.0 / 0.0));   //  -nan ?

  fprintf(stderr, "IEEE_INF\n");
  assertEqual(1,  IEEE_INF(exp(800)));
  assertEqual(-1, IEEE_INF(-exp(800)));
  assertEqual(0,  IEEE_INF(PI));

  fprintf(stderr, "IEEE_PosINF\n");
  assertTrue(IEEE_PosINF(exp(800)));

  fprintf(stderr, "IEEE_NegINF\n");
  assertTrue(IEEE_NegINF(-exp(800)));

  //  crash - AVR specific
  // fprintf(stderr, "IEEE_Sign\n");
  // assertTrue(IEEE_Sign(PI));
  // assertTrue(IEEE_Sign(-PI));
  // 
  // fprintf(stderr, "IEEE_Exponent\n");
  // assertTrue(IEEE_Exponent(PI));
  // 
  // fprintf(stderr, "IEEE_Mantisse\n");
  // assertTrue(IEEE_Mantisse(PI));

  // crash - AVR specific
  // fprintf(stderr, "IEEE_POW2\n");
  // float f = 2;
  // for (int i = 0; i < 20; i++)
  // {
  //   fprintf(stderr, "%d\t%f\t", i, f);
  //   assertEqualFloat(f, IEEE_POW2(1, i), 0.0001);
  //   f *= 2;
  // }
  // 
  // fprintf(stderr, "IEEE_POW2fast\n");
  // f = 2;
  // for (int i = 0; i < 20; i++)
  // {
  //   fprintf(stderr, "%d\t%f\t", i, f);
  //   assertEqualFloat(f, IEEE_POW2fast(1, i), 0.0001);
  //   f *= 2;
  // }

}


unittest_main()


//  -- END OF FILE -- 

