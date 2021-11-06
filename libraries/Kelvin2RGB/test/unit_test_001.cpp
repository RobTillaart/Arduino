//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the Kelvin2RGB library
//          https://github.com/RobTillaart/Kelvin2RGB
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


#include "Arduino.h"
#include "Kelvin2RGB.h"


unittest_setup()
{
}


unittest_teardown()
{
}


/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", (char *) KELVIN2RGB_LIB_VERSION);
  
  Kelvin2RGB tempColor;

  assertEqualFloat(0, tempColor.temperature(), 0.0001);
  assertEqualFloat(0, tempColor.brightness(), 0.0001);
  assertEqualFloat(0, tempColor.red(), 0.0001);
  assertEqualFloat(0, tempColor.green(), 0.0001);
  assertEqualFloat(0, tempColor.blue(), 0.0001);
  assertEqualFloat(0, tempColor.RGB(), 0.0001);
}


unittest(test_Tanner_Helland)
{
  Kelvin2RGB tempColor;

  fprintf(stderr, "DLS_warmWhite\n");
  tempColor.convert_TH(DLS_warmWhite, 100);

  assertEqualFloat(3000, tempColor.temperature(), 0.0001);
  assertEqualFloat(100, tempColor.brightness(), 0.0001);
  assertEqualFloat(1, tempColor.red(), 0.0001);
  assertEqualFloat(0.694903, tempColor.green(), 0.0001);
  assertEqualFloat(0.431048, tempColor.blue(), 0.0001);
  assertEqual(16757102, tempColor.RGB());
}


unittest(test_Neil_Bartlett)
{
  Kelvin2RGB tempColor;

  fprintf(stderr, "DLS_warmWhite\n");
  tempColor.convert_NB(DLS_warmWhite, 100);

  assertEqualFloat(3000, tempColor.temperature(), 0.0001);
  assertEqualFloat(100, tempColor.brightness(), 0.0001);
  assertEqualFloat(1, tempColor.red(), 0.0001);
  assertEqualFloat(0.707636, tempColor.green(), 0.0001);
  assertEqualFloat(0.424804, tempColor.blue(), 0.0001);
  assertEqual(16757868, tempColor.RGB());
}


unittest(test_colour_spaces)
{
  Kelvin2RGB tempColor;

  fprintf(stderr, "test_colour_spaces\n");
  tempColor.setRGB(0.50, 1.00, 0.75, 90);  // brightness in %
  
  fprintf(stderr, "BRIGHT: %f\n", tempColor.brightness());
  fprintf(stderr, "RED   : %f\n", tempColor.red());
  fprintf(stderr, "GREEN : %f\n", tempColor.green());
  fprintf(stderr, "BLUE  : %f\n", tempColor.blue());
  fprintf(stderr, "RGB   : %d\n", tempColor.RGB());
  fprintf(stderr, "BGR   : %d\n", tempColor.BGR());
  fprintf(stderr, "CMYK  : %d\n", tempColor.CMYK());
  fprintf(stderr, "RGB565: %d\n", tempColor.RGB565());

  assertEqualFloat(90, tempColor.brightness(), 0.0001);
  assertEqualFloat(0.450, tempColor.red(),   0.0001);
  assertEqualFloat(0.900, tempColor.green(), 0.0001);
  assertEqualFloat(0.675, tempColor.blue(),  0.0001);
  assertEqual(7595692, tempColor.RGB());
  assertEqual(65792, tempColor.BGR());
  assertEqual(2130722560, tempColor.CMYK());
  assertEqual(30517, tempColor.RGB565());
}


unittest_main()

// --------
