//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-25
// PURPOSE: unit tests for the GAMMA library
//          https://github.com/RobTillaart/GAMMA
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
#include "Adler.h"



unittest_setup()
{
  fprintf(stderr, "ADLER_LIB_VERSION: %s\n", (char *) ADLER_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(ADLER_MOD_PRIME, 65521);
}


unittest(test_adler32)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";

  assertEqual(96993776, adler32((uint8_t *) str1, 5));
  assertEqual(136184406, adler32((uint8_t *) str2, 6));
  assertEqual(234881829, adler32((uint8_t *) str3, 8));
}


unittest_main()

// --------
