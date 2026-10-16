//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-18
// PURPOSE: unit tests for the LTC2941 library
//     URL: https://github.com/RobTillaart/LTC2941
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


#include "LTC2941.h"


unittest_setup()
{
  fprintf(stderr, "LTC2941_LIB_VERSION: %s\n", (char *) LTC2941_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants_error)
{
  assertEqual(0x00, LTC2941_OK             );
  assertEqual(0x10, LTC2941_NOT_READY      );
  assertEqual(0x11, LTC2941_REQUEST_ERROR1 );
  assertEqual(0x12, LTC2941_REQUEST_ERROR2 );
  assertEqual(0x13, LTC2941_CONTROL_ERROR  );
  assertEqual(0x14, LTC2941_RSENSE_ERROR   );
  assertEqual(0x15, LTC2941_MAH_ERROR      );
  assertEqual(0x16, LTC2941_PRESCALER_ERROR);
  assertEqual(0xFF, LTC2941_OTHER_ERROR    );
}


unittest(test_constants_status)
{
  assertEqual(0x01, LTC2941_ALERT_UNDERVOLTAGE );
  assertEqual(0x02, LTC2941_ALERT_BATTERY      );
  assertEqual(0x04, LTC2941_ALERT_CHARGE_LOW   );
  assertEqual(0x08, LTC2941_ALERT_CHARGE_HIGH  );
  assertEqual(0x20, LTC2941_ALERT_UNDEROVERFLOW);
  assertEqual(0x80, LTC2941_CHIP_ID            );
}


unittest(test_constructor)
{
  LTC2941 LTC;

  assertEqual(0x64, LTC.getAddress());
  assertEqual(LTC2941_OK, LTC.getLastError());
}


unittest_main()


//  -- END OF FILE --

