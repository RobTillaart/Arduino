//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-02
// PURPOSE: unit tests for the SWSerialOut library
//          https://github.com/RobTillaart/SWSerialOut
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
#include "SWSerialOut.h"





unittest_setup()
{
  fprintf(stderr, "SWSERIALOUT_LIB_VERSION: %s\n", (char *) SWSERIALOUT_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


unittest(test_constructor)
{
  SWSerialOut SWSO(7);
  SWSO.begin(9600);

  assertEqual(1,1);
}


unittest_main()


//  -- END OF FILE --

