//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-10
// PURPOSE: unit tests for the MCP23008
//          https://github.com/RobTillaart/MCP23008
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
#include "MCP23008.h"


unittest_setup()
{
  fprintf(stderr, "MCP23008_LIB_VERSION: %s\n", (char *) MCP23008_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MCP23008_OK            , 0x00);
  assertEqual(MCP23008_PIN_ERROR     , 0x81);
  assertEqual(MCP23008_I2C_ERROR     , 0x82);
  assertEqual(MCP23008_VALUE_ERROR   , 0x83);
  assertEqual(MCP23008_REGISTER_ERROR, 0xFF);
  assertEqual(MCP23008_INVALID_READ  , 0xFF);
}


//  TODO more tests if godmode->wire works
unittest(test_constructor)
{
  Wire.resetMocks();

  MCP23008 MCP(0x27);

  assertFalse(Wire.didBegin());

  Wire.begin();
  MCP.begin();

  //  in fact invalid ...
  assertTrue(Wire.didBegin());
  assertTrue(MCP.isConnected());
}


unittest(test_lastError)
{
  Wire.resetMocks();

  MCP23008 MCP(0x27);

  Wire.begin();
  MCP.begin();
  assertEqual(MCP23008_OK, MCP.lastError());

  //  MCP23008_PIN_ERROR
  MCP.pinMode1(8, INPUT);
  assertEqual(MCP23008_PIN_ERROR, MCP.lastError());
  assertEqual(MCP23008_OK, MCP.lastError());

  MCP.write1(8, 1);
  assertEqual(MCP23008_PIN_ERROR, MCP.lastError());
  assertEqual(MCP23008_OK, MCP.lastError());

  uint8_t y = MCP.read1(8);
  assertEqual(MCP23008_PIN_ERROR, MCP.lastError());
  assertEqual(MCP23008_OK, MCP.lastError());


  //  MCP23008_VALUE_ERROR  - 3 is not INPUT, INPUT_PULLUP, OUTPUT)
  MCP.pinMode1(0, 3);
  assertEqual(MCP23008_VALUE_ERROR, MCP.lastError());
  assertEqual(MCP23008_OK, MCP.lastError());
}


unittest_main()


//  --END OF FILE --

