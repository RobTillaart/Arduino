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
}

unittest_teardown()
{
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

  assertEqual(-24975, ACS.mA_DC());
  assertEqual(-20087, ACS.mA_DC());
  assertEqual(-15200, ACS.mA_DC());
  assertEqual(0, ACS.mA_DC());
  assertEqual(19012, ACS.mA_DC());
  assertEqual(25024, ACS.mA_DC());
}


unittest(test_mA_AC)
{
  ACS712  ACS(A0, 5.0, 1023, 100);  // analogPin, volts, maxADC, mVperA

  // loop with micros and a lot of analogReads - not possible
  // assertEqual(0, ACS.mA_AC(50));
  // assertEqual(0, ACS.mA_AC(60));
  assertEqual(1, 1);
}


unittest(test_midPoint)
{
  ACS712  ACS(A0, 5.0, 1023, 100); // analogPin, volts, maxADC, mVperA

  // loop with micros and a lot of analogReads - not possible
  // ACS.autoMidPoint(50);
  // float amp50 = ACS.getMidPoint();
  // assertEqual(0, amp50);
  // 
  // ACS.autoMidPoint(60);
  // float amp60 = ACS.getMidPoint();
  // assertEqual(0, amp60);

  ACS.setMidPoint(1000);
  float amp = ACS.getMidPoint();
  assertEqual(1000, amp);

  ACS.incMidPoint();
  amp = ACS.getMidPoint();
  assertEqual(1001, amp);

  ACS.decMidPoint();
  amp = ACS.getMidPoint();
  assertEqual(1000, amp);
}


unittest(test_formFactor)
{
  ACS712  ACS(A0, 5.0, 1023, 100);

  // default 0.5 * sqrt(2)
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
  assertEqual(21, nmv);       // default value..

  ACS.setNoisemV(100);
  nmv = ACS.getNoisemV();
  assertEqual(100, nmv);
}


unittest(test_mVperAmp)
{
  ACS712  ACS(A0, 5.0, 1023, 100);

  int mpa = ACS.getmVperAmp();
  assertEqual(100, mpa);       // default value..

  ACS.setmVperAmp(50);
  mpa = ACS.getmVperAmp();
  assertEqual(50, mpa);
}


unittest_main()


// -- END OF FILE --
