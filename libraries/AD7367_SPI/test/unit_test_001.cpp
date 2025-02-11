//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-10
// PURPOSE: unit tests for the Arduino library for the AD7367, 2 channel consecutive sampling 14 bit ADC.
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
#include "AD7367_SPI.h"



unittest_setup()
{
  fprintf(stderr, "AD7367_SPI_LIB_VERSION: %s\n", (char *) AD7367_SPI_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constructors)
{
  //  select, convert, busy, SPI (optional)
  AD7367_SPI AD(5, 6, 7);

  SPI.begin();

  AD.begin();

  assertEqual(0, AD.getValue(0));
  assertEqual(0, AD.getValue(1));
}


unittest(get_type)
{
  //  select, convert, busy, SPI (optional)
  AD7367_SPI AD0(5, 6, 7);
  AD7366_SPI AD1(8, 9, 10);

  SPI.begin();

  AD0.begin();
  AD1.begin();

  assertEqual(67, AD0.getType());
  assertEqual(66, AD1.getType());
}


unittest(get_bits)
{
  //  select, convert, busy, SPI (optional)
  AD7367_SPI AD0(5, 6, 7);
  AD7366_SPI AD1(8, 9, 10);

  SPI.begin();

  AD0.begin();
  AD1.begin();

  assertEqual(14, AD0.getBits());
  assertEqual(12, AD1.getBits());
}


unittest_main()


//  -- END OF FILE --
