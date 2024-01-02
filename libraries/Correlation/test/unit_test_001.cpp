//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the Correlation library
//          https://github.com/RobTillaart/Correlation
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


#include "Correlation.h"


unittest_setup()
{
  fprintf(stderr, "CORRELATION_LIB_VERSION: %s\n", (char *) CORRELATION_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Correlation C;
  assertEqual(0, C.count());
  assertEqual(20, C.size());

  Correlation D(100);
  assertEqual(0, D.count());
  assertEqual(100, D.size());
}


unittest(test_add_basic)
{
  Correlation C(2);

  assertTrue(C.add(2, 7));
  assertTrue(C.add(3, 9));
  assertFalse(C.add(4, 10));
}


unittest(test_add_clear)
{
  Correlation C;

  assertTrue(C.add(2, 7));
  assertTrue(C.add(3, 9));
  assertTrue(C.add(4, 10));
  assertTrue(C.add(5, 14));
  assertTrue(C.add(6, 15));

  assertEqual(5, C.count());
  assertEqual(20, C.size());

  C.clear();
  assertEqual(0, C.count());
  assertEqual(20, C.size());

  for (int i = 0; i < C.size(); i++)
  {
    assertTrue(C.add(i, i*i));
  }
  assertFalse(C.add(0, 0));
}


unittest(test_get_coefficients)
{
  Correlation C;

  C.add(2, 7);
  C.add(3, 9);
  C.add(4, 10);
  C.add(5, 14);
  C.add(6, 15);
  C.calculate();

  assertEqualFloat(2.6,      C.getA(), 0.0001);
  assertEqualFloat(2.1,      C.getB(), 0.0001);
  assertEqualFloat(0.97913,  C.getR(), 0.0001);
  assertEqualFloat(0.958696, C.getRsquare(), 0.0001);
  assertEqualFloat(1.9,      C.getEsquare(), 0.0001);
}


unittest(test_get_statistics)
{
  Correlation C;

  C.add(2, 7);
  C.add(3, 9);
  C.add(4, 10);
  C.add(5, 14);
  C.add(6, 15);
  C.calculate();

  assertEqualFloat(4, C.getAverageX(), 0.0001);
  assertEqualFloat(11, C.getAverageY(), 0.0001);
}


unittest(test_estimate)
{
  Correlation C;

  C.add(2, 7);
  C.add(3, 9);
  C.add(4, 10);
  C.add(5, 14);
  C.add(6, 15);
  C.calculate();

  fprintf(stderr, "estimate X\n");
  for (int i = 4; i < 8; i++)
  {
    fprintf(stderr, "%d\t%f\n", i, C.getEstimateX(i));
  }
  fprintf(stderr, "estimate Y\n");
  for (int i = 15; i < 20; i++)
  {
    fprintf(stderr, "%d\t%f\n", i, C.getEstimateY(i));
  }
  assertEqualFloat(-1.2381, C.getEstimateX(0), 0.0001);
  assertEqualFloat(2.6,     C.getEstimateY(0), 0.0001);
}


unittest(test_calculate)
{
  Correlation C;

  assertFalse(C.calculate());
  assertFalse(C.calculate(true));

  C.add(2, 7);
  C.add(3, 9);
  C.add(4, 10);
  C.add(5, 14);
  C.add(6, 15);

  assertTrue(C.calculate());
  assertTrue(C.calculate(true));
}


unittest(test_calculate_flags)
{
  Correlation C;

  assertTrue(C.getR2Calculation());
  C.setR2Calculation(false);
  assertFalse(C.getR2Calculation());
  C.setR2Calculation(true);
  assertTrue(C.getR2Calculation());

  assertTrue(C.getE2Calculation());
  C.setE2Calculation(false);
  assertFalse(C.getE2Calculation());
  C.setE2Calculation(true);
  assertTrue(C.getE2Calculation());
}


unittest_main()


//  -- END OF FILE --

