//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
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
{
  fprintf(stderr, "CRC_LIB_VERSION: %s\n", (char *) CRC_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_crc8)
{
  assertEqual(0xF4, calcCRC8(data, 9, 0x07));
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


unittest(test_crc16)
{
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


unittest(test_crc32)
{
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


unittest(test_crc64)
{
  fprintf(stderr, "no reference yet\n");
  assertEqual(1, 1);
}


unittest_main()
