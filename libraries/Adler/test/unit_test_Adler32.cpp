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
#include "Adler32.h"


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
  fprintf(stderr, "ADLER32_LIB_VERSION: %s\n", (char *) ADLER32_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(ADLER32_MOD_PRIME, 65521);
}


unittest(test_ADLER32_lorem)
{
  Adler32 ad32;

  ad32.begin();

  fprintf(stderr, "strlen lorem\n");
  assertEqual(868, strlen(lorem));

  for (int i = 0; lorem[i] != 0; i++)
  {
    ad32.add(lorem[i]);
  }
  assertEqual(3972480156, ad32.getAdler());
  assertEqual(868, ad32.count());

  ad32.begin();
  assertEqual(3972480156, ad32.add(lorem, strlen(lorem)));
  assertEqual(3972480156, ad32.getAdler());
  assertEqual(868, ad32.count());

  ad32.begin();
  assertEqual(3972480156, ad32.addFast(lorem, strlen(lorem)));
  assertEqual(3972480156, ad32.getAdler());
  assertEqual(868, ad32.count());
}


unittest_main()


//  -- END OF FILE --

