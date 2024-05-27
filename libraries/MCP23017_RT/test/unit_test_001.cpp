//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the MCP23017
//          https://github.com/RobTillaart/MCP23017_RT
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
#include "MCP23017.h"


unittest_setup()
{
  fprintf(stderr, "MCP23017_LIB_VERSION: %s\n", (char *) MCP23017_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MCP23017_OK            , 0x00);
  assertEqual(MCP23017_PIN_ERROR     , 0x81);
  assertEqual(MCP23017_I2C_ERROR     , 0x82);
  assertEqual(MCP23017_VALUE_ERROR   , 0x83);
  assertEqual(MCP23017_PORT_ERROR    , 0x84);
  assertEqual(MCP23017_REGISTER_ERROR, 0xFF);
  assertEqual(MCP23017_INVALID_READ  , 0xFF);
}


// TODO more tests if godmode->wire works
unittest(test_constructor)
{
  Wire.resetMocks();

  MCP23017 MCP(0x27);

  assertFalse(Wire.didBegin());
  
  Wire.begin();
  MCP.begin();
  assertTrue(Wire.didBegin());
  assertTrue(MCP.isConnected());
}


unittest(test_lastError)
{
  Wire.resetMocks();

  MCP23017 MCP(0x27);

  Wire.begin();
  MCP.begin();
  assertEqual(MCP23017_OK, MCP.lastError());

  // MCP23017_PIN_ERROR
  MCP.pinMode1(16, INPUT);
  assertEqual(MCP23017_PIN_ERROR, MCP.lastError());
  assertEqual(MCP23017_OK, MCP.lastError());

  MCP.write1(16, 1);
  assertEqual(MCP23017_PIN_ERROR, MCP.lastError());
  assertEqual(MCP23017_OK, MCP.lastError());

  uint8_t y = MCP.read1(16);
  assertEqual(MCP23017_PIN_ERROR, MCP.lastError());
  assertEqual(MCP23017_OK, MCP.lastError());


  // MCP23017_VALUE_ERROR  - 3 is not INPUT, INPUT_PULLUP, OUTPUT)
  MCP.pinMode1(0, 3);
  assertEqual(MCP23017_VALUE_ERROR, MCP.lastError());
  assertEqual(MCP23017_OK, MCP.lastError());


  // MCP23017_PORT_ERROR
  MCP.pinMode8(2, 0xF0);
  assertEqual(MCP23017_PORT_ERROR, MCP.lastError());
  assertEqual(MCP23017_OK, MCP.lastError());

  MCP.write8(2, 0xF0);
  assertEqual(MCP23017_PORT_ERROR, MCP.lastError());
  assertEqual(MCP23017_OK, MCP.lastError());

  uint8_t x = MCP.read8(2);
  assertEqual(MCP23017_PORT_ERROR, MCP.lastError());
  assertEqual(MCP23017_OK, MCP.lastError());
}


unittest_main()


//  -- END OF FILE --

