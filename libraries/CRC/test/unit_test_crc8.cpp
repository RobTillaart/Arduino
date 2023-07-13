//
//    FILE: unit_test_crc8.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-03-31
// PURPOSE: unit tests for the CRC library
//          https://github.com/RobTillaart/CRC
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


#include "CRC.h"
#include <ArduinoUnitTests.h>
#include <Arduino.h>


char str[24] = "123456789";
uint8_t * data = (uint8_t *) str;


unittest_setup()
{}


unittest_teardown()
{}


unittest(test_crc8)
{
  fprintf(stderr, "TEST CRC8\n");

  assertEqual(0xDA, calcCRC8(data, 9, 0x9B, 0xFF));
  assertEqual(0x15, calcCRC8(data, 9, 0x39, 0x00, 0x00, true, true));
  assertEqual(0xBC, calcCRC8(data, 9, 0xD5));
  assertEqual(0x97, calcCRC8(data, 9, 0x1D, 0xFF, 0x00, true, true));
  assertEqual(0x7E, calcCRC8(data, 9, 0x1D, 0xFD));
  assertEqual(0xA1, calcCRC8(data, 9, 0x07, 0x00, 0x55));
  assertEqual(0xA1, calcCRC8(data, 9, 0x31, 0x00, 0x00, true, true));
  assertEqual(0xD0, calcCRC8(data, 9, 0x07, 0xFF, 0x00, true, true));
  assertEqual(0x25, calcCRC8(data, 9, 0x9B, 0x00, 0x00, true, true));
}


unittest_main()
