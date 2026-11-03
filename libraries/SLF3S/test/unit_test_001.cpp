//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-11-02
// PURPOSE: unit tests for the SLF3S library
//     URL: https://github.com/RobTillaart/SLF3S
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


#include "SLF3S.h"


unittest_setup()
{
  fprintf(stderr, "SLF3S_LIB_VERSION: %s\n", (char *) SLF3S_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, SLF3S_OK        );
  assertEqual(0x01, SLF3S_CRC_ERROR );
  assertEqual(0x10, SLF3S_NOT_READY );
  assertEqual(0x11, SLF3S_NO_REQUEST);
}


unittest(test_constructor)
{
  SLF3S slf;

  assertEqual(0x08, slf.getAddress());
  assertEqual(SLF3S_OK, slf.getLastError());

  //  default false, as there is no request.
  assertFalse(slf.isReady());
  assertEqual(SLF3S_NO_REQUEST, slf.getLastError());
  //  error should reset
  assertEqual(SLF3S_OK, slf.getLastError());

  //  no data so all zero.
  assertEqualFloat(0.0f, slf.getFlow(), 0.01f);
  assertEqualFloat(0.0f, slf.getTemperature(), 0.01f);
  assertEqual(0, slf.getSignalFlags());
}


unittest_main()


//  -- END OF FILE --

