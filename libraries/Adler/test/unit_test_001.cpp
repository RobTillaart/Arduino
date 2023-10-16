//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-25
// PURPOSE: unit tests for the Adler library
//          https://github.com/RobTillaart/Adler
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
#include "Adler.h"


char lorem[] = "Lorem ipsum dolor sit amet, \
consectetuer adipiscing elit. Aenean commodo ligula eget dolor. \
Aenean massa. Cum sociis natoque penatibus et magnis dis parturient \
montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, \
pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. \
Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. \
In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. \
Nullam dictum felis eu pede mollis pretium. Integer tincidunt. \
Cras dapibus. Vivamus elementum semper nisi. \
Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, \
consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, \
viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus \
varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies \
nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui.";


unittest_setup()
{
  fprintf(stderr, "ADLER_LIB_VERSION: %s\n", (char *) ADLER_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(ADLER16_MOD_PRIME, 251);
  assertEqual(ADLER32_MOD_PRIME, 65521);
}


unittest(test_adler_static)
{
  char str1[24] = "abcde";
  char str2[24] = "abcdef";
  char str3[24] = "abcdefgh";

  assertEqual(96993776, adler32((uint8_t *) str1, 5));
  assertEqual(136184406, adler32((uint8_t *) str2, 6));
  assertEqual(234881829, adler32((uint8_t *) str3, 8));

  assertEqual(57845, adler16((uint8_t *) str1, 5));
  assertEqual(18016, adler16((uint8_t *) str2, 6));
  assertEqual(17972, adler16((uint8_t *) str3, 8));

  assertEqual(96993776, adler32(str1, 5));
  assertEqual(136184406, adler32(str2, 6));
  assertEqual(234881829, adler32(str3, 8));

  assertEqual(57845, adler16(str1, 5));
  assertEqual(18016, adler16(str2, 6));
  assertEqual(17972, adler16(str3, 8));
}


unittest_main()


//  -- END OF FILE --

