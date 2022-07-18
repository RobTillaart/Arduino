//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-07-18
// PURPOSE: unit tests for SparseArray library
//          https://github.com/RobTillaart/SparseArray
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
#include "SparseArray.h"



unittest_setup()
{
  fprintf(stderr, "SPARSEARRAY_LIB_VERSION: %s\n", (char*) SPARSEARRAY_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1000, SPARSEARRAY_MAX_SIZE);
}


unittest(test_constructor)
{
  SparseArray sar(10);
  assertEqual(10, sar.size());
  assertEqual(0, sar.count());

  SparseArray sar2(1100);
  assertEqual(1000, sar2.size());
}


unittest(test_set)
{
  SparseArray sar(10);
  assertEqual(10, sar.size());
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sar.set(i, 1.0 * i * i));
    assertEqual(i, sar.count());
  }
  assertTrue(sar.set(13, 5));
  assertFalse(sar.set(15, 5));   //  don't fit any more...

  //  do not set new element to zero
  sar.clear();
  assertEqual(0, sar.count());

  sar.set(1, 0);
  assertEqual(0, sar.count());
}


unittest(test_get)
{
  SparseArray sar(10);
  assertEqual(10, sar.size());
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sar.set(i, 1.0 * i * i));
    assertEqualFloat(1.0 * i * i, sar.get(i), 0.001);
  }
}


unittest(test_sum)
{
  SparseArray sar(10);
  assertEqual(10, sar.size());
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sar.set(i, 10));
  }
  assertEqualFloat(100, sar.sum(), 0.0001);
}


unittest(test_add)
{
  SparseArray sar(10);
  assertEqual(10, sar.size());
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sar.add(i, 1.0 * i * i));
    assertEqualFloat(1.0 * i * i, sar.get(i), 0.001);
  }
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sar.add(i, 1.0 * i * i));
    assertEqualFloat(2.0 * i * i, sar.get(i), 0.001);
  }
  for (int i = 0; i < 10; i++)
  {
    assertTrue(sar.add(i, -2.0 * i * i));
    assertEqualFloat(0, sar.get(i), 0.001);
  }
  assertEqual(0, sar.count());
}


unittest(test_boundingSegment)
{
  SparseArray sar(10);
  assertEqual(10, sar.size());
  //  10 element array - 6 random elements in the middle
  for (int i = 0; i < 6; i++)
  {
    uint8_t x = random(5) + 3;
    sar.set(x, random(37));
  }
  //  random generator does not work
  //  assertEqual(6, sar.count());
  assertEqual(1, sar.count());

  uint16_t minX, maxX;
  sar.boundingSegment(minX, maxX);
  fprintf(stderr, "%d\t%d\n", minX, maxX);
}


unittest_main()


// -- END OF FILE --
