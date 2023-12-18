//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the MCP_ADC
//          https://github.com/RobTillaart/MCP_ADC
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
#include "MCP_ADC.h"


unittest_setup()
{
  fprintf(stderr, "MCP_ADC_LIB_VERSION: %s\n", (char *) MCP_ADC_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  MCP3002 ADC2;
  MCP3004 ADC4;
  MCP3008 ADC8;
  MCP3202 ADC22;
  MCP3204 ADC24;
  MCP3208 ADC28;

  ADC2.begin(10);
  ADC4.begin(9);
  ADC8.begin(8);
  ADC22.begin(7);
  ADC24.begin(6);
  ADC28.begin(5);

  assertEqual(2, ADC2.channels());
  assertEqual(4, ADC4.channels());
  assertEqual(8, ADC8.channels());
  assertEqual(2, ADC22.channels());
  assertEqual(4, ADC24.channels());
  assertEqual(8, ADC28.channels());

  assertEqual(1023, ADC2.maxValue());
  assertEqual(1023, ADC4.maxValue());
  assertEqual(1023, ADC8.maxValue());
  assertEqual(4095, ADC22.maxValue());
  assertEqual(4095, ADC24.maxValue());
  assertEqual(4095, ADC28.maxValue());
}


unittest(test_MCP3002)
{
  MCP3002 mcp_adc;

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


unittest_main()


//  -- END OF FILE --
