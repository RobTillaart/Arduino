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
#include "CRC16.h"


char str[24] = "123456789";
uint8_t * data = (uint8_t *) str;


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_crc16)
{
  fprintf(stderr, "TEST CRC16\n");

  CRC16 crc;
  crc.setPolynome(0x1021);
  crc.setStartXOR(0xFFFF);
  crc.add(data, 9);
  assertEqual(0x29B1, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x8005);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xBB3D, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0x1D0F);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0xE5CC, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x8005);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0xFEE8, crc.getCRC());

  crc.reset();
  crc.setPolynome(0xC867);
  crc.setStartXOR(0xFFFF);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x4C06, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x8005);
  crc.setStartXOR(0x800D);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x9ECF, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x0589);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0x0001);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x007E, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x0589);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x007F, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x3D65);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0xFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xEA82, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x3D65);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0xFFFF);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0xC2B7, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0xFFFF);
  crc.setEndXOR(0xFFFF);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0xD64E, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x8005);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0xFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x44C2, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0xFFFF);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x6F91, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0xB2AA);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x63D0, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x8BB7);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0xD0DB, crc.getCRC());

  crc.reset();
  crc.setPolynome(0xA097);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x0FB3, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0x89EC);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x26B1, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x8005);
  crc.setStartXOR(0xFFFF);
  crc.setEndXOR(0xFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xB4C8, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0xC6C6);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xBF05, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x2189, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x8005);
  crc.setStartXOR(0xFFFF);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x4B37, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0xFFFF);
  crc.setEndXOR(0xFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x906E, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1021);
  crc.setStartXOR(0x0000);
  crc.setEndXOR(0x0000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x31C3, crc.getCRC());


  /*
  assertEqual(0x29B1, crc16(data, 9, 0x1021, 0xFFFF, 0x0000, false, false ));
  assertEqual(0xBB3D, crc16(data, 9, 0x8005, 0x0000, 0x0000, true,  true  ));
  assertEqual(0xE5CC, crc16(data, 9, 0x1021, 0x1D0F, 0x0000, false, false ));
  assertEqual(0xFEE8, crc16(data, 9, 0x8005, 0x0000, 0x0000, false, false ));
  assertEqual(0x4C06, crc16(data, 9, 0xC867, 0xFFFF, 0x0000, false, false ));
  assertEqual(0x9ECF, crc16(data, 9, 0x8005, 0x800D, 0x0000, false, false ));
  assertEqual(0x007E, crc16(data, 9, 0x0589, 0x0000, 0x0001, false, false ));
  assertEqual(0x007F, crc16(data, 9, 0x0589, 0x0000, 0x0000, false, false ));
  assertEqual(0xEA82, crc16(data, 9, 0x3D65, 0x0000, 0xFFFF, true,  true  ));
  assertEqual(0xC2B7, crc16(data, 9, 0x3D65, 0x0000, 0xFFFF, false, false ));
  assertEqual(0xD64E, crc16(data, 9, 0x1021, 0xFFFF, 0xFFFF, false, false ));
  assertEqual(0x44C2, crc16(data, 9, 0x8005, 0x0000, 0xFFFF, true,  true  ));
  assertEqual(0x6F91, crc16(data, 9, 0x1021, 0xFFFF, 0x0000, true,  true  ));
  assertEqual(0x63D0, crc16(data, 9, 0x1021, 0xB2AA, 0x0000, true,  true  ));
  assertEqual(0xD0DB, crc16(data, 9, 0x8BB7, 0x0000, 0x0000, false, false ));
  assertEqual(0x0FB3, crc16(data, 9, 0xA097, 0x0000, 0x0000, false, false ));
  assertEqual(0x26B1, crc16(data, 9, 0x1021, 0x89EC, 0x0000, true,  true  ));
  assertEqual(0xB4C8, crc16(data, 9, 0x8005, 0xFFFF, 0xFFFF, true,  true  ));
  assertEqual(0xBF05, crc16(data, 9, 0x1021, 0xC6C6, 0x0000, true,  true  ));
  assertEqual(0x2189, crc16(data, 9, 0x1021, 0x0000, 0x0000, true,  true  ));
  assertEqual(0x4B37, crc16(data, 9, 0x8005, 0xFFFF, 0x0000, true,  true  ));
  assertEqual(0x906E, crc16(data, 9, 0x1021, 0xFFFF, 0xFFFF, true,  true  ));
  assertEqual(0x31C3, crc16(data, 9, 0x1021, 0x0000, 0x0000, false, false ));
  */
}


unittest_main()

// --------
