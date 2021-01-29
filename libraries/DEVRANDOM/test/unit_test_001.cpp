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
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", DEVRANDOM_LIB_VERSION);

  DEVRANDOM dr;
  
  assertEqual(DEVRANDOM_MODE_SW, dr.getMode());
  
  dr.useHW(4);
  assertEqual(DEVRANDOM_MODE_HW, dr.getMode());
  
  dr.useAR(0);
  assertEqual(DEVRANDOM_MODE_AR, dr.getMode());
  
  dr.useSW();
  assertEqual(DEVRANDOM_MODE_SW, dr.getMode());
}


unittest(test_constructor_seed)
{
  DEVRANDOM dr_str("hello world");
  assertEqual(DEVRANDOM_MODE_SW, dr_str.getMode());

  DEVRANDOM dr_int((uint32_t)123456789);
  assertEqual(DEVRANDOM_MODE_SW, dr_int.getMode());

  DEVRANDOM dr_float((float)PI);
  assertEqual(DEVRANDOM_MODE_SW, dr_float.getMode());

}


unittest(test_generator_mode)
{
  DEVRANDOM dr;

  assertEqual(1, dr.available());

  fprintf(stderr, "peak == read test\n");
  for (int i = 0; i < 10; i++)
  {
    int n = dr.peek();
    fprintf(stderr,"\t%d\t%d\n", i, n);
    assertEqual(n, dr.read());
  }
}

unittest_main()

// --------
