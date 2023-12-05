//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-28
// PURPOSE: unit tests for the HT16K33
//          https://github.com/RobTillaart/HT16K33
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
#include "HT16K33.h"


unittest_setup()
{
  fprintf(stderr, "HT16K33_LIB_VERSION: %s\n", (char *) HT16K33_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  HT16K33 seg(0x70);

  Wire.begin();
  fprintf(stderr, "None of the functions return anything...\n");

  assertEqual(1, 1);
}


unittest(test_constants)
{
  assertEqual(HT16K33_0     ,  0);
  assertEqual(HT16K33_1     ,  1);
  assertEqual(HT16K33_2     ,  2);
  assertEqual(HT16K33_3     ,  3);
  assertEqual(HT16K33_4     ,  4);
  assertEqual(HT16K33_5     ,  5);
  assertEqual(HT16K33_6     ,  6);
  assertEqual(HT16K33_7     ,  7);
  assertEqual(HT16K33_8     ,  8);
  assertEqual(HT16K33_9     ,  9);
  assertEqual(HT16K33_A     ,  10);
  assertEqual(HT16K33_B     ,  11);
  assertEqual(HT16K33_C     ,  12);
  assertEqual(HT16K33_D     ,  13);
  assertEqual(HT16K33_E     ,  14);
  assertEqual(HT16K33_F     ,  15);
  assertEqual(HT16K33_SPACE ,  16);
  assertEqual(HT16K33_MINUS ,  17);
  assertEqual(HT16K33_TOP_C ,  18);
  assertEqual(HT16K33_DEGREE,  19);

  assertEqual(HT16K33_NONE  ,  99);
}


unittest_main()


//  -- END OF FILE --

