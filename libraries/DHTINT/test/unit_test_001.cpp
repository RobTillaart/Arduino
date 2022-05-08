//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-05-08
// PURPOSE: unit tests for the DHT temperature and humidity sensor
//          https://github.com/RobTillaart/DHTINT
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
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

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "dhtint.h"


unittest_setup()
{
  fprintf(stderr, "DHTINT_LIB_VERSION: %s\n", (char *) DHTINT_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual( 0, DHTLIB_OK                    );
  assertEqual(-1, DHTLIB_ERROR_CHECKSUM        );
  assertEqual(-2, DHTLIB_ERROR_TIMEOUT_A       );
  assertEqual(-3, DHTLIB_ERROR_BIT_SHIFT       );
  assertEqual(-4, DHTLIB_ERROR_SENSOR_NOT_READY);
  assertEqual(-5, DHTLIB_ERROR_TIMEOUT_C       );
  assertEqual(-6, DHTLIB_ERROR_TIMEOUT_D       );
  assertEqual(-7, DHTLIB_ERROR_TIMEOUT_B       );
  assertEqual(-8, DHTLIB_WAITING_FOR_READ      );
  
  assertEqual(-100, DHTLIB_HUMIDITY_OUT_OF_RANGE   );
  assertEqual(-101, DHTLIB_TEMPERATURE_OUT_OF_RANGE);
  
  assertEqual(-999, DHTLIB_INVALID_VALUE);
}


unittest(test_constructor)
{
  DHTINT dht(4);

  // verify default flags
  // assertEqual(0, dht.getType());     // calls read which blocks.
  assertEqual(0, dht.getHumOffset());
  assertEqual(0, dht.getTempOffset());
  #if defined(__AVR__)
  fprintf(stderr, "__AVR__ defined.");
  assertFalse(dht.getDisableIRQ());
  #else
  fprintf(stderr, "__AVR__ not defined.");
  assertTrue(dht.getDisableIRQ());
  #endif
  assertFalse(dht.getWaitForReading());
  assertEqual(0, dht.getReadDelay());
  assertFalse(dht.getSuppressError());
}


unittest(test_hum_temp)
{
  DHTINT dht(4);

  assertEqual(0, dht.getHumidity());
  assertEqual(0, dht.getHumOffset());
  dht.setHumOffset(2);
  assertEqual(2, dht.getHumOffset());
  
  assertEqual(0, dht.getTemperature());
  assertEqual(0, dht.getTempOffset());
  dht.setTempOffset(-3);
  assertEqual(-3, dht.getTempOffset());
}


unittest(test_process_flags)
{
  DHTINT dht(4);

  dht.setType(11);
  assertEqual(11, dht.getType());
  dht.setType(22);
  assertEqual(22, dht.getType());
  
  dht.setDisableIRQ(true);
  assertTrue(dht.getDisableIRQ());
  dht.setDisableIRQ(false);
  assertFalse(dht.getDisableIRQ());
  
  dht.setWaitForReading(true);
  assertTrue(dht.getWaitForReading());
  dht.setWaitForReading(false);
  assertFalse(dht.getWaitForReading());
  
  dht.setReadDelay(1500);
  assertEqual(1500, dht.getReadDelay());
  dht.setType(11);
  dht.setReadDelay();
  assertEqual(0, dht.getReadDelay());
  dht.setType(22);
  dht.setReadDelay();
  assertEqual(0, dht.getReadDelay());
  
  dht.setSuppressError(true);
  assertTrue(dht.getSuppressError());
  dht.setSuppressError(false);
  assertFalse(dht.getSuppressError());
}


unittest(test_read)
{
  DHTINT dht(4);

  fprintf(stderr, "\tread() cannot be tested  GODMODE?\n");
  // int rc = dht.read();
  // fprintf(stderr, "%d\n", rc);
  
  long lr = dht.lastRead();
  fprintf(stderr, "\ttime since lastRead %ld\n", lr);
}

unittest_main()

// --------
