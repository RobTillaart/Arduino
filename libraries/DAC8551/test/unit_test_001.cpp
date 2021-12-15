//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the DAC8551
//          https://github.com/RobTillaart/
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
#include "DAC8551.h"


unittest_setup()
{
  fprintf(stderr, "DAC8551_LIB_VERSION: %s\n", (char *) DAC8551_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, DAC8551_POWERDOWN_NORMAL  );
  assertEqual(1, DAC8551_POWERDOWN_1K      );
  assertEqual(2, DAC8551_POWERDOWN_100K    );
  assertEqual(3, DAC8551_POWERDOWN_HIGH_IMP);

  assertEqual(0, DAC8501_POWERDOWN_NORMAL  );
  assertEqual(1, DAC8501_POWERDOWN_1K      );
  assertEqual(2, DAC8501_POWERDOWN_100K    );
  assertEqual(3, DAC8501_POWERDOWN_HIGH_IMP);

  assertEqual(0, DAC8531_POWERDOWN_NORMAL  );
  assertEqual(1, DAC8531_POWERDOWN_1K      );
  assertEqual(2, DAC8531_POWERDOWN_100K    );
  assertEqual(3, DAC8531_POWERDOWN_HIGH_IMP);

  assertEqual(0, DAC8550_POWERDOWN_NORMAL  );
  assertEqual(1, DAC8550_POWERDOWN_1K      );
  assertEqual(2, DAC8550_POWERDOWN_100K    );
  assertEqual(3, DAC8550_POWERDOWN_HIGH_IMP);

}


unittest(test_HW_constructor)
{
  DAC8551 myDAC(10);
  myDAC.begin();

  for (uint16_t val = 0; val < 65500; val += 30)
  {
    myDAC.setValue(val);
    if (myDAC.getValue() != val)
    {
      fprintf(stderr, "%d -> %d\n", val, myDAC.getValue());
    }
  }
  myDAC.setValue(100);
  assertEqual(100, myDAC.getValue());
}


unittest(test_SW_constructor)
{
  DAC8551 myDAC(4, 5, 6);
  myDAC.begin();
  
  for (uint16_t val = 0; val < 65500; val += 30)
  {
    myDAC.setValue(val);
    if (myDAC.getValue() != val)
    {
      fprintf(stderr, "%d -> %d\n", val, myDAC.getValue());
    }
  }
  myDAC.setValue(100);
  assertEqual(100, myDAC.getValue());
}


unittest(test_powerDown)
{
  DAC8551 myDAC(4, 5, 6);
  myDAC.begin();
  
  myDAC.setPowerDown(DAC8551_POWERDOWN_NORMAL);
  assertEqual(DAC8551_POWERDOWN_NORMAL, myDAC.getPowerDownMode());
  
  myDAC.setPowerDown(DAC8551_POWERDOWN_1K);
  assertEqual(DAC8551_POWERDOWN_1K, myDAC.getPowerDownMode());
  
  myDAC.setPowerDown(DAC8551_POWERDOWN_100K);
  assertEqual(DAC8551_POWERDOWN_100K, myDAC.getPowerDownMode());
  
  myDAC.setPowerDown(DAC8551_POWERDOWN_HIGH_IMP);
  assertEqual(DAC8551_POWERDOWN_HIGH_IMP, myDAC.getPowerDownMode());
}


unittest_main()

// --------
