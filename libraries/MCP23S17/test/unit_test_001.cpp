//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-12-30
// PURPOSE: unit tests for the MCP23S17
//          https://github.com/RobTillaart/MCP23S17
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
#include "MCP23S17.h"


unittest_setup()
{
  fprintf(stderr, "MCP23S17_LIB_VERSION: %s\n", (char *) MCP23S17_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MCP23S17_OK          , 0x00);
  assertEqual(MCP23S17_PIN_ERROR   , 0x81);
  assertEqual(MCP23S17_SPI_ERROR   , 0x82);
  assertEqual(MCP23S17_VALUE_ERROR , 0x83);
  assertEqual(MCP23S17_PORT_ERROR  , 0x84);
  assertEqual(MCP23S17_INVALID_READ, -100);
}


unittest(test_constructor)
{

}


unittest_main()

// --------
