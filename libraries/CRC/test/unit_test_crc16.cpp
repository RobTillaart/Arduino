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


unittest(test_crc16)
{
  fprintf(stderr, "TEST CRC16\n");

  assertEqual(0x29B1, calcCRC16(data, 9, 0x1021, 0xFFFF, 0x0000, false, false ));
  assertEqual(0xBB3D, calcCRC16(data, 9, 0x8005, 0x0000, 0x0000, true,  true  ));
  assertEqual(0xE5CC, calcCRC16(data, 9, 0x1021, 0x1D0F, 0x0000, false, false ));
  assertEqual(0xFEE8, calcCRC16(data, 9, 0x8005, 0x0000, 0x0000, false, false ));
  assertEqual(0x4C06, calcCRC16(data, 9, 0xC867, 0xFFFF, 0x0000, false, false ));
  assertEqual(0x9ECF, calcCRC16(data, 9, 0x8005, 0x800D, 0x0000, false, false ));
  assertEqual(0x007E, calcCRC16(data, 9, 0x0589, 0x0000, 0x0001, false, false ));
  assertEqual(0x007F, calcCRC16(data, 9, 0x0589, 0x0000, 0x0000, false, false ));
  assertEqual(0xEA82, calcCRC16(data, 9, 0x3D65, 0x0000, 0xFFFF, true,  true  ));
  assertEqual(0xC2B7, calcCRC16(data, 9, 0x3D65, 0x0000, 0xFFFF, false, false ));
  assertEqual(0xD64E, calcCRC16(data, 9, 0x1021, 0xFFFF, 0xFFFF, false, false ));
  assertEqual(0x44C2, calcCRC16(data, 9, 0x8005, 0x0000, 0xFFFF, true,  true  ));
  assertEqual(0x6F91, calcCRC16(data, 9, 0x1021, 0xFFFF, 0x0000, true,  true  ));
  assertEqual(0x63D0, calcCRC16(data, 9, 0x1021, 0xB2AA, 0x0000, true,  true  ));
  assertEqual(0xD0DB, calcCRC16(data, 9, 0x8BB7, 0x0000, 0x0000, false, false ));
  assertEqual(0x0FB3, calcCRC16(data, 9, 0xA097, 0x0000, 0x0000, false, false ));
  assertEqual(0x26B1, calcCRC16(data, 9, 0x1021, 0x89EC, 0x0000, true,  true  ));
  assertEqual(0xB4C8, calcCRC16(data, 9, 0x8005, 0xFFFF, 0xFFFF, true,  true  ));
  assertEqual(0xBF05, calcCRC16(data, 9, 0x1021, 0xC6C6, 0x0000, true,  true  ));
  assertEqual(0x2189, calcCRC16(data, 9, 0x1021, 0x0000, 0x0000, true,  true  ));
  assertEqual(0x4B37, calcCRC16(data, 9, 0x8005, 0xFFFF, 0x0000, true,  true  ));
  assertEqual(0x906E, calcCRC16(data, 9, 0x1021, 0xFFFF, 0xFFFF, true,  true  ));
  assertEqual(0x31C3, calcCRC16(data, 9, 0x1021, 0x0000, 0x0000, false, false ));
}


unittest_main()
