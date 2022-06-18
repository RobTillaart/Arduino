//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the AM232X temperature and humidity sensor
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

#include "Arduino.h"
#include "AM232X.h"


unittest_setup()
{
  fprintf(stderr, "AM232X_LIB_VERSION: %s\n", (char *) AM232X_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(  0, AM232X_OK                  );
  assertEqual(-10, AM232X_ERROR_UNKNOWN       );
  assertEqual(-11, AM232X_ERROR_CONNECT       );
  assertEqual(-12, AM232X_ERROR_FUNCTION      );
  assertEqual(-13, AM232X_ERROR_ADDRESS       );
  assertEqual(-14, AM232X_ERROR_REGISTER      );
  assertEqual(-15, AM232X_ERROR_CRC_1         );
  assertEqual(-16, AM232X_ERROR_CRC_2         );
  assertEqual(-17, AM232X_ERROR_WRITE_DISABLED);
  assertEqual(-18, AM232X_ERROR_WRITE_COUNT   );
  assertEqual(-19, AM232X_MISSING_BYTES       );
  assertEqual(-20, AM232X_READ_TOO_FAST       );
}


unittest(test_AM232X_constructor)
{
  AM232X AM;
  Wire.begin();

  assertTrue(AM.begin());
  assertTrue(AM.isConnected());   // TODO - GODMODE

  assertEqual(0, AM.lastRead());
  // assertEqual(-10, AM.read());
}


unittest(test_AM232X_read_delay)
{
  AM232X AM;
  Wire.begin();

  assertTrue(AM.begin());
  assertTrue(AM.isConnected());   // TODO - GODMODE

  assertEqual(0, AM.lastRead());
  // assertEqual(-10, AM.read());

  // default 2000
  assertEqual(2000, AM.getReadDelay());
  AM.setReadDelay(3000);
  assertEqual(3000, AM.getReadDelay());
  // set readDelay to 0 will reset to datasheet value
  AM.setReadDelay(0);
  assertEqual(2000, AM.getReadDelay());
}


unittest(test_AM232X_hum_temp)
{
  AM232X AM;

  assertEqualFloat(0, AM.getHumidity(), 0.001);
  assertEqualFloat(0, AM.getHumOffset(), 0.001);
  AM.setHumOffset(1.5);
  assertEqualFloat(1.5, AM.getHumOffset(), 0.001);
  
  assertEqualFloat(0, AM.getTemperature(), 0.001);
  assertEqualFloat(0, AM.getTempOffset(), 0.001);
  AM.setTempOffset(-1.5);
  assertEqualFloat(-1.5, AM.getTempOffset(), 0.001);
}


unittest(test_hum_AM2320_temp)
{
  AM2320 AM;

  assertEqualFloat(0, AM.getHumidity(), 0.001);
  assertEqualFloat(0, AM.getHumOffset(), 0.001);
  AM.setHumOffset(1.5);
  assertEqualFloat(1.5, AM.getHumOffset(), 0.001);
  
  assertEqualFloat(0, AM.getTemperature(), 0.001);
  assertEqualFloat(0, AM.getTempOffset(), 0.001);
  AM.setTempOffset(-1.5);
  assertEqualFloat(-1.5, AM.getTempOffset(), 0.001);
}


unittest(test_hum_AM2321_temp)
{
  AM2321 AM;

  assertEqualFloat(0, AM.getHumidity(), 0.001);
  assertEqualFloat(0, AM.getHumOffset(), 0.001);
  AM.setHumOffset(1.5);
  assertEqualFloat(1.5, AM.getHumOffset(), 0.001);
  
  assertEqualFloat(0, AM.getTemperature(), 0.001);
  assertEqualFloat(0, AM.getTempOffset(), 0.001);
  AM.setTempOffset(-1.5);
  assertEqualFloat(-1.5, AM.getTempOffset(), 0.001);
}


unittest(test_AM2322_hum_temp)
{
  AM2322 AM;

  assertEqualFloat(0, AM.getHumidity(), 0.001);
  assertEqualFloat(0, AM.getHumOffset(), 0.001);
  AM.setHumOffset(1.5);
  assertEqualFloat(1.5, AM.getHumOffset(), 0.001);
  
  assertEqualFloat(0, AM.getTemperature(), 0.001);
  assertEqualFloat(0, AM.getTempOffset(), 0.001);
  AM.setTempOffset(-1.5);
  assertEqualFloat(-1.5, AM.getTempOffset(), 0.001);
}


unittest(test_AM232X_surpress_error)
{
  AM232X AM;

  Wire.begin();

  assertTrue(AM.begin());
  assertTrue(AM.isConnected());

  assertFalse(AM.getSuppressError());
  AM.setSuppressError(true);
  assertTrue(AM.getSuppressError());
  AM.setSuppressError(false);
  assertFalse(AM.getSuppressError());
}


unittest_main()

// --------
