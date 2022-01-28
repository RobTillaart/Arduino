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


#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "CRC12.h"


char str[24] = "123456789";
uint8_t * data = (uint8_t *) str;


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_crc12_getters)
{
  fprintf(stderr, "TEST CRC12 GETTERS\n");

  CRC12 crc;
  crc.setPolynome(0x080D);
  crc.setStartXOR(0x0555);
  crc.setEndXOR(0x0AAA);
  crc.setReverseIn(true);
  crc.setReverseOut(false);
  
  assertEqual(0x080D, crc.getPolynome());
  assertEqual(0x0555, crc.getStartXOR());
  assertEqual(0x0AAA, crc.getEndXOR());
  assertTrue(crc.getReverseIn());
  assertFalse(crc.getReverseOut());
}


unittest(test_crc12)
{
  fprintf(stderr, "TEST CRC12\n");

  CRC12 crc;
  crc.setPolynome(0x080D);
  crc.add(data, 9);
  assertEqual(0xEFB, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x080D);
  crc.add(data, 9);
  crc.add(data, 9);
  assertEqual(0x1B3, crc.getCRC());

  // TODO extend

}


unittest_main()

// --------
