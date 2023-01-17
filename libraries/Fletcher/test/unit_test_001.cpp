//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-25
// PURPOSE: unit tests for the GAMMA library
//          https://github.com/RobTillaart/GAMMA
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
#include "Fletcher.h"
#include "Fletcher16.h"
#include "Fletcher32.h"
#include "Fletcher64.h"



unittest_setup()
{
  fprintf(stderr, "FLETCHER_LIB_VERSION: %s\n", (char *) FLETCHER_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(FLETCHER_16, 255);
  assertEqual(FLETCHER_32, 65535UL);
  assertEqual(FLETCHER_64, 4294967295ULL);
}


unittest(test_fletcher16)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";

  assertEqual(51440UL, fletcher16((uint8_t *) str1, 5));
  assertEqual( 8279UL, fletcher16((uint8_t *) str2, 6));
  assertEqual( 1575UL, fletcher16((uint8_t *) str3, 8));
}


unittest(test_fletcher32)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";

  assertEqual(4031760169UL, fletcher32((uint16_t *) str1, 3));
  assertEqual(1448095018UL, fletcher32((uint16_t *) str2, 3));
  assertEqual(3957429649UL, fletcher32((uint16_t *) str3, 4));
}


unittest(test_fletcher64)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";

  assertEqual(14467467625952928454ULL, fletcher64((uint32_t *) str1, 2));
  assertEqual(14467579776138987718ULL, fletcher64((uint32_t *) str2, 2));
  assertEqual( 3543817411021686982ULL, fletcher64((uint32_t *) str3, 2));
}


unittest(test_FF_1)
{
  uint8_t x[1]  = { 0xFF };
  uint16_t y[1] = { 0xFFFF };
  uint32_t z[1] = { 0xFFFFFFFF };

  assertEqual(0, fletcher16(x, 1));
  assertEqual(0, fletcher32(y, 1));
  assertEqual(0, fletcher64(z, 1));
}


unittest(test_FF_2)
{
  uint8_t x[1]  = { 0xFF };
  uint16_t y[1] = { 0xFFFF };
  uint32_t z[1] = { 0xFFFFFFFF };

  Fletcher16 FL16;
  FL16.begin();
  assertEqual(0, FL16.getFletcher());
  FL16.begin(0xFF, 0);
  assertEqual(0, FL16.getFletcher());
  FL16.add(0xFF);
  assertEqual(0, FL16.getFletcher());
  FL16.add(0xFF);
  assertEqual(0, FL16.getFletcher());

  Fletcher32 FL32;
  FL32.begin();
  assertEqual(0, FL32.getFletcher());
  FL32.begin(0xFFFF, 0);
  assertEqual(0, FL32.getFletcher());
  FL32.add(0xFFFF);
  assertEqual(0, FL32.getFletcher());
  FL32.add(0xFFFF);
  assertEqual(0, FL32.getFletcher());

  Fletcher64 FL64;
  FL64.begin();
  assertEqual(0, FL64.getFletcher());
  FL64.begin(0xFFFFFFFF, 0);
  assertEqual(0, FL64.getFletcher());
  FL64.add(0xFFFFFFFF);
  assertEqual(0, FL64.getFletcher());
  FL64.add(0xFFFFFFFF);
  assertEqual(0, FL64.getFletcher());
}


unittest_main()

// --------
