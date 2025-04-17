//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-04-16
// PURPOSE: unit tests for the MCP330X
//          https://github.com/RobTillaart/MCP330X
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
#include "MCP330X.h"


unittest_setup()
{
  fprintf(stderr, "MCP330X_LIB_VERSION: %s\n", (char *) MCP330X_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  MCP3302 ADC2;
  MCP3304 ADC4;


  ADC2.begin(10);
  ADC4.begin(9);

  assertEqual(4, ADC2.channels());
  assertEqual(8, ADC4.channels());


  assertEqual(4095, ADC2.maxValue());
  assertEqual(4095, ADC4.maxValue());
}

/*
unittest(test_MCP3302)
{
  MCP3302 mcp_adc;

  mcp_adc.begin(10);

  for (int ch = 0; ch < mcp_adc.channels(); ch++)
  {
    assertEqual(0, mcp_adc.read(ch));
  }

  for (int ch = 0; ch < mcp_adc.channels(); ch++)
  {
    assertEqual(0, mcp_adc.differentialRead(ch));
  }

  for (int ch = 0; ch < mcp_adc.channels(); ch++)
  {
    assertEqual(0, mcp_adc.deltaRead(ch));
  }

}
*/

unittest_main()


//  -- END OF FILE --
