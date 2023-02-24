//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the pressure library
//          https://github.com/RobTillaart/pressure
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
#include "pressure.h"



unittest_setup()
{
  fprintf(stderr, "PRESSURE_LIB_VERSION: %s\n", (char *) PRESSURE_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  pressure P;

  assertEqualFloat(0.0, P.getMilliBar(), 1e-4);
  assertEqualFloat(0.0, P.getBar(), 1e-4);
  assertEqualFloat(0.0, P.getPSI(), 1e-4);
  assertEqualFloat(0.0, P.getATM(), 1e-4);
  assertEqualFloat(0.0, P.getDynes(), 1e-4);
  assertEqualFloat(0.0, P.getInchHg(), 1e-4);
  assertEqualFloat(0.0, P.getInchH2O(), 1e-4);
  assertEqualFloat(0.0, P.getPascal(), 1e-4);
  assertEqualFloat(0.0, P.getTORR(), 1e-4);
  assertEqualFloat(0.0, P.getCmHg(), 1e-4);
  assertEqualFloat(0.0, P.getCmH2O(), 1e-4);
  assertEqualFloat(0.0, P.getMSW(), 1e-4);
}


unittest(test_constants_setter)
{
  fprintf(stderr, "Test conversion constants\n");

  assertEqualFloat(1000,          BAR2MILLIBAR,    1);
  assertEqualFloat(1013.25,       ATM2MILLIBAR,    1e-4);
  assertEqualFloat(68.9475729318, PSI2MILLIBAR,    1e-4);
  assertEqualFloat(0.001,         DYNES2MILLIBAR,  1e-7);
  assertEqualFloat(33.85355,      INHG2MILLIBAR,   1e-4);
  assertEqualFloat(2.49088908333, INH2O2MILLIBAR,  1e-4);
  assertEqualFloat(0.01,          PASCAL2MILLIBAR, 1e-4);
  assertEqualFloat(1.33322368,    TORR2MILLIBAR,   1e-5);
  assertEqualFloat(13.3322368,    CMHG2MILLIBAR,   1e-5);
  assertEqualFloat(0.980665,      CMH2O2MILLIBAR,  1e-5);
  assertEqualFloat(0.01,          MSW2MILLIBAR,    1e-3);
}


unittest(test_constants_getter)
{
  fprintf(stderr, "Test conversion constants\n");

  assertEqualFloat(0.001,         MILLIBAR2BAR,    1e-7);
  assertEqualFloat(9.86923267e-4, MILLIBAR2ATM,    1e-7);
  assertEqualFloat(0.0145037738,  MILLIBAR2PSI,    1e-4);
  assertEqualFloat(1000,          MILLIBAR2DYNES,  1);
  assertEqualFloat(2.9539e-2,     MILLIBAR2INHG,   1e-5);
  assertEqualFloat(0.40146307866, MILLIBAR2INH2O,  1e-4);
  assertEqualFloat(100,           MILLIBAR2PASCAL, 1e-3);
  assertEqualFloat(0.750061683,   MILLIBAR2TORR,   1e-5);
  assertEqualFloat(0.0750061683,  MILLIBAR2CMHG,   1e-6);
  assertEqualFloat(1.0197162129,  MILLIBAR2CMH2O,  1e-5);
  assertEqualFloat(100,           MILLIBAR2MSW,    1);
}


unittest(test_constants_3)
{
  fprintf(stderr, "Test conversion constants\n");

  assertEqualFloat(1.0, BAR2MILLIBAR    * MILLIBAR2BAR,    1e-5);
  assertEqualFloat(1.0, ATM2MILLIBAR    * MILLIBAR2ATM,    1e-5);
  assertEqualFloat(1.0, PSI2MILLIBAR    * MILLIBAR2PSI,    1e-5);
  assertEqualFloat(1.0, DYNES2MILLIBAR  * MILLIBAR2DYNES,  1e-5);
  assertEqualFloat(1.0, INHG2MILLIBAR   * MILLIBAR2INHG,   1e-5);
  assertEqualFloat(1.0, INH2O2MILLIBAR  * MILLIBAR2INH2O,  1e-5);
  assertEqualFloat(1.0, PASCAL2MILLIBAR * MILLIBAR2PASCAL, 1e-5);
  assertEqualFloat(1.0, TORR2MILLIBAR   * MILLIBAR2TORR,   1e-5);
  assertEqualFloat(1.0, CMHG2MILLIBAR   * MILLIBAR2CMHG,   1e-5);
  assertEqualFloat(1.0, CMH2O2MILLIBAR  * MILLIBAR2CMH2O,  1e-5);
  assertEqualFloat(1.0, MSW2MILLIBAR    * MILLIBAR2MSW,    1e-5);
}


unittest(test_get_set)
{
  pressure P;

  P.setMilliBar(2);
  assertEqualFloat(2.0, P.getMilliBar(), 1e-4);
  P.setBar(2);
  assertEqualFloat(2.0, P.getBar(), 1e-4);
  P.setPSI(2);
  assertEqualFloat(2.0, P.getPSI(), 1e-4);

  P.setATM(2);
  assertEqualFloat(2.0, P.getATM(), 1e-4);
  P.setDynes(2);
  assertEqualFloat(2.0, P.getDynes(), 1e-4);
  P.setInchHg(2);
  assertEqualFloat(2.0, P.getInchHg(), 1e-4);

  P.setInchH2O(2);
  assertEqualFloat(2.0, P.getInchH2O(), 1e-4);
  P.setPascal(2);
  assertEqualFloat(2.0, P.getPascal(), 1e-4);
  P.setTORR(2);
  assertEqualFloat(2.0, P.getTORR(), 1e-4);

  P.setCmHg(2);
  assertEqualFloat(2.0, P.getCmHg(), 1e-4);
  P.setCmH2O(2);
  assertEqualFloat(2.0, P.getCmH2O(), 1e-4);
  P.setMSW(2);
  assertEqualFloat(2.0, P.getMSW(), 1e-4);
}


unittest_main()


//  -- END OF FILE --

