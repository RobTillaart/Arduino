//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-06-14
// PURPOSE: unit tests for the AD7390/ AD7391 DACs
//          https://github.com/RobTillaart/AD7390
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
#include "AD7390.h"


unittest_setup()
{
  fprintf(stderr, "AD7390_LIB_VERSION:\t%s\n", (char *) AD7390_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_begin)
{
  AD7390 myDAC(6, 7, 11, 13);
  myDAC.begin(0);
  assertEqual(0, myDAC.getValue());

  myDAC.begin(42);
  assertEqual(42, myDAC.getValue());
}


unittest(test_7390_setValue)
{
  AD7390 myDAC(6, 7, 11, 13);
  myDAC.begin(0);
  assertEqual(0, myDAC.getValue());

  for (int i = 0; i < myDAC.getMaxValue(); i += 200)
  {
    myDAC.setValue(i);
    assertEqual(i, myDAC.getValue());
  }
}


unittest(test_7391_setValue)
{
  AD7391 myDAC(6, 7, 11, 13);
  myDAC.begin(0);
  assertEqual(0, myDAC.getValue());

  for (int i = 0; i < myDAC.getMaxValue(); i += 100)
  {
    myDAC.setValue(i);
    assertEqual(i, myDAC.getValue());
  }
}


unittest(test_setPercentage)
{
  AD7390 myDAC(6, 7, 11, 13);
  myDAC.begin(0);
  assertEqual(0, myDAC.getValue());

  for (int i = 0; i < 100; i += 6.28)
  {
    myDAC.setPercentage(i);
    assertEqualFloat(i, myDAC.getPercentage(), 0.1);
  }
}


unittest(test_setVoltage)
{
  AD7390 myDAC(6, 7, 11, 13);
  myDAC.begin(0);
  assertEqual(0, myDAC.getValue());

  myDAC.setRefVoltage(5.0);
  for (float i = 0; i <= 5.0; i += 0.25)
  {
    myDAC.setVoltage(i);
    assertEqualFloat(i, myDAC.getVoltage(), 0.1);
  }
}


unittest(test_setRefVoltage)
{
  AD7390 myDAC(6, 7, 11, 13);
  myDAC.begin(0);
  assertEqual(0, myDAC.getValue());

  assertFalse(myDAC.setRefVoltage(-1.0));
  assertFalse(myDAC.setRefVoltage(5.6));
  assertTrue(myDAC.setRefVoltage(0.0));

  assertTrue(myDAC.setRefVoltage(5.5));
  assertFalse(myDAC.setVoltage(-1.0));
  assertTrue(myDAC.setVoltage(5.0));

  assertTrue(myDAC.setRefVoltage(2.5));
  assertFalse(myDAC.setVoltage(5.0));
  assertTrue(myDAC.setVoltage(2.0));
}


unittest_main()


//  -- END OF FILE --
