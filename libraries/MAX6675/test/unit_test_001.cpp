//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-12
// PURPOSE: unit tests for the MAX31855_RT Thermocouple library
//          https://github.com/RobTillaart/MAX31855_RT
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "MAX6675.h"



unittest_setup()
{
  fprintf(stderr, "MAX6675_LIB_VERSION: %s\n", (char *) MAX6675_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, STATUS_OK);
  assertEqual(0x04, STATUS_ERROR);
  assertEqual(0x80, STATUS_NOREAD);
  assertEqual(0x81, STATUS_NO_COMMUNICATION);

  assertEqual(-999, MAX6675_NO_TEMPERATURE);
}


unittest(test_status)
{
  const int selectPin = 7;
  const int dataPin   = 6;
  const int clockPin  = 5;

  MAX6675 tc(selectPin, dataPin, clockPin);
  tc.begin();

  fprintf(stderr, "Status...\n");
  assertEqual(STATUS_NOREAD, (int)tc.getStatus());
  assertEqual(0, tc.lastRead());
  assertEqual(0, tc.getRawData());
}


unittest(test_temperature)
{
  const int selectPin = 7;
  const int dataPin   = 6;
  const int clockPin  = 5;

  MAX6675 tc(selectPin, dataPin, clockPin);
  tc.begin();

  fprintf(stderr, "Temperature...\n");
  assertEqualFloat(MAX6675_NO_TEMPERATURE, tc.getTemperature(), 0.001);

  fprintf(stderr, "\nOffset...\n");
  for (int of = 0; of < 10; of++)
  {
    tc.setOffset(of * 0.1);
    fprintf(stderr, "%f\t", of * 0.1);
    assertEqualFloat(of * 0.1, tc.getOffset(), 0.001);
  }
}


unittest(test_SPIspeed_SWSPIdelay)
{
  const int selectPin = 7;
  const int dataPin   = 6;
  const int clockPin  = 5;

  MAX6675 tc(selectPin, dataPin, clockPin);
  tc.begin();

  fprintf(stderr, "SPIspeed...\n");
  for (uint32_t sp = 100000; sp <= 1000000; sp += 100000)
  {
    tc.setSPIspeed(sp);
    fprintf(stderr, "%lu\t", sp);
    assertEqual(sp, tc.getSPIspeed());
  }

  fprintf(stderr, "\nsetSWSPIdelay...\n");
  for (uint16_t del = 0; del < 11; del++)
  {
    tc.setSWSPIdelay(del);
    fprintf(stderr, "%d\t", del);
    assertEqual(del, tc.getSWSPIdelay());
  }
}


unittest_main()


// -- END OF FILE --
