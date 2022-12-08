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
  fprintf(stderr, "FAST_TRIG_LIB_VERSION: %s\n", (char *) FAST_TRIG_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_sinTable16)
{
  fprintf(stderr,"Table16 error is < 0.1%% \n");
  const float degrees2radians = PI / 180.0;
  for (int i = 0; i < 91; i++)
  {
    assertEqualFloat(sin(i * degrees2radians), sinTable16[i] / 65535.0, 0.001);
  }
}


unittest(test_sinTable8)
{
  fprintf(stderr,"Table8 error is < 1.0%% \n");
  const float degrees2radians = PI / 180.0;
  for (int i = 0; i < 91; i++)
  {
    assertEqualFloat(sin(i * degrees2radians), sinTable8[i] / 255.0, 0.01);
  }
}


unittest(test_max_error_table16)
{
  const float degrees2radians = PI / 180.0;
  float maxError = 0;
  for (int i = 0; i < 91; i++)
  {
    float t = abs(sin(i * degrees2radians) - (sinTable16[i] / 65535.0));
    if (t > maxError) maxError = t;
  }
  fprintf(stderr,"Table16 max error: %2.5f\n", maxError);
  assertEqualFloat(0, maxError, 0.001);
}


unittest(test_max_error_table8)
{
  const float degrees2radians = PI / 180.0;
  float maxError = 0;
  for (int i = 0; i < 91; i++)
  {
    float t = abs(sin(i * degrees2radians) - (sinTable8[i] / 255.0));
    if (t > maxError) maxError = t;
  }
  fprintf(stderr,"Table8 max error: %2.5f\n", maxError);
  assertEqualFloat(0, maxError, 0.01);
}


unittest(test_atanFast)
{
  for (float x = -10; x < 10; x += 0.1)
  {
    assertEqualFloat(atanFast(x), atan(x), 0.001);
  }
}

unittest_main()

// --------
