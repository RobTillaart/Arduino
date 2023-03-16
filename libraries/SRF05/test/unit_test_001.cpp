//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-07
// PURPOSE: unit tests for the SRF05 library
//          https://github.com/RobTillaart/SRF05
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

#include "SRF05.h"



unittest_setup()
{
  fprintf(stderr, "\nSRF05_LIB_VERSION: %s\n", (char *) SRF05_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, SRF05_MODE_SINGLE);
  assertEqual(1, SRF05_MODE_AVERAGE);
  assertEqual(2, SRF05_MODE_MEDIAN);
  assertEqual(3, SRF05_MODE_RUN_AVERAGE);
}


unittest(test_constructor)
{
  SRF05 SRF(7, 6);
}


unittest(test_SOS)
{
  SRF05 SRF(7, 6);

  assertEqualFloat(340, SRF.getSpeedOfSound(), 0.001);
  for (float sos = 330; sos < 350; sos += 1.3)
  {
    SRF.setSpeedOfSound(sos);
    assertEqualFloat(sos, SRF.getSpeedOfSound(), 0.001);
  }
}


unittest(test_correctionFactor)
{
  SRF05 SRF(7, 6);

  assertEqualFloat(1, SRF.getCorrectionFactor(), 0.001);
  for (float cf = 0.95; cf < 1.06; cf += 0.01)
  {
    SRF.setCorrectionFactor(cf);
    assertEqualFloat(cf, SRF.getCorrectionFactor(), 0.001);
  }
}


unittest(test_operationalMode)
{
  SRF05 SRF(7, 6);

  assertEqual(0, SRF.getOperationalMode());
  SRF.setModeRunningAverage(0.2);
  assertEqual(3, SRF.getOperationalMode());
  SRF.setModeMedian(7);
  assertEqual(2, SRF.getOperationalMode());
  SRF.setModeAverage(7);
  assertEqual(1, SRF.getOperationalMode());
  SRF.setModeSingle();
  assertEqual(0, SRF.getOperationalMode());
}


unittest(test_lastTime)
{
  SRF05 SRF(7, 6);

  assertEqual(0, SRF.lastTime());  //  minimal
}


unittest(test_triggerLength)
{
  SRF05 SRF(7, 6);

  assertEqual(10, SRF.getTriggerLength());
  for (uint8_t len = 1; len < 20; len += 3)
  {
    SRF.setTriggerLength(len);
    assertEqual(len, SRF.getTriggerLength());
  }
  SRF.setTriggerLength();
  assertEqual(10, SRF.getTriggerLength());
}


unittest_main()


//  -- END OF FILE --

