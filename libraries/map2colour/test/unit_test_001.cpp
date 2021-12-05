//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-12-04
// PURPOSE: unit tests for the map2colour library
//          https://github.com/RobTillaart/map2colour
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
#include "map2colour.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor_I)
{
  fprintf(stderr, "MAP2COLOUR_LIB_VERSION: %s\n", (char *) MAP2COLOUR_LIB_VERSION);

  map2colour mc;

  float values[7] = { 1, 2, 3, 4, 5, 6, 7 };
  assertTrue(mc.begin(values));

  assertEqual(0x00000000, mc.map2RGB(1));
  assertEqual(0x00FF0000, mc.map2RGB(2));
  assertEqual(0x00FFFF00, mc.map2RGB(3));
  assertEqual(0x0000FF00, mc.map2RGB(4));
  assertEqual(0x0000FFFF, mc.map2RGB(5));
  assertEqual(0x000000FF, mc.map2RGB(6));
  assertEqual(0x00FFFFFF, mc.map2RGB(7));
}

unittest(test_constructor_II)
{
  fprintf(stderr, "MAP2COLOUR_LIB_VERSION: %s\n", (char *) MAP2COLOUR_LIB_VERSION);

  map2colour mc;

  float values[7] = { 1, 2, 3, 4, 5, 6, 7 };
  uint32_t colours[7] = 
  {
    M2C_WHITE, M2C_BLACK, M2C_FUCHSIA, M2C_OLIVE, M2C_NAVY, M2C_GREEN, M2C_YELLOW
  };
  assertTrue(mc.begin(values, colours));

  assertEqual(M2C_WHITE,   mc.map2RGB(1));
  assertEqual(M2C_BLACK,   mc.map2RGB(2));
  assertEqual(M2C_FUCHSIA, mc.map2RGB(3));
  assertEqual(M2C_OLIVE,   mc.map2RGB(4));
  assertEqual(M2C_NAVY,    mc.map2RGB(5));
  assertEqual(M2C_GREEN,   mc.map2RGB(6));
  assertEqual(M2C_YELLOW,  mc.map2RGB(7));
}



unittest(test_constants)
{
  fprintf(stderr, "MAP2COLOUR_LIB_VERSION: %s\n", (char *) MAP2COLOUR_LIB_VERSION);

  assertEqual(M2C_BLACK   ,0x00000000);
  assertEqual(M2C_SILVER  ,0x00C0C0C0);
  assertEqual(M2C_GRAY    ,0x00808080);
  assertEqual(M2C_WHITE   ,0x00FFFFFF);
  assertEqual(M2C_MAROON  ,0x00800000);
  assertEqual(M2C_RED     ,0x00FF0000);
  assertEqual(M2C_PURPLE  ,0x00800080);
  assertEqual(M2C_FUCHSIA ,0x00FF00FF);
  assertEqual(M2C_GREEN   ,0x00008000);
  assertEqual(M2C_LIME    ,0x000FF000);
  assertEqual(M2C_OLIVE   ,0x00808000);
  assertEqual(M2C_YELLOW  ,0x00FFFF00);
  assertEqual(M2C_NAVY    ,0x00000080);
  assertEqual(M2C_BLUE    ,0x000000FF);
  assertEqual(M2C_TEAL    ,0x00008080);
  assertEqual(M2C_AQUA    ,0x0000FFFF);
}



unittest_main()


// -- END OF FILE --
