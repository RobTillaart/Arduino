//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-28
// PURPOSE: unit tests for the MAX7219 library
//          https://github.com/RobTillaart/MATRIX7219
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
#include "MATRIX7219.h"


unittest_setup()
{
  fprintf(stderr, "MATRIX7219_LIB_VERSION: %s\n", (char *) MATRIX7219_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  MATRIX7219 mx(3, 4, 5, 1);
  assertEqual(1, mx.getMatrixCount());
}


unittest(test_layout)
{
  MATRIX7219 mx(3, 4, 5, 1);

  assertFalse(mx.getInvert());
  assertFalse(mx.getReverse());
  assertFalse(mx.getSwap());

  mx.setInvert(true);
  mx.setReverse(true);
  mx.setSwap(true);

  assertTrue(mx.getInvert());
  assertTrue(mx.getReverse());
  assertTrue(mx.getSwap());
}


unittest_main()


//  -- END OF FILE --

