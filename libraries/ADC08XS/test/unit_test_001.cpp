//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-01-10
// PURPOSE: unit tests for the ADC081S
//          https://github.com/RobTillaart/ADC081S
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
#include "ADC08XS.h"


unittest_setup()
{
  fprintf(stderr, "ADC08XS_LIB_VERSION: %s\n", (char *) ADC08XS_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  ADC082S ADC_1;
  ADC102S ADC_2;
  ADC124S ADC_3;

  ADC_1.begin(7);
  ADC_2.begin(8);
  ADC_3.begin(9);

  assertEqual(255,  ADC_1.maxValue());
  assertEqual(2,    ADC_1.maxChannel());
  assertEqual(1023, ADC_2.maxValue());
  assertEqual(2,    ADC_2.maxChannel());
  assertEqual(4095, ADC_3.maxValue());
  assertEqual(4,    ADC_3.maxChannel());
}


unittest_main()


//  -- END OF FILE --
