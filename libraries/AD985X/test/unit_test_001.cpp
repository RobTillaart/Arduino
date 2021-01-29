//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the AD9850 and AD9851 function generator
//          https://github.com/RobTillaart/AD985X
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
#include "AD985X.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", AD985X_LIB_VERSION);
  AD9850 funcgen0;
  AD9851 funcgen1;

  assertEqual(AD9850_MAX_FREQ, funcgen0.getMaxFrequency());
  assertEqual(AD9851_MAX_FREQ, funcgen1.getMaxFrequency());
}


unittest(test_auto_update)
{
  fprintf(stderr, "VERSION: %s\n", AD985X_LIB_VERSION);
  AD9850 funcgen0;
  AD9851 funcgen1;
  funcgen0.begin(4, 5, 6);
  funcgen1.begin(10, 11, 16);


  assertTrue(funcgen0.getAutoUpdate());
  assertTrue(funcgen1.getAutoUpdate());
  funcgen0.setAutoUpdate(false);
  funcgen1.setAutoUpdate(false);
  assertFalse(funcgen0.getAutoUpdate());
  assertFalse(funcgen1.getAutoUpdate());
  funcgen0.setAutoUpdate(true);
  funcgen1.setAutoUpdate(true);
  assertTrue(funcgen0.getAutoUpdate());
  assertTrue(funcgen1.getAutoUpdate());
}


unittest(test_ad9850)
{
  AD9850 funcgen;
  funcgen.begin(4, 5, 6);

  funcgen.setFrequency(1000);
  long freq = funcgen.getFrequency();
  assertEqual(1000, freq);

  for (int ph = 0; ph < 32; ph += 4)
  {
    funcgen.setPhase(ph);
    int phase = funcgen.getPhase();
    assertEqual(ph, phase);
  }
}


unittest(test_ad9851)
{
  AD9851 funcgen;
  funcgen.begin(4, 5, 6);
  
  funcgen.setFrequency(1000);
  long freq = funcgen.getFrequency();
  assertEqual(1000, freq);

  for (int ph = 0; ph < 32; ph += 4)
  {
    funcgen.setPhase(ph);
    int phase = funcgen.getPhase();
    assertEqual(ph, phase);
  }

  funcgen.setRefClockHigh();
  assertEqual(180, funcgen.getRefClock());
  funcgen.setRefClockLow();
  assertEqual(30, funcgen.getRefClock());
}


unittest(test_ad9851_reset)
{
  AD9851 funcgen;
  funcgen.begin(4, 5, 6);
  
  funcgen.setFrequency(1000);
  assertEqual(1000, funcgen.getFrequency());
  funcgen.setPhase(14);
  assertEqual(14, funcgen.getPhase());
  funcgen.setRefClockHigh();
  assertEqual(180, funcgen.getRefClock());
  
  funcgen.reset();

  assertEqual(0,  funcgen.getFrequency());
  assertEqual(0,  funcgen.getPhase());
  assertEqual(30, funcgen.getRefClock());
}


unittest(test_ad9851_autoRefClock)
{
  AD9851 funcgen;
  funcgen.begin(4, 5, 6);

  assertFalse(funcgen.getAutoRefClock());
  for (uint32_t freq = 70; freq <= 70000000; freq *= 10)
  {
    funcgen.setFrequency(freq);
    fprintf(stderr, "freq %ld\t", freq);
    assertEqual(30, funcgen.getRefClock());
  }

  funcgen.setAutoRefClock(true);
  assertTrue(funcgen.getAutoRefClock());
  for (uint32_t freq = 70; freq <= 1000000; freq *= 10)
  {
    funcgen.setFrequency(freq);
    fprintf(stderr, "freq %ld\t", freq);
    assertEqual(30, funcgen.getRefClock());
  }

  funcgen.setFrequency(10000000);
  fprintf(stderr, "freq 10000000\t");
  assertEqual(30, funcgen.getRefClock());
  funcgen.setFrequency(100000001);
  fprintf(stderr, "freq 100000001\t");
  assertEqual(180, funcgen.getRefClock());
  funcgen.setFrequency(70000000);
  fprintf(stderr, "freq 70000000\t");
  assertEqual(180, funcgen.getRefClock());
  
  fprintf(stderr, "get- setARCCutOffFreq\t");
  funcgen.setARCCutOffFreq(5000);
  assertEqual(5000, funcgen.getARCCutOffFreq());
  funcgen.setARCCutOffFreq(5000000);
  assertEqual(5000000, funcgen.getARCCutOffFreq());
  funcgen.setARCCutOffFreq(50000000);
  assertEqual(30000000, funcgen.getARCCutOffFreq());

}


unittest(test_ad9851_offset)
{
  AD9851 funcgen;
  funcgen.begin(4, 5, 6);

  assertEqual(0, funcgen.getCalibration());
  funcgen.setFrequency(1000000);
  assertEqual(1000000, funcgen.getFrequency());
  for (int32_t offset = -1000; offset <= 1000; offset += 100)
  {
    funcgen.setCalibration(offset);
    fprintf(stderr, "offset %d\t", offset);
    assertEqual(offset, funcgen.getCalibration());
  }
  assertEqual(1000000, funcgen.getFrequency());

  funcgen.setCalibration();
  assertEqual(0, funcgen.getCalibration());
}

unittest(test_ad9851_float_freq)
{
  AD9851 funcgen;
  funcgen.begin(4, 5, 6);

  for (float f = 100.0; f < 110.0; f += 0.1)
  {
    funcgen.setFrequencyF(f);
    fprintf(stderr, "%ld\t", funcgen.getFactor());
    assertEqualFloat(f, funcgen.getFrequency(), 1.0);
  }
}


unittest_main()

// --------
