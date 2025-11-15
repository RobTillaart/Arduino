//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-10-31
// PURPOSE: unit tests for the ellipse
//          https://github.com/RobTillaart/ellipse
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


#include "ellipse.h"


unittest_setup()
{
  fprintf(stderr, "ELLIPSE_LIB_VERSION: %s\n", (char*) ELLIPSE_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "\nE(1.0, 1.0)");
  ellipse E(1.0, 1.0);
  fprintf(stderr, "%03.8f\n", E.getA());
  fprintf(stderr, "%03.8f\n", E.getB());
  fprintf(stderr, "%03.8f\n", E.getC());
  fprintf(stderr, "%03.8f\n", E.getH());
  fprintf(stderr, "%03.8f\n", E.area());
  fprintf(stderr, "%03.8f\n", E.circumference());
  fprintf(stderr, "%03.8f\n", E.perimeter_reference());
  fprintf(stderr, "%03.8f\n", E.perimeter_Kepler());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan1());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan2());
  fprintf(stderr, "%03.8f\n", E.eccentricity());
  fprintf(stderr, "%03.8f\n", E.ratio());
  fprintf(stderr, "\n");

  fprintf(stderr, "E(1.0, 0.5)");
  E.setA(1.0);
  E.setB(0.5);
  fprintf(stderr, "%03.8f\n", E.getA());
  fprintf(stderr, "%03.8f\n", E.getB());
  fprintf(stderr, "%03.8f\n", E.getC());
  fprintf(stderr, "%03.8f\n", E.getH());
  fprintf(stderr, "%03.8f\n", E.area());
  fprintf(stderr, "%03.8f\n", E.circumference());
  fprintf(stderr, "%03.8f\n", E.perimeter_reference());
  fprintf(stderr, "%03.8f\n", E.perimeter_Kepler());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan1());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan2());
  fprintf(stderr, "%03.8f\n", E.eccentricity());
  fprintf(stderr, "%03.8f\n", E.ratio());
}


unittest(test_approximation)
{
  fprintf(stderr, "E(1.0, 0.8)");
  ellipse E(1.0, 0.8);
  fprintf(stderr, "%03.8f\n", E.getA());
  fprintf(stderr, "%03.8f\n", E.getB());
  fprintf(stderr, "%03.8f\n", E.perimeter_reference());
  fprintf(stderr, "%03.8f\n", E.perimeter_Parker_fast());
  fprintf(stderr, "%03.8f\n", E.perimeter_polynome());
  fprintf(stderr, "\n");

  fprintf(stderr, "E(1.0, 0.4)");
  E.setA(1.0);
  E.setB(0.4);
  fprintf(stderr, "%03.8f\n", E.getA());
  fprintf(stderr, "%03.8f\n", E.getB());
  fprintf(stderr, "%03.8f\n", E.perimeter_reference());
  fprintf(stderr, "%03.8f\n", E.perimeter_Parker_fast());
  fprintf(stderr, "%03.8f\n", E.perimeter_polynome());
}


unittest(test_isCircle)
{
  fprintf(stderr, "E(1.0, 1.0) \t");
  ellipse E(1.0, 1.0);
  fprintf(stderr, "ECC: %03.8f\n", E.eccentricity());
  assertTrue(E.isCircle());
  assertFalse(E.isFlat());

  E.setA(1.0);
  E.setB(0.1);
  fprintf(stderr, "E(1.0, 0.1) \t");
  fprintf(stderr, "ECC: %03.8f\n", E.eccentricity());
  assertFalse(E.isCircle());
  assertTrue(E.isFlat());
}


unittest(test_radius)
{
  fprintf(stderr, "E(1.0, 1.0)");
  ellipse E(1.0, 1.0);
  fprintf(stderr, "LONG:\t%03.8f\n", E.getLongRadius());
  fprintf(stderr, "SHORT:\t%03.8f\n", E.getShortRadius());

  E.setA(1.0);
  E.setB(0.1);
  fprintf(stderr, "LONG:\t%03.8f\n", E.getLongRadius());
  fprintf(stderr, "SHORT:\t%03.8f\n", E.getShortRadius());
}


unittest(test_angle)
{
  ellipse E(1.0, 1.0);
  for (int B = 10; B >= 0; B--)
  {
    E.setB(B * 0.1);
    fprintf(stderr, "E(1.0, %1.1f) => ", B * 0.1);
    fprintf(stderr, "Angle:\t%03.8f\n", E.angle());
  }
}


unittest_main()


//  -- END OF FILE --

