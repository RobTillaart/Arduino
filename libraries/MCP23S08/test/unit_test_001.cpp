//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-10
// PURPOSE: unit tests for the MCP23S08
//          https://github.com/RobTillaart/MCP23S08
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
#include "MCP23S08.h"


unittest_setup()
{
  fprintf(stderr, "MCP23S08_LIB_VERSION: %s\n", (char *) MCP23S08_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MCP23S08_OK            , 0x00);
  assertEqual(MCP23S08_PIN_ERROR     , 0x81);
  assertEqual(MCP23S08_SPI_ERROR     , 0x82);
  assertEqual(MCP23S08_VALUE_ERROR   , 0x83);
  assertEqual(MCP23S08_PORT_ERROR    , 0x84);
  assertEqual(MCP23S08_REGISTER_ERROR, 0xFF);
  assertEqual(MCP23S08_INVALID_READ  , 0xFF);
}


unittest(test_constructor)
{

}


unittest_main()


//  -- END OF FILE --

