//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-11-04
// PURPOSE: unit tests for the FastShiftIn library
//          https://github.com/RobTillaart/FastShiftInOut
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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
// assertNotNull(actual)


#include <ArduinoUnitTests.h>

#include "FastShiftInOut.h"


unittest_setup()
{
  fprintf(stderr, "FASTSHIFTINOUT_LIB_VERSION: %s\n", (char *) FASTSHIFTINOUT_LIB_VERSION);
}


unittest_teardown()
{
}



unittest(test_constructor)
{
  FastShiftInOut FSIO(8,9,10);

  assertEqual(LSBFIRST, FSIO.getBitOrder());

  FSIO.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, FSIO.getBitOrder());
}


unittest(test_constructor_LSB)
{
  FastShiftInOut FSIO(8,9,10, LSBFIRST);

  assertEqual(LSBFIRST, FSIO.getBitOrder());

  FSIO.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, FSIO.getBitOrder());
}


unittest(test_constructor_MSB)
{
  FastShiftInOut FSIO(8,9,10, MSBFIRST);

  assertEqual(MSBFIRST, FSIO.getBitOrder());
  
  FSIO.setBitOrder(LSBFIRST);
  assertEqual(LSBFIRST, FSIO.getBitOrder());
}


/*  need godmode to test this appropriately
unittest(test_write)
{
  FastShiftInOut FSIO(8,9,10);

  assertEqual(1, FSIO.write(0x42));
  assertEqual(1, FSIO.writeLSBFIRST(0xAA));
  assertEqual(1, FSIO.writeMSBFIRST(0x55));
}
*/


/*  Print interface not implemented (yet)
unittest(test_print)
{
  FastShiftInOut FSIO(8,9,10);;

  assertEqual(5, FSIO.print(FASTSHIFTINOUT_LIB_VERSION));
  assertEqual(7, FSIO.println(FASTSHIFTINOUT_LIB_VERSION));
}
*/


unittest_main()


//  -- END OF FILE --

