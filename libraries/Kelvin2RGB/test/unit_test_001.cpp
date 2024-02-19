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
  fprintf(stderr, "KELVIN2RGB_LIB_VERSION: %s\n", (char *) KELVIN2RGB_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(DLS_dark           ,     0);
  assertEqual(DLS_match          ,  1700);
  assertEqual(DLS_sodiumLamp     ,  1700);
  assertEqual(DLS_candleFlame    ,  1850);
  assertEqual(DLS_sunrise        ,  1850);
  assertEqual(DLS_sunset         ,  1850);
  assertEqual(DLS_bulb           ,  2400);
  assertEqual(DLS_bulbSoftWhite  ,  2550);
  assertEqual(DLS_LEDlamp        ,  2700);
  assertEqual(DLS_warmWhite      ,  3000);
  assertEqual(DLS_studioLight    ,  3200);
  assertEqual(DLS_studioCPlight  ,  3350);
  assertEqual(DLS_daylightHorizon,  5000);
  assertEqual(DLS_flashLight     ,  5700);
  assertEqual(DLS_xenonLight     ,  6200);
  assertEqual(DLS_dayLightBright ,  6500);
  assertEqual(DLS_normal         ,  6500);
  assertEqual(DLS_screenLow      ,  6500);
  assertEqual(DLS_screenMed      ,  8000);
  assertEqual(DLS_screenHigh     ,  9500);
  assertEqual(DLS_polewardSky0   , 15000);
  assertEqual(DLS_polewardSky1   , 19000);
  assertEqual(DLS_polewardSky2   , 23000);
  assertEqual(DLS_polewardSky3   , 27000);
}



unittest(test_constructor)
{
  Kelvin2RGB tempColor;

  tempColor.begin();

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

  tempColor.begin();

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

  tempColor.begin();

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

  tempColor.begin();

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
  assertEqual(11331187, tempColor.BGR());
  assertEqual(2130722560, tempColor.CMYK());
  assertEqual(30517, tempColor.RGB565());
}


unittest_main()


//  -- END OF FILE ---

