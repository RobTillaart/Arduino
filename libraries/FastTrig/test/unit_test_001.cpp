//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-23
// PURPOSE: unit tests for the FastTrig library
//          https://github.com/RobTillaart/FastTrig
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
#include "FastTrig.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_isinTable16)
{
  fprintf(stderr,"Table16 error is < 0.1%% \n");
  const float degrees2radians = PI/180.0;
  for (int i = 0; i < 91; i++)
  {
    assertEqualFloat(sin(i * degrees2radians), isinTable16[i] / 65535.0, 0.001);
  }
}

unittest(test_isinTable8)
{
  fprintf(stderr,"Table8 error is < 1%% \n");
  const float degrees2radians = PI/180.0;
  for (int i = 0; i < 91; i++)
  {
    assertEqualFloat(sin(i * degrees2radians), isinTable8[i] / 255.0, 0.01);
  }
}

unittest(test_max_error_table16)
{
  fprintf(stderr,"Table16 max error: ");
  const float degrees2radians = PI/180.0;
  float m = 0;
  for (int i = 0; i < 91; i++)
  {
    float t = abs(sin(i * degrees2radians) - (isinTable16[i] / 65535.0));
    if (t > m) m = t;
  }
  fprintf(stderr,"%2.4f\n", m);
  assertEqualFloat(0, m, 0.001);
}

unittest(test_max_error_table8)
{
  fprintf(stderr,"Table8 max error: ");
  const float degrees2radians = PI/180.0;
  float m = 0;
  for (int i = 0; i < 91; i++)
  {
    float t = abs(sin(i * degrees2radians) - (isinTable8[i] / 255.0));
    if (t > m) m = t;
  }
  fprintf(stderr,"%2.4f\n", m);
  assertEqualFloat(0, m, 0.01);
}

unittest_main()

// --------
