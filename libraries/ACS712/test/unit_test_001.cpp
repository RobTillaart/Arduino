//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-06
// PURPOSE: unit tests for the ACS712 current sensor
//          https://github.com/RobTillaart/ACS712
//          https://www.adafruit.com/product/2857
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
#include "ACS712.h"

#define A0      0


unittest_setup()
{
    fprintf(stderr, "ACS712_LIB_VERSION: %s\n", (char *) ACS712_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(1.0/sqrt(2), ACS712_FF_SINUS,    0.001);
  assertEqualFloat(1.0, ACS712_FF_SQUARE,           0.001);
  assertEqualFloat(1.0/sqrt(3), ACS712_FF_TRIANGLE, 0.001);
  assertEqualFloat(1.0/sqrt(3), ACS712_FF_SAWTOOTH, 0.001);
  
  assertEqual(21, ACS712_DEFAULT_NOISE);
  assertEqual(50, ACS712_DEFAULT_FREQ);
}


unittest(test_mA_DC)
{
  GodmodeState* state = GODMODE();
  state->reset();

  //  0 == A0
  ACS712  ACS(0, 5.0, 1023, 100);  // analogPin, volts, maxADC, mVperA

  // assertEqual(0, ACS.mA_AC(50));
  // assertEqual(0, ACS.mA_AC(60));
  int future[12] = {0, 0, 100, 100, 200, 200, 511, 511, 900, 900, 1023, 1023};
  state->analogPin[0].fromArray(future, 12);

  assertEqualFloat(-24975.6, ACS.mA_DC(), 1);
  assertEqualFloat(-20088.0, ACS.mA_DC(), 1);
  assertEqualFloat(-15200.4, ACS.mA_DC(), 1);
  assertEqualFloat(0.0,      ACS.mA_DC(), 1);
  assertEqualFloat( 19012.7, ACS.mA_DC(), 1);
  assertEqualFloat( 25024.4, ACS.mA_DC(), 1);
}


unittest(test_mA_AC)
{
  ACS712  ACS(A0, 5.0, 1023, 100);  // analogPin, volts, maxADC, mVperA

  // loop with micros and a lot of analogReads - not possible
  // assertEqual(0, ACS.mA_AC(50));
  // assertEqual(0, ACS.mA_AC(60));
  assertEqual(1, 1);
}


unittest(test_mA_AC_samples)
{
  ACS712  ACS(A0, 5.0, 1023, 100);  // analogPin, volts, maxADC, mVperA

  // loop with micros and a lot (150?) of analogReads - not possible
  // assertEqual(0, ACS.mA_AC_samples(50));
  // assertEqual(0, ACS.mA_AC_samples(60));
  assertEqual(1, 1);
}


unittest(test_midPoint)
{
  ACS712  ACS(A0, 5.0, 1023, 100); // analogPin, volts, maxADC, mVperA

  // loop with micros and a lot of analogReads - not possible
  // ACS.autoMidPoint(50);
  // uint16_t amp50 = ACS.getMidPoint();
  // assertEqual(0, amp50);
  // 
  // ACS.autoMidPoint(60);
  // uint16_t amp60 = ACS.getMidPoint();
  // assertEqual(0, amp60);

  uint16_t amp = ACS.getMidPoint();
  assertEqual(511, amp);
  
  ACS.setMidPoint(1000);
  amp = ACS.getMidPoint();
  assertEqual(1000, amp);

  ACS.incMidPoint();
  amp = ACS.getMidPoint();
  assertEqual(1001, amp);

  ACS.decMidPoint();
  amp = ACS.getMidPoint();
  assertEqual(1000, amp);

  ACS.decMidPoint();
  amp = ACS.getMidPoint();
  assertEqual(999, amp);

  ACS.resetMidPoint();
  amp = ACS.getMidPoint();
  assertEqual(511, amp);

  //  test range ends
  ACS.setMidPoint(1023);
  amp = ACS.incMidPoint();
  assertEqual(1023, amp);

  ACS.setMidPoint(0);
  amp = ACS.decMidPoint();
  assertEqual(0, amp);
}


unittest(test_formFactor)
{
  ACS712  ACS(A0, 5.0, 1023, 100);

  //  default 0.5 * sqrt(2)
  float ff = ACS.getFormFactor();
  float eff = 0.5 * sqrt(2);
  float delta = abs(eff - ff);
  assertMoreOrEqual(0.0001, delta);

  ACS.setFormFactor(0.8);
  ff = ACS.getFormFactor();
  eff = 0.8;
  delta = abs(eff - ff);
  assertMoreOrEqual(0.0001, delta);
}


unittest(test_Noise)
{
  ACS712  ACS(A0, 5.0, 1023, 100);

  int nmv = ACS.getNoisemV();
  assertEqual(21, nmv);       //  default value..

  ACS.setNoisemV(100);
  nmv = ACS.getNoisemV();
  assertEqual(100, nmv);
}


unittest(test_mVperAmp)
{
  ACS712  ACS(A0, 5.0, 1023, 100);

  float mpa = ACS.getmVperAmp();
  assertEqualFloat(100, mpa, 0.001);       //  default value..

  float mva = 25.0;
  while (mva < 200)
  {
    ACS.setmVperAmp(mva);
    mpa = ACS.getmVperAmp();
    assertEqualFloat(mva, mpa, 0.001);
    mva += 24.8;  //  just a bit random adjustments
  }
}


unittest(test_AmperePerStep)
{
  ACS712  ACS(A0, 5.0, 1023, 100);

  float aps = ACS.getAmperePerStep();
  assertEqualFloat(0.047885, aps, 0.001);

  float mva = 25.0;
  while (mva < 200)
  {
    ACS.setmVperAmp(mva);
    aps = ACS.getAmperePerStep();
    assertEqualFloat(5000.0/1023/mva, aps, 0.001);
    mva += 24;
  }
}


unittest_main()


//  -- END OF FILE --
