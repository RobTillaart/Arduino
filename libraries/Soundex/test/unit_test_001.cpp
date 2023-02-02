//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-02-05
// PURPOSE: unit tests for the Soundex library
//          https://github.com/RobTillaart/Soundex
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
#include "Soundex.h"



unittest_setup()
{
  fprintf(stderr, "SOUNDEX_LIB_VERSION: %s\n", (char *) SOUNDEX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_soundex_constants)
{
  assertEqual(SOUNDEX_MIN_LENGTH, 4);
  assertEqual(SOUNDEX_MAX_LENGTH, 12);
}


unittest(test_soundex_default)
{
  Soundex SDX;
  //  examples from Wikipedia
  assertEqual("R163", SDX.soundex("Robert"));
  assertEqual("R163", SDX.soundex("Rupert"));
  assertEqual("R150", SDX.soundex("Rubin"));
  assertEqual("T522", SDX.soundex("Tymczak"));
  assertEqual("P236", SDX.soundex("Pfister"));
  assertEqual("H555", SDX.soundex("Honeyman"));
}


unittest(test_soundex_chemicals)
{
  Soundex SDX;

  SDX.setLength(10);

  //  e.g. for long chemical names
  assertEqual("T624634500", SDX.soundex("Trichloroethylene"));
  assertEqual("P532615323", SDX.soundex("pentacarbon decahydrate"));
  assertEqual("D261524223", SDX.soundex("deoxyribonucleic acid"));
}


unittest(test_soundex16)
{
  Soundex SDX;

  assertEqual(0xA203, SDX.soundex16("Robert"));
  assertEqual(0xA203, SDX.soundex16("Rupert"));
  assertEqual(0xA1BD, SDX.soundex16("Rubin"));
  assertEqual(0xB956, SDX.soundex16("Tymczak"));
  assertEqual(0x901A, SDX.soundex16("Pfister"));
  assertEqual(0x4972, SDX.soundex16("Honeyman"));
}


unittest(test_soundex32)
{
  Soundex SDX;

  assertEqual(0x2FE4F75B, SDX.soundex32("Trichloroethylene"));
  assertEqual(0x25F6EB97, SDX.soundex32("pentacarbon decahydrate"));
  assertEqual(0x0835BD86, SDX.soundex32("deoxyribonucleic acid"));
}


unittest(test_soundex_getLength)
{
  Soundex SDX;

  assertEqual(4, SDX.getLength());

  for (int i = 4; i < 12; i++)
  {
    SDX.setLength(i);
    assertEqual(i, SDX.getLength());
  }

  //  fails
  SDX.setLength(12);
  assertNotEqual(12, SDX.getLength());
  assertEqual(11, SDX.getLength());

  //  fails
  SDX.setLength(3);
  assertNotEqual(3, SDX.getLength());
  assertEqual(4, SDX.getLength());
}


unittest_main()


//  -- END OF FILE --

