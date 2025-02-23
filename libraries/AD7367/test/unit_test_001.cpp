//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-25
// PURPOSE: unit tests for the Arduino library for the AD7367, 2 channel simultaneous sampling 14 bit ADC.
//          https://github.com/RobTillaart/AD7367
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
#include "AD7367.h"



unittest_setup()
{
  fprintf(stderr, "AD7367_LIB_VERSION: %s\n", (char *) AD7367_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constructors)
{
  //  select, clock, convert, busy, data0, data1
  AD7367 AD(5, 6, 7, 8, 9, 10);

  AD.begin();

  assertEqual(0, AD.getValue(0));
  assertEqual(0, AD.getValue(1));
}


unittest(get_type)
{
  //  select, clock, convert, busy, data0, data1
  AD7367 AD0(5, 6, 7, 8, 9, 10);
  AD7366 AD1(5, 6, 7, 8, 9, 10);

  AD0.begin();
  AD1.begin();

  assertEqual(67, AD0.getType());
  assertEqual(66, AD1.getType());
}


unittest(get_bits)
{
  //  select, clock, convert, busy, data0, data1
  AD7367 AD0(5, 6, 7, 8, 9, 10);
  AD7366 AD1(5, 6, 7, 8, 9, 10);

  AD0.begin();
  AD1.begin();

  assertEqual(14, AD0.getBits());
  assertEqual(12, AD1.getBits());
}


unittest_main()


//  -- END OF FILE --
