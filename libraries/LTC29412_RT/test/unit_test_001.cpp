//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-20
// PURPOSE: unit tests for the LTC2942 library
//     URL: https://github.com/RobTillaart/LTC2942_RT
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


#include "LTC2942.h"


unittest_setup()
{
  fprintf(stderr, "LTC2942_LIB_VERSION: %s\n", (char *) LTC2942_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants_error)
{
  assertEqual(0x00, LTC2942_OK             );
  assertEqual(0x10, LTC2942_NOT_READY      );
  assertEqual(0x11, LTC2942_REQUEST_ERROR1 );
  assertEqual(0x12, LTC2942_REQUEST_ERROR2 );
  assertEqual(0x13, LTC2942_CONTROL_ERROR  );
  assertEqual(0x14, LTC2942_RSENSE_ERROR   );
  assertEqual(0x15, LTC2942_MAH_ERROR      );
  assertEqual(0x16, LTC2942_PRESCALER_ERROR);
  assertEqual(0xFF, LTC2942_OTHER_ERROR    );
}


unittest(test_constants_status)
{
  assertEqual(0x01, LTC2942_ALERT_UNDERVOLTAGE );
  assertEqual(0x02, LTC2942_ALERT_VOLTAGE      );
  assertEqual(0x04, LTC2942_ALERT_CHARGE_LOW   );
  assertEqual(0x08, LTC2942_ALERT_CHARGE_HIGH  );
  assertEqual(0x10, LTC2942_ALERT_TEMPERATURE  );
  assertEqual(0x20, LTC2942_ALERT_UNDEROVERFLOW);
  assertEqual(0x80, LTC2942_CHIP_ID            );
}


unittest(test_constructor)
{
  LTC2942 LTC;

  assertEqual(0x64, LTC.getAddress());
  assertEqual(LTC2942_OK, LTC.getLastError());
  assertEqual(128, LTC.getPrescaler());
  assertEqualFloat(1, LTC.getMaxCurrent(), 0.001);
}


unittest_main()


//  -- END OF FILE --

