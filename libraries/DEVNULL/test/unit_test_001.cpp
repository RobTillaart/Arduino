//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-18
// PURPOSE: unit tests for the DEVNULL library
//          https://github.com/RobTillaart/
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


#include "DEVNULL.h"


unittest_setup()
{
  fprintf(stderr, "DEVNULL_LIB_VERSION: %s\n", (char *) DEVNULL_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_all)
{
  DEVNULL dn;

  assertEqual(0,   dn.available());
  assertEqual(EOF, dn.peek());
  assertEqual(EOF, dn.read());

  assertEqual(1,   dn.write('a'));
  assertEqual('a', dn.lastByte());

  assertEqual(11,  dn.print("hello world"));
  assertEqual('d', dn.lastByte());
  assertEqual(13,  dn.println("hello world"));
  assertEqual(10,  dn.lastByte());  //  10 == newline
}

unittest_main()

// --------
