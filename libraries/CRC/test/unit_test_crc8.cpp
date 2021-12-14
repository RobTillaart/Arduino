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


#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "CRC8.h"


char str[24] = "123456789";
uint8_t * data = (uint8_t *) str;


unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_crc8)
{
  fprintf(stderr, "TEST CRC8\n");

  CRC8 crc;
  crc.setPolynome(0x07);
  crc.add(data, 9);
  assertEqual(0xF4, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x39);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x15, crc.getCRC());

  crc.reset();
  crc.setPolynome(0xD5);
  crc.add(data, 9);
  assertEqual(0xBC, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1D);
  crc.setStartXOR(0xFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x97, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1D);
  crc.setStartXOR(0xFD);
  crc.add(data, 9);
  assertEqual(0x7E, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x07);
  crc.setStartXOR(0x00);
  crc.setEndXOR(0x55);
  crc.add(data, 9);
  assertEqual(0xA1, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x31);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xA1, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x07);
  crc.setStartXOR(0xFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xD0, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x9B);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x25, crc.getCRC());


  /*
  // DONE
  assertEqual(0xDA, crc8(data, 9, 0x9B, 0xFF));
  assertEqual(0x15, crc8(data, 9, 0x39, 0x00, 0x00, true, true));
  assertEqual(0xBC, crc8(data, 9, 0xD5));
  assertEqual(0x97, crc8(data, 9, 0x1D, 0xFF, 0x00, true, true));
  assertEqual(0x7E, crc8(data, 9, 0x1D, 0xFD));
  assertEqual(0xA1, crc8(data, 9, 0x07, 0x00, 0x55));
  assertEqual(0xA1, crc8(data, 9, 0x31, 0x00, 0x00, true, true));
  assertEqual(0xD0, crc8(data, 9, 0x07, 0xFF, 0x00, true, true));
  assertEqual(0x25, crc8(data, 9, 0x9B, 0x00, 0x00, true, true));
  */
}


unittest_main()

// --------
