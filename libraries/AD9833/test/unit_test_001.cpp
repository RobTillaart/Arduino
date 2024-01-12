//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-27
// PURPOSE: unit tests for the AD9833 function generator
//          https://github.com/RobTillaart/AD9833
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
#include "AD9833.h"


unittest_setup()
{
  fprintf(stderr, "AD9833_LIB_VERSION: %s\n", AD9833_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(12500000UL, AD9833_MAX_FREQ);
  assertEqual(360, AD9833_MAX_PHASE);

  assertEqual(0, AD9833_OFF);
  assertEqual(1, AD9833_SINE);
  assertEqual(2, AD9833_SQUARE1);
  assertEqual(3, AD9833_SQUARE2);
  assertEqual(4, AD9833_TRIANGLE);
}


unittest(test_constructor)
{
  AD9833 funcgen(10);
  AD9833 fgsw(4,5,6);

  funcgen.begin();
  fgsw.begin();

  assertEqual(AD9833_MAX_FREQ, funcgen.getMaxFrequency());
  assertEqual(AD9833_MAX_PHASE, funcgen.getMaxPhase());

  assertTrue(funcgen.usesHWSPI());
  assertFalse(fgsw.usesHWSPI());
}


unittest(test_wave)
{
  AD9833 funcgen(4, 5, 6);
  funcgen.begin();

  for (long wave = 0; wave < 5; wave++)
  {
    funcgen.setWave(wave);
    int w = funcgen.getWave();
    assertEqual(w, wave);
  }
}


unittest(test_frequency)
{
  AD9833 funcgen(4, 5, 6);
  funcgen.begin();

  for (float freq = 10; freq <= 10000000; freq *= 10)
  {
    funcgen.setFrequency(freq);
    float fr = funcgen.getFrequency();
    assertEqualFloat(fr, freq, 1);
  }
}


unittest(test_phase)
{
  AD9833 funcgen(4, 5, 6);
  funcgen.begin();

  for (int ph = 0; ph < 360; ph += 30)
  {
    funcgen.setPhase(ph);
    int phase = funcgen.getPhase();
    assertEqual(ph, phase);
  }
}


unittest(test_crystal)
{
  AD9833 funcgen(4, 5, 6);
  funcgen.begin();

  for (float freq = 1000000; freq <= 25000000; freq += 3000000)
  {
    funcgen.setCrystalFrequency(freq);
    float fr = funcgen.getCrystalFrequency();
    assertEqualFloat(fr, freq, 1);
  }
}


unittest_main()


//  -- END OF FILE --


