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


unittest(test_microsPerByte)
{
  Serial.begin(115200);

  const uint8_t sendPin  = 4;

  RS485 master(&Serial, sendPin);
  assertEqual(0, master.getDeviceID());

  //  default value
  assertEqual(1000, master.getMicrosPerByte());

  master.setMicrosPerByte(115200);
  //  count 11 bits / byte
  uint32_t us = (11 * 1000000UL) / 115200;
  assertEqual(us, master.getMicrosPerByte());
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

// --------
