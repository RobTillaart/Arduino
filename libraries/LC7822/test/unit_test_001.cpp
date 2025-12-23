//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-20
// PURPOSE: unit tests for the LC7822 library
//     URL: https://github.com/RobTillaart/LC7822
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
#include "LC7822.h"


unittest_setup()
{
  fprintf(stderr, "LC7822_LIB_VERSION: %s\n", (char *) LC7822_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  LC7821 LC21(4,5,6,7);  //  no reset Pin
  assertTrue(LC21.begin());
  assertFalse(LC21.reset());
  assertEqual(LC21.getAddress(), 0x0B);
  assertTrue(LC21.begin(0x0A));
  assertEqual(LC21.getAddress(), 0x0A);
  fprintf(stderr, "\n");

  LC7822 LC22(4,5,6,7);  //  no reset Pin
  assertTrue(LC22.begin());
  assertFalse(LC22.reset());
  assertEqual(LC22.getAddress(), 0x0D);
  assertTrue(LC22.begin(0x0C));
  assertEqual(LC22.getAddress(), 0x0C);
  fprintf(stderr, "\n");

  LC7823 LC23(4,5,6,7);  //  no reset Pin
  assertTrue(LC23.begin());
  assertFalse(LC23.reset());
  assertEqual(LC23.getAddress(), 0x0F);
  assertTrue(LC23.begin(0x0E));
  assertEqual(LC23.getAddress(), 0x0E);
  fprintf(stderr, "\n");
}


unittest(test_setAll)
{
  LC7822 LC(4,5,6,7);  //  no reset Pin
  assertTrue(LC.begin());
  for (int i = 0; i <  255; i += 47)  //  only a few steps is sufficient.
  {
    LC.setAll(i);
    assertEqual(LC.getAll(), i);
  }
}


unittest(test_setSwitch)
{
  LC7822 LC(4,5,6,7);  //  no reset Pin
  assertTrue(LC.begin());
  for (int i = 0; i <  8; i++)
  {
    LC.setSwitch(i, 1);
    assertTrue(LC.getSwitch(i));
  }
  for (int i = 0; i <  8; i++)
  {
    LC.setSwitch(i, 0);
    assertFalse(LC.getSwitch(i));
  }
}


unittest(test_microDelay)
{
  LC7822 LC(4,5,6,7);  //  no reset Pin
  assertTrue(LC.begin());
  for (int i = 0; i <  5; i++)
  {
    LC.setMicroDelay(i);
    assertEqual(LC.getMicroDelay(), i);
  }
}


unittest_main()


//  -- END OF FILE --

