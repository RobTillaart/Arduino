//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-xx-xx
// PURPOSE: unit tests for the DCT532 library
//     URL: https://github.com/RobTillaart/DCT532
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
#include "DCT532.h"


unittest_setup()
{
  fprintf(stderr, "DCT532_LIB_VERSION: %s\n", (char *) DCT532_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual( 0, DCT532_OK);
  assertEqual(-1, DCT532_REQUEST_ERROR);
}


unittest(test_constructor)
{
  DCT532 dct(0x28);

  //  defaults before begin()
  assertEqual(0x28, dct.getAddress());
  assertEqual(   0, dct.lastRead());
  assertEqual(   0, dct.getPressure());
  assertEqual(   0, dct.getTemperature());
  assertEqual(   0, dct.getLastError());

  //  TODO
}


unittest_main()


//  -- END OF FILE --

