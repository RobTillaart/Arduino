//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-11-23
// PURPOSE: unit tests for the NeumannCorrector
//          https://github.com/RobTillaart/HC4067
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
#include "NeumannCorrector.h"


unittest_setup()
{
  fprintf(stderr, "NEUMANNCORRECTOR_LIB_VERSION: %s\n", (char *) NEUMANNCORRECTOR_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  NeumannCorrector NC;

  assertEqual(32, NC.size());
}


unittest(test_add)
{
  NeumannCorrector NC;
  for (int i = 0; i < 256; i++)
  {
    NC.add(i);
    if (NC.available())
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.println(NC.get());
    }
  }
  assertEqual(32, NC.size());
}


unittest(test_get)
{
  NeumannCorrector NC;

  for (int i = 0; i < 256; i++)
  {
    NC.add(i);
  }
  for (int i = 0; i < 5; i++)
  {
    NC.get();
  }
  assertEqual(0, NC.available());

  for (int i = 0; i < 256; i++)
  {
    NC.add(i);
  }
  NC.clear();
  assertEqual(0, NC.available());
}


unittest(test_clear)
{
  NeumannCorrector NC;

  for (int i = 0; i < 256; i++)
  {
    NC.add(i);
  }
  NC.clear();
  assertEqual(0, NC.available());
  assertEqual(0, NC.get());
}


unittest_main()


//  -- END OF FILE --

