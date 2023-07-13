//
//    FILE: unit_test_crc32.cpp
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


unittest(test_crc32)
{
  fprintf(stderr, "TEST CRC32\n");

  assertEqual(0xCBF43926, calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true));
  assertEqual(0xFC891918, calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false));
  assertEqual(0xE3069283, calcCRC32(data, 9, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true));
  assertEqual(0x87315576, calcCRC32(data, 9, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true));
  assertEqual(0x0376E6E7, calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false));
  assertEqual(0x765E7680, calcCRC32(data, 9, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false));
  assertEqual(0x3010BF7F, calcCRC32(data, 9, 0x814141AB, 0x00000000, 0x00000000, false, false));
  assertEqual(0x340BC6D9, calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true));
  assertEqual(0xBD0BE338, calcCRC32(data, 9, 0x000000AF, 0x00000000, 0x00000000, false, false));
}


unittest_main()
