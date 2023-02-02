//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-06-14
// PURPOSE: unit tests for the UUID library
//          https://github.com/RobTillaart/UUID
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
#include "UUID.h"


unittest_setup()
{
  fprintf(stderr, "UUID_LIB_VERSION: %s\n", (char *) UUID_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, UUID_MODE_VARIANT4);
  assertEqual(1, UUID_MODE_RANDOM);
}


unittest(test_generate)
{
  UUID uuid;
  char u[40], v[40], w[40];
  
  uuid.generate();
  strcpy(u, uuid.toCharArray());
  assertEqual(36, strlen(u));

  strcpy(v, uuid.toCharArray());
  assertEqual(36, strlen(v));
  assertEqual(u, v);

  uuid.generate();
  strcpy(v, uuid.toCharArray());
  assertEqual(36, strlen(v));

  uuid.generate();
  strcpy(w, uuid.toCharArray());
  assertEqual(36, strlen(w));
  
  assertNotEqual(u, v);
  assertNotEqual(u, w);
  assertNotEqual(w, v);
}


unittest(test_layout)
{
  UUID uuid;
  char u[40];
  
  uuid.generate();
  strcpy(u, uuid.toCharArray());
  fprintf(stderr, ">%s<\n", uuid.toCharArray());
  assertEqual(36, strlen(u));

  assertEqual('-', u[8]);
  assertEqual('-', u[13]);
  assertEqual('4', u[15]);
  assertEqual('-', u[18]);
  assertEqual('-', u[23]);
}


unittest(test_mode)
{
  UUID uuid;

  assertEqual(UUID_MODE_VARIANT4, uuid.getMode());
  uuid.setRandomMode();
  assertEqual(UUID_MODE_RANDOM, uuid.getMode());
  uuid.setVariant4Mode();
  assertEqual(UUID_MODE_VARIANT4, uuid.getMode());
}


unittest(test_printTo)
{
  UUID uuid;

  assertEqual(36, Serial.print(uuid));    // 36
  assertEqual(38, Serial.println(uuid));  // 36 + \n\r
}



unittest_main()


//  -- END OF FILE --

