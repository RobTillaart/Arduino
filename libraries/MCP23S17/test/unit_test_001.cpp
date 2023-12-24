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
  assertEqual(MCP23S17_OK            , 0x00);
  assertEqual(MCP23S17_PIN_ERROR     , 0x81);
  assertEqual(MCP23S17_SPI_ERROR     , 0x82);
  assertEqual(MCP23S17_VALUE_ERROR   , 0x83);
  assertEqual(MCP23S17_PORT_ERROR    , 0x84);
  assertEqual(MCP23S17_REGISTER_ERROR, 0xFF);
  assertEqual(MCP23S17_INVALID_READ  , 0xFF);

  fprintf(stderr, "\nSPI-speed\n");
  assertEqual(MCP23S17_TYP_SPI_SPEED , 8000000);
  assertEqual(MCP23S17_MAX_SPI_SPEED , 10000000);
}


unittest(test_SW_constructor)
{
  MCP23S17 mcp_sw(10, 11, 12, 13);  //  default address 0x00
  assertEqual(0x00, mcp_sw.getAddress());
  assertFalse(mcp_sw.usesHWSPI());
  assertEqual(MCP23S17_OK, mcp_sw.lastError());

  for (int addr = 0; addr < 8; addr++)
  {
    MCP23S17 mcp_sw(10, 11, 12, 13, addr);
    assertEqual(addr, mcp_sw.getAddress());
  }
}


unittest(test_HW_constructors)
{
  MCP23S17 mcp_hw0(10);
  assertEqual(0x00, mcp_hw0.getAddress());
  assertTrue(mcp_hw0.usesHWSPI());
  assertEqual(MCP23S17_OK, mcp_hw0.lastError());

  for (int addr = 0; addr < 8; addr++)
  {
    MCP23S17 mcp_hw(10, addr);
    assertEqual(addr, mcp_hw.getAddress());
  }

  MCP23S17 mcp_hw1(10, &SPI);
  assertEqual(0x00, mcp_hw1.getAddress());
  assertTrue(mcp_hw1.usesHWSPI());

  for (int addr = 0; addr < 8; addr++)
  {
    MCP23S17 mcp_hw(10, addr, &SPI);
    assertEqual(addr, mcp_hw.getAddress());
    assertTrue(mcp_hw.usesHWSPI());
  }
}


////////////////////////////////////////////////////////////
//
//  1 bit interface
//
unittest(test_pinMode)
{
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.pinMode1(16, INPUT));
  assertEqual(MCP23S17_PIN_ERROR, mcp_hw.lastError());
  assertFalse(mcp_hw.pinMode1(0, 4));
  assertEqual(MCP23S17_VALUE_ERROR, mcp_hw.lastError());
}


unittest(test_digitalWrite)
{
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.write1(16, 0));
  assertEqual(MCP23S17_PIN_ERROR, mcp_hw.lastError());
}


unittest(test_digitalRead)
{
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertEqual(MCP23S17_INVALID_READ, mcp_hw.read1(16));
  assertEqual(MCP23S17_PIN_ERROR, mcp_hw.lastError());
}


unittest(test_Polarity)
{
  bool flag;
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.setPolarity(16, true));
  assertEqual(MCP23S17_PIN_ERROR, mcp_hw.lastError());

  assertFalse(mcp_hw.getPolarity(16, flag));
  assertEqual(MCP23S17_PIN_ERROR, mcp_hw.lastError());
}


unittest(test_Pullup)
{
  bool flag;
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.setPullup(16, true));
  assertEqual(MCP23S17_PIN_ERROR, mcp_hw.lastError());

  assertFalse(mcp_hw.getPullup(16, flag));
  assertEqual(MCP23S17_PIN_ERROR, mcp_hw.lastError());
}


////////////////////////////////////////////////////////////
//
//  8 bit interface
//
unittest(test_pinMode8)
{
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.pinMode8(2, 0xFF));
  assertEqual(MCP23S17_PORT_ERROR, mcp_hw.lastError());
}


unittest(test_Write8)
{
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.write8(2, HIGH));
  assertEqual(MCP23S17_PORT_ERROR, mcp_hw.lastError());
}


unittest(test_Read8)
{
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertEqual(MCP23S17_INVALID_READ, mcp_hw.read8(2));
  assertEqual(MCP23S17_PORT_ERROR, mcp_hw.lastError());
}


unittest(test_Polarity8)
{
  uint8_t mask;
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.setPolarity8(2, 0xFF));
  assertEqual(MCP23S17_PORT_ERROR, mcp_hw.lastError());

  assertFalse(mcp_hw.getPolarity8(2, mask));
  assertEqual(MCP23S17_PORT_ERROR, mcp_hw.lastError());
}


unittest(test_Pullup8)
{
  uint8_t mask;
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  assertFalse(mcp_hw.setPullup8(2, 0xFF));
  assertEqual(MCP23S17_PORT_ERROR, mcp_hw.lastError());

  assertFalse(mcp_hw.getPullup8(2, mask));
  assertEqual(MCP23S17_PORT_ERROR, mcp_hw.lastError());
}


////////////////////////////////////////////////////////////
//
//  16 bit interface
//
//  no testable calls yet.





////////////////////////////////////////////////////////////
//
//  MISC
//
unittest(test_SPIspeed)
{
  MCP23S17 mcp_hw(10);
  assertEqual(MCP23S17_OK, mcp_hw.lastError());

  for (uint32_t speed = 1000000; speed < 16000000; speed += 1000000)
  {
    mcp_hw.setSPIspeed(speed);
    assertEqual(speed, mcp_hw.getSPIspeed());
  }
}


unittest_main()


//  -- END OF FILE --

