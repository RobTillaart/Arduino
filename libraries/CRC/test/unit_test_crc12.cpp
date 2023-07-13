//
//    FILE: unit_test_crc16.cpp
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


unittest(test_crc12)
{
  fprintf(stderr, "TEST CRC12\n");

  CRC12 crc;
  crc.add(data, 9);
  assertEqual(0xEFB, crc.calc());
  crc.add(data, 9);
  assertEqual(0x1B3, crc.calc());

  assertEqual(0xEFB, calcCRC12(data, 9));

  // TODO extend

}

unittest_main()
