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


unittest(test_constants)
{
  assertEqual(1000, SPARSEMATRIX_MAX_SIZE);
}


unittest(test_constructor)
{
  SparseMatrix sm(10);
  assertEqual(10, sm.size());
  assertEqual(0, sm.count());

  SparseMatrix sm2(1100);
  assertEqual(1000, sm2.size());
}


unittest(test_set)
{
  SparseMatrix sm(10);
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.set(i, i, 1.0 * i * i));
    assertEqual(i, sm.count());
  }
  assertTrue(sm.set(3, 4, 5));
  assertFalse(sm.set(5, 4, 5));   //  don't fit any more...

  //  do not set new element to zero
  sm.clear();
  assertEqual(0, sm.count());

  sm.set(1, 2, 0);
  assertEqual(0, sm.count());
}


unittest(test_get)
{
  SparseMatrix sm(10);
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.set(i, i, 1.0 * i * i));
    assertEqualFloat(1.0 * i * i, sm.get(i, i), 0.001);
  }
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


unittest(test_add)
{
  SparseMatrix sm(10);
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.add(i, i, 1.0 * i * i));
    assertEqualFloat(1.0 * i * i, sm.get(i, i), 0.001);
  }
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.add(i, i, 1.0 * i * i));
    assertEqualFloat(2.0 * i * i, sm.get(i, i), 0.001);
  }
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sm.add(i, i, -2.0 * i * i));
    assertEqualFloat(0, sm.get(i, i), 0.001);
  }
  assertEqual(0, sm.count());
}


unittest(test_bounding_box)
{
  SparseMatrix sm(10);
  //  10 x 10 matrix - 6 random elements in the middle
  for (int i = 0; i < 6; i++)
  {
    uint8_t x = random(5) + 3;
    uint8_t y = random(5) + 3;
    sm.set(x, y, random(37));
  }
  //  random generator does not work
  //  assertEqual(6, sm.count());
  assertEqual(1, sm.count());

  uint8_t minX, maxX, minY, maxY;
  sm.boundingBox(minX, maxX, minY, maxY);
  fprintf(stderr, "%d\t%d\t%d\t%d\n", minX, maxX, minY, maxY);
}


unittest_main()


// -- END OF FILE --
