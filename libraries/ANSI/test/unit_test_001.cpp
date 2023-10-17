//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-11
// PURPOSE: unit tests for the Arduino ANSI library
//          https://github.com/RobTillaart/ANSI
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
#include "ansi.h"


unittest_setup()
{
  fprintf(stderr, "ANSI_LIB_VERSION: %s\n", (char *) ANSI_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  ANSI ansi(&Serial);
  assertEqual(12, ansi.println("1234567890") );

  VT100 vt(&Serial);
  assertEqual(10, vt.print("1234567890") );
}


unittest(test_gray2color)
{
  ANSI ansi(&Serial);

  for (int gray = 0; gray < 255; gray += 31)
  {
    int color = ansi.gray2color(gray);
    assertEqual(232 + gray * 3 / 32, color);
  }
}


unittest_main()

//  -- END OF FILE --
