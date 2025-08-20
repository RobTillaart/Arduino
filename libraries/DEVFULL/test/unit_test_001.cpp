//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-11
// PURPOSE: unit tests for the DEVFULL library
//          https://github.com/RobTillaart/DEVFULL
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


#include "DEVFULL.h"


unittest_setup()
{
  fprintf(stderr, "DEVFULL_LIB_VERSION: %s\n", (char *) DEVFULL_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_all)
{
  DEVFULL df;

  assertEqual(INT_MAX, df.available());
  assertEqual(0x0000, df.peek());
  assertEqual(0x0000, df.read());
  assertEqual(-28, df.write('a'));
  assertEqual(-28, df.write((const uint8_t*) "hello\n", 6));
  assertEqual(-28, df.print("hello world"));
  assertEqual(-56, df.println("hello world"));   //  -56 ==> two underlying write calls...
}

unittest_main()


//  -- END OF FILE --

