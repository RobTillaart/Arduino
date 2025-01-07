//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-07
// PURPOSE: unit tests for the rataryDecoderSwitch library
//          https://github.com/RobTillaart/rotaryDecoderSwitch
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


#include "rotaryDecoderSwitch.h"



unittest_setup()
{
  fprintf(stderr, "ROTARY_DECODER_SWITCH_LIB_VERSION: %s\n", (char *) ROTARY_DECODER_SWITCH_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  rotaryDecoderSwitch RE(0x20);

  Wire.begin();

  RE.begin(2);
  assertEqual(2, RE.getRECount());

  RE.begin(10);
  assertEqual(2, RE.getRECount());
}


unittest(test_getValue)
{
  rotaryDecoderSwitch RE(0x20);

  Wire.begin();

  RE.begin(2);
  for (int i = 0; i < 2; i++)
  {
    assertEqual(0, RE.getValue(i));
  }
  for (int i = 0; i < 2; i++)
  {
    RE.setValue(i, i * 100);
    assertEqual(i * 100, RE.getValue(i));
  }
}


unittest(test_getLastPosition)
{
  rotaryDecoderSwitch RE(0x20);

  Wire.begin();

  RE.begin(2);
  for (int i = 0; i < 2; i++)
  {
    assertEqual(0, RE.getLastPosition(i));
  }
}


unittest_main()


//  -- END OF FILE --

