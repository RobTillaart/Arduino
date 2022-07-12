//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-07-12
// PURPOSE: unit tests for SparseMatrix library
//          https://github.com/RobTillaart/SparseMatrix
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
#include "SparseMatrix.h"



unittest_setup()
{
  fprintf(stderr, "SPARSEMATRIX_LIB_VERSION: %s\n", (char*) SPARSEMATRIX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  SparseMatrix sm(10);
  assertEqual(10, sm.size());
  assertEqual(0, sm.count());
}


unittest(test_set)
{
  SparseMatrix sm(10);
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.set(i, i, 1.0 * i * i));
    assertEqual(i+1, sm.count());
  }
  assertFalse(sm.set(3,4,5));   //  don't fit any more...
}


unittest(test_get)
{
  SparseMatrix sm(10);
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.set(i, i, 1.0 * i * i));
    assertEqualFloat(1.0 * i * i, sm.get(i, i), 0.001);
  }
  assertFalse(sm.set(3,4,5));   //  don't fit any more...
}


unittest(test_sum)
{
  SparseMatrix sm(10);
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.set(i, i, 10));
  }
  assertEqualFloat(100, sm.sum(), 0.0001);
}


unittest_main()


// -- END OF FILE --
