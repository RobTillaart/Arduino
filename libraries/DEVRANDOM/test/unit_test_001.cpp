//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-18
// PURPOSE: unit tests for the DEVRANDOM library
//          https://github.com/RobTillaart/DEVRANDOM
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
#include "DEVRANDOM.h"


unittest_setup()
{
  fprintf(stderr, "DEVRANDOM_LIB_VERSION: %s\n", (char *) DEVRANDOM_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, DEVRANDOM_MODE_RANDOM);
  assertEqual(1, DEVRANDOM_MODE_DIGITALREAD);
  assertEqual(2, DEVRANDOM_MODE_ANALOGREAD);
  assertEqual(3, DEVRANDOM_MODE_MARSAGLIA);
}


unittest(test_constructor)
{
  DEVRANDOM dr;

  assertEqual(DEVRANDOM_MODE_RANDOM, dr.getMode());

  dr.useDigitalRead(4);
  assertEqual(DEVRANDOM_MODE_DIGITALREAD, dr.getMode());

  dr.useAnalogRead(0);
  assertEqual(DEVRANDOM_MODE_ANALOGREAD, dr.getMode());

  dr.useMarsaglia();
  assertEqual(DEVRANDOM_MODE_MARSAGLIA, dr.getMode());

  dr.useRandom();
  assertEqual(DEVRANDOM_MODE_RANDOM, dr.getMode());
}


unittest(test_constructor_seed)
{
  DEVRANDOM dr_str("hello world");
  assertEqual(DEVRANDOM_MODE_RANDOM, dr_str.getMode());

  DEVRANDOM dr_int((uint32_t)123456789);
  assertEqual(DEVRANDOM_MODE_RANDOM, dr_int.getMode());

  DEVRANDOM dr_float((float)PI);
  assertEqual(DEVRANDOM_MODE_RANDOM, dr_float.getMode());

}


unittest(test_read)
{
  DEVRANDOM dr;
  assertEqual(1, dr.available());

  fprintf(stderr, "read() >= 0test\n");
  for (int i = 0; i < 10; i++)
  {
    assertLessOrEqual(0, dr.read());
  }
}


unittest(test_generator_mode_random)
{
  DEVRANDOM dr;

  assertEqual(1, dr.available());

  fprintf(stderr, "peek() == read() test\n");
  for (int i = 0; i < 10; i++)
  {
    int n = dr.peek();
    fprintf(stderr,"\t%d\t%d\n", i, n);
    assertEqual(n, dr.read());
  }
}


unittest(test_generator_mode_Marsaglia)
{
  DEVRANDOM dr;
  dr.useMarsaglia();

  assertEqual(1, dr.available());

  fprintf(stderr, "peek() == read() test\n");
  for (int i = 0; i < 10; i++)
  {
    int n = dr.peek();
    fprintf(stderr,"\t%d\t%d\n", i, n);
    assertEqual(n, dr.read());
  }
}


unittest_main()

// --------
