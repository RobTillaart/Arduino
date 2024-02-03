//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-05-24
// PURPOSE: unit tests for RS485
//          https://github.com/RobTillaart/RS485
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
#include "RS485.h"


unittest_setup()
{
  fprintf(stderr, "RS485_LIB_VERSION: %s\n", (char *) RS485_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_ASCII_CONTROLS)
{
  assertEqual(ASCII_NUL, 0x00);
  assertEqual(ASCII_SOH, 0x01);
  assertEqual(ASCII_STX, 0x02);
  assertEqual(ASCII_ETX, 0x03);
  assertEqual(ASCII_EOT, 0x04);
  assertEqual(ASCII_ENQ, 0x05);
  assertEqual(ASCII_ACK, 0x06);
  assertEqual(ASCII_BEL, 0x07);
  assertEqual(ASCII_BS , 0x08);
  assertEqual(ASCII_TAB, 0x09);
  assertEqual(ASCII_LF , 0x0A);
  assertEqual(ASCII_VT , 0x0B);
  assertEqual(ASCII_FF , 0x0C);
  assertEqual(ASCII_CR , 0x0D);
  assertEqual(ASCII_SO , 0x0E);
  assertEqual(ASCII_SI , 0x0F);
  assertEqual(ASCII_DLE, 0x10);
  assertEqual(ASCII_DC1, 0x11);
  assertEqual(ASCII_DC2, 0x12);
  assertEqual(ASCII_DC3, 0x13);
  assertEqual(ASCII_DC4, 0x14);
  assertEqual(ASCII_NAK, 0x15);
  assertEqual(ASCII_SYN, 0x16);
  assertEqual(ASCII_ETB, 0x17);
  assertEqual(ASCII_CAN, 0x18);
  assertEqual(ASCII_EM , 0x19);
  assertEqual(ASCII_SUB, 0x1A);
  assertEqual(ASCII_ESC, 0x1B);
  assertEqual(ASCII_FS , 0x1C);
  assertEqual(ASCII_GS , 0x1D);
  assertEqual(ASCII_RS , 0x1E);
  assertEqual(ASCII_US , 0x1F);
  assertEqual(ASCII_DEL, 0x7F);
}


unittest(test_constructor)
{
  Serial.begin(115200);

  const uint8_t sendPin  = 4;
  const uint8_t deviceID = 1;
  RS485 rs485(&Serial, sendPin, deviceID);

  assertEqual(1, rs485.getDeviceID());
  
  RS485 master(&Serial, sendPin);
  assertEqual(0, master.getDeviceID());
}


unittest(test_communication_mode)
{
  Serial.begin(115200);

  const uint8_t sendPin  = 4;

  RS485 master(&Serial, sendPin);

  //  default value
  assertEqual(0, master.getMode());
  master.setTXmode();
  assertEqual(1, master.getMode());
  master.setRXmode();
  assertEqual(0, master.getMode());
}


unittest_main()


//  -- END OF FILE --

