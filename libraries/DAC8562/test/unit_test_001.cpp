//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-29
// PURPOSE: unit tests for the DAC8562
//          https://github.com/RobTillaart/DAC8562
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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
#include "DAC8562.h"


unittest_setup()
{
  fprintf(stderr, "DAC8562_LIB_VERSION: %s\n", (char *) DAC8562_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, DAC8562_POWERDOWN_NORMAL  );
  assertEqual(1, DAC8562_POWERDOWN_1K      );
  assertEqual(2, DAC8562_POWERDOWN_100K    );
  assertEqual(3, DAC8562_POWERDOWN_HIGH_IMP);
}


unittest(test_constructors_maxValue)
{
  DAC7562 DAC1(10);
  DAC7563 DAC2(10);
  DAC8162 DAC3(10);
  DAC8163 DAC4(10);
  DAC8562 DAC5(10);
  DAC8563 DAC6(10);

  assertEqual(DAC1.getMaxValue(), 4095);
  assertEqual(DAC2.getMaxValue(), 4095);
  assertEqual(DAC3.getMaxValue(), 16383);
  assertEqual(DAC4.getMaxValue(), 16383);
  assertEqual(DAC5.getMaxValue(), 65535);
  assertEqual(DAC6.getMaxValue(), 65535);

  DAC1.begin();
  DAC2.begin();
  DAC3.begin();
  DAC4.begin();
  DAC5.begin();
  DAC6.begin();

  assertEqual(DAC1.getValue(0), 0);
  assertEqual(DAC2.getValue(0), 2048);
  assertEqual(DAC3.getValue(0), 0);
  assertEqual(DAC4.getValue(0), 8192);
  assertEqual(DAC5.getValue(0), 0);
  assertEqual(DAC6.getValue(0), 32768);

}

unittest(test_HW_constructor)
{
  DAC8562 myDAC(10);
  myDAC.begin();

  for (uint16_t val = 0; val < 65500; val += 30)
  {
    myDAC.setValue(val);
    if (myDAC.getValue(0) != val)
    {
      fprintf(stderr, "%d -> %d\n", val, myDAC.getValue(0));
    }
  }
  myDAC.setValue(100);
  assertEqual(100, myDAC.getValue(0));
  assertEqual(100, myDAC.getValue(1));
}


unittest(test_SW_constructor)
{
  DAC8562 myDAC(4, 5, 6);
  myDAC.begin();
  
  for (uint16_t val = 0; val < 65500; val += 30)
  {
    myDAC.setValue(val);
    if (myDAC.getValue(0) != val)
    {
      fprintf(stderr, "%d -> %d\n", val, myDAC.getValue(0));
    }
  }
  myDAC.setValue(100);
  assertEqual(100, myDAC.getValue(0));
}


unittest(test_powerDown)
{
  DAC8562 myDAC(4, 5, 6);
  myDAC.begin();
  
  myDAC.setPowerDownMode(DAC8562_POWERDOWN_NORMAL);
  assertEqual(DAC8562_POWERDOWN_NORMAL, myDAC.getPowerDownMode());
  
  myDAC.setPowerDownMode(DAC8562_POWERDOWN_1K);
  assertEqual(DAC8562_POWERDOWN_1K, myDAC.getPowerDownMode());
  
  myDAC.setPowerDownMode(DAC8562_POWERDOWN_100K);
  assertEqual(DAC8562_POWERDOWN_100K, myDAC.getPowerDownMode());
  
  myDAC.setPowerDownMode(DAC8562_POWERDOWN_HIGH_IMP);
  assertEqual(DAC8562_POWERDOWN_HIGH_IMP, myDAC.getPowerDownMode());
}


unittest_main()


//  -- END OF FILE --

