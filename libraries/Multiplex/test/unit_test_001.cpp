//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-09
// PURPOSE: unit tests for the Multiplex
//          https://github.com/RobTillaart/Multiplex
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
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
#include "Multiplex.h"


//  A simple implementation of Print that outputs
//  to Serial, prefixing each call to write(buffer, size)
//  with an id.
class FakeStream : public Print
{
  public:
  FakeStream(uint8_t id) : _id(id) { _id = id; };
  
  virtual size_t write(uint8_t c) override 
  { 
    return Serial.write(c);
  };
  
  virtual size_t write(const uint8_t *buffer, size_t size) 
  {
    size_t n = 0;
    n += Serial.print("stream");
    n += Serial.print(_id, DEC);
    n += Serial.print(':');
        
    for (uint8_t i = 0 ; i < size ; i++)
    {
      n += write(buffer[i]);
    }
    return n;
  }
  private: 
  uint8_t _id = 0;
};


unittest_setup()
{
  fprintf(stderr, "MULTIPLEX_LIB_VERSION: %s\n", (char *) MULTIPLEX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Multiplex mp;
  assertEqual(0, mp.count());
  assertEqual(4, mp.size());

  FakeStream stream1(1);
  FakeStream stream2(2);

  assertTrue(mp.add(&stream1));
  assertTrue(mp.add(&stream2));
  assertEqual(2, mp.count());
  assertEqual(4, mp.size());
  
  mp.reset();
  assertEqual(0, mp.count());
  assertEqual(4, mp.size());
}


unittest(test_enable)
{
  Multiplex mp;
  FakeStream stream1(1);
  FakeStream stream2(2);

  assertTrue(mp.add(&stream1));
  assertTrue(mp.add(&stream2));

  for (int i = 0; i < mp.count(); i++)
  {
    assertTrue(mp.isEnabled(i));
    mp.disable(i);
    assertFalse(mp.isEnabled(i));
    mp.enable(i);
    assertTrue(mp.isEnabled(i));
  }

  assertTrue(mp.isEnabledStream(&stream1));
  assertTrue(mp.isEnabledStream(&stream2));

  mp.disableStream(&stream1);
  mp.disableStream(&stream2);

  assertFalse(mp.isEnabledStream(&stream1));
  assertFalse(mp.isEnabledStream(&stream2));
}


unittest_main()


//  -- END OF FILE --
