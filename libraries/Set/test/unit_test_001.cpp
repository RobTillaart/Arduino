//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-07
// PURPOSE: unit tests for the SET library
//          https://github.com/RobTillaart/SET
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>


#include "set.h"



unittest_setup()
{
  fprintf(stderr, "SET_LIB_VERSION: %s\n", (char *) SET_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Set A;

  assertTrue(A.isEmpty());
  assertFalse(A.isFull());
  assertEqual(0, A.count());

  A.invert();
  assertFalse(A.isEmpty());
  assertTrue(A.isFull());
  assertEqual(256, A.count());

  A.clear();
  assertTrue(A.isEmpty());
  assertFalse(A.isFull());
  assertEqual(0, A.count());

  A.add(42);
  assertFalse(A.isEmpty());
  assertFalse(A.isFull());
  assertEqual(1, A.count());

  A.addAll();
  assertFalse(A.isEmpty());
  assertTrue(A.isFull());
  assertEqual(256, A.count());
}


unittest(test_count_has)
{
  Set A;

  A.clear();
  for (int i = 0; i < 10; i++)
  {
    assertEqual(i, A.count());
    A.add(i);
  }

  for (int i = 0; i < 10; i++)
  {
    assertTrue(A.has(i));
  }

  for (int i = 0; i < 10; i++)
  {
    assertEqual(10 - i, A.count());
    A.sub(i);
  }
  assertEqual(0, A.count());

}


unittest(test_operator)
{
  Set A;
  Set B;
  Set C;

  A.clear();
  B.clear();
  for (int i = 0; i < 10; i++)
  {
    A.add(i);
    B.add(i + 7);
  }
  C = A + B;
  assertEqual(10, A.count());
  assertEqual(10, B.count());
  assertEqual(17, C.count());

  C = A - B;
  assertEqual(7, C.count());

  C = A * B;
  assertEqual(3, C.count());

  C = A;
  A += B;
  assertEqual(17, A.count());

  A -= B;
  assertEqual(7, A.count());

  A *= B;
  assertEqual(0, A.count());

  C *= B;
  assertTrue( A == A );
  assertTrue( A != B );
  assertTrue( C <= B);
}


unittest(test_iterator)
{
  Set A;
  A.clear();

  for (int i = 0; i < 20; i++)
  {
    A.add(i*3);
  }
  assertEqual(20, A.count());

  fprintf(stderr, "\nFirst() -> next()\n");
  int cur = A.first();
  for (int i = 0; i < 20; i++)
  {
    assertEqual(i * 3, cur);
    cur = A.next();
  }

  fprintf(stderr, "\nlast() -> prev()\n");
  cur = A.last();
  for (int i = 19; i > 0; i--)
  {
    assertEqual(i * 3, cur);
    cur = A.prev();
  }

  fprintf(stderr, "\ngetNth()\n");
  assertEqual(0, A.getNth(1));
  assertEqual(3, A.getNth(2));
  assertEqual(6, A.getNth(3));
  assertEqual(9, A.getNth(4));
  assertEqual(12, A.getNth(5));
  assertEqual(15, A.getNth(6));
  assertEqual(18, A.getNth(7));
  assertEqual(21, A.getNth(8));

}


unittest_main()


// --------
