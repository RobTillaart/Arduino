//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the FastShiftIn library
//          https://github.com/RobTillaart/FastShiftIn
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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
// assertNotNull(actual)

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "FastShiftOut.h"

unittest_setup()
{
}

unittest_teardown()
{
}



unittest(test_constructor)
{
  FastShiftOut FSO(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTOUT_LIB_VERSION);
  assertEqual(LSBFIRST, FSO.getBitOrder());

  FSO.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, FSO.getBitOrder());
}


unittest(test_constructor_LSB)
{
  FastShiftOut FSO(12, 13, LSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTOUT_LIB_VERSION);
  assertEqual(LSBFIRST, FSO.getBitOrder());

  FSO.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, FSO.getBitOrder());
}


unittest(test_constructor_MSB)
{
  FastShiftOut FSO(12, 13, MSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTOUT_LIB_VERSION);
  assertEqual(MSBFIRST, FSO.getBitOrder());
  
  FSO.setBitOrder(LSBFIRST);
  assertEqual(LSBFIRST, FSO.getBitOrder());
}


unittest(test_write)
{
  FastShiftOut FSO(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTOUT_LIB_VERSION);

  assertEqual(1, FSO.write(0x42));
  assertEqual(1, FSO.writeLSBFIRST(0xAA));
  assertEqual(1, FSO.writeMSBFIRST(0x55));
}


unittest(test_print)
{
  FastShiftOut FSO(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTOUT_LIB_VERSION);

  assertEqual(5, FSO.print(FASTSHIFTOUT_LIB_VERSION));
  assertEqual(7, FSO.println(FASTSHIFTOUT_LIB_VERSION));
}



unittest_main()

// --------
