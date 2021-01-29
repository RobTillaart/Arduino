//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the bitHelpers.h
//          https://github.com/RobTillaart/bitHelpers
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)

#include <ArduinoUnitTests.h>

#include "bitHelpers.h"


unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_bitCount)
{
  assertEqual(32, bitCountReference((uint32_t)0xFFFFFFFF));
  assertEqual(32, bitCountKR((uint32_t)0xFFFFFFFF));
  assertEqual(32, bitCountArray((uint32_t)0xFFFFFFFF));
  assertEqual(32, bitCountF1((uint32_t)0xFFFFFFFF));
  assertEqual(32, bitCountF2((uint32_t)0xFFFFFFFF));
  assertEqual(32, bitCount((uint32_t)0xFFFFFFFF));
}

unittest(test_bitReverse)
{
  assertEqual(0xAA, bitReverse((uint8_t)0x55));
  assertEqual(0xFF00, bitReverse((uint16_t)0x00FF));
  assertEqual(0xFFFFAAAA, bitReverse((uint32_t)0x5555FFFF));
  assertEqual(0xFFFFAAAAFFFFAAAA, bitReverse((uint64_t)0x5555FFFF5555FFFF));
}

unittest(test_nybbleReverse)
{
  assertEqual(0xAB, nybbleReverse((uint8_t)0xBA));
  assertEqual(0xABCD, nybbleReverse((uint16_t)0xDCBA));
  assertEqual(0x12345678, nybbleReverse((uint32_t)0x87654321));
  assertEqual(0x0123456789ABCDEF, nybbleReverse((uint64_t)0xFEDCBA9876543210));
}

unittest(test_byteReverse)
{
  assertEqual(0xABCD, byteReverse((uint16_t)0xCDAB));
  assertEqual(0x12345678, byteReverse((uint32_t)0x78563412));
  assertEqual(0x0123456789ABCDEF, byteReverse((uint64_t)0xEFCDAB8967452301));
}

unittest(test_swap)
{
  assertEqual(0x15, swap((uint8_t)0x51));
  assertEqual(0x1234, swap((uint16_t)0x3412));
  assertEqual(0x12345678, swap((uint32_t)0x56781234));
  assertEqual(0x0123456789ABCDEF, swap((uint64_t)0x89ABCDEF01234567));
}

unittest(test_bitRotateLeft)
{
  // TODO
}

unittest(test_bitRotateRight)
{
  // TODO
}

unittest(test_bitFlip)
{
  // TODO
}

unittest(test_bitsNeeded)
{
  assertEqual(15, bitsNeededRef(0x5167));
  assertEqual(6 , bitsNeeded((uint8_t)0x34));
  assertEqual(11, bitsNeeded((uint16_t)0x0412));
  assertEqual(32, bitsNeeded((uint32_t)0xF0001234));
  assertEqual(49, bitsNeeded((uint64_t)0x0001DEF012345677));
}


unittest_main()

// --------
