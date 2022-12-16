//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-08-13
// PURPOSE: unit tests for the PIR current sensor
//          https://github.com/RobTillaart/PIR
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
#include "PIR.h"


unittest_setup()
{
  fprintf(stderr, "PIR_LIB_VERSION: %s\n", (char *) PIR_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, PIR_OK);
  assertEqual(0xFF, PIR_ERR_NO_SENSOR);
  assertEqual(0xFE, PIR_ERR_ARRAY_FULL);
  assertEqual(0xFD, PIR_ERR_INDEX);
}


unittest(test_add)
{
  PIR P;

  for (int i = 0; i < 8; i++)
  {
    assertEqual(i, P.add(i + 2));
  }

  assertEqual(PIR_ERR_ARRAY_FULL, P.add(10));
}


unittest(test_count)
{
  PIR P;

  assertEqual(0, P.count());
  for (int i = 0; i < 8; i++)
  {
    P.add(i+2);
    assertEqual(i+1, P.count());
  }

  P.add(10);
  assertEqual(8, P.count());
}


unittest(test_read)
{
  PIR P;

  //  no PIR added yet
  uint8_t x = P.read();
  assertEqual(0, x);
  uint8_t y = P.lastValue();
  assertEqual(x, y);
  
  P.add(3);
  x = P.read();
  assertEqual(0, x);
  y = P.lastValue();
  assertEqual(x, y);
}


unittest(test_single_read)
{
  PIR P;

  //  no PIR added yet => error
  uint8_t x = P.read(0);
  assertEqual((int)PIR_ERR_NO_SENSOR, x);

  P.add(3);
  x = P.read(0);
  assertNotEqual((int)PIR_ERR_INDEX, x);
}


unittest_main()


// -- END OF FILE --
