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
  assertEqual('-', u[18]);
  assertEqual('-', u[23]);
}



unittest_main()


// --------

