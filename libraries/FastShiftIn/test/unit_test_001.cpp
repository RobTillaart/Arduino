//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the FastShiftIn library
//          https://github.com/RobTillaart/FastShiftIn
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


#include "Arduino.h"
#include "FastShiftIn.h"


// PATCH FOR DUE & ZERO FOR UNIT TEST - https://github.com/Arduino-CI/arduino_ci/issues/252
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
// - due         #  ARDUINO_ARCH_SAM    does not support shiftIn apparently
// - zero        #  ARDUINO_ARCH_SAMD   
#endif


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  FastShiftIn FSI(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTIN_LIB_VERSION);
  assertEqual(0, FSI.lastRead());
  assertEqual(LSBFIRST, FSI.getBitOrder());
  
  FSI.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, FSI.getBitOrder());
}


unittest(test_constructor_LSB)
{
  FastShiftIn FSI(12, 13, LSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTIN_LIB_VERSION);
  assertEqual(0, FSI.lastRead());
  assertEqual(LSBFIRST, FSI.getBitOrder());
  
  FSI.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, FSI.getBitOrder());
}


unittest(test_constructor_MSB)
{
  FastShiftIn FSI(12, 13, MSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTIN_LIB_VERSION);
  assertEqual(0, FSI.lastRead());
  assertEqual(MSBFIRST, FSI.getBitOrder());
  
  FSI.setBitOrder(LSBFIRST);
  assertEqual(LSBFIRST, FSI.getBitOrder());
}


unittest(test_read)
{
  FastShiftIn FSI(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", FASTSHIFTIN_LIB_VERSION);

// apparently needed... To be investigated someday ...
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)

  assertEqual(0, FSI.read());
  assertEqual(0, FSI.readLSBFIRST());
  assertEqual(0, FSI.readMSBFIRST());

#else  // AVR

  assertEqual(255, FSI.read());
  assertEqual(255, FSI.readLSBFIRST());
  assertEqual(255, FSI.readMSBFIRST());
  
#endif
}


unittest_main()

// --------
