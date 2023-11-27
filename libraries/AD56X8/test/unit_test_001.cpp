//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-07-28
// PURPOSE: unit tests for the AD56X8 DA convertor.
//          https://github.com/RobTillaart/AD56X8
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
#include "AD56X8.h"



unittest_setup()
{
  fprintf(stderr, "AD56X8_LIB_VERSION: %s\n", (char *) AD56X8_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(constant)
{
  assertEqual(0x00, AD56X8_PWR_NORMAL    );
  assertEqual(0x01, AD56X8_PWR_1K        );
  assertEqual(0x02, AD56X8_PWR_100K      );
  assertEqual(0x03, AD56X8_PWR_TRI_STATE );

  assertEqual(0x00, AD56X8_CC_0000 );
  assertEqual(0x01, AD56X8_CC_8000 );
  assertEqual(0x02, AD56X8_CC_FFFF );
  assertEqual(0x03, AD56X8_CC_NOP  );
}


unittest(constructors)
{
  AD56X8 AD0(8);
  AD5668 AD16(9);
  AD5648 AD14(10, 11, 12);
  AD5628 AD12(4, 5, 6);
  AD5668_3 AD16M(7, 3, 2);

  assertTrue(AD0.usesHWSPI());
  assertTrue(AD16.usesHWSPI());
  assertFalse(AD14.usesHWSPI());
  assertFalse(AD12.usesHWSPI());
  assertFalse(AD16M.usesHWSPI());
}


unittest(get_type)
{
  AD56X8 AD0(8);
  AD5668 AD16(9);
  AD5648 AD14(10, 11, 12);
  AD5628 AD12(4, 5, 6);
  AD5668_3 AD16M(7);

  assertEqual(0, AD0.getType());
  assertEqual(16, AD16.getType());
  assertEqual(14, AD14.getType());
  assertEqual(12, AD12.getType());
  assertEqual(16, AD16M.getType());
}


unittest(get_setValue)
{
  AD5628 AD0(8);  //  12 bit  0..4096

  AD0.begin();

  //  valid channels
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertTrue(AD0.setValue(chan, chan * 100));
  }
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertEqual(chan * 100, AD0.getValue(chan));
  }

  //  channel out of range test.
  assertFalse(AD0.setValue(8, 0));
  //  value out of range
  assertFalse(AD0.setValue(0, 4096));
  assertFalse(AD0.setValue(0, 65535));
}


unittest(get_setPercentage)
{
  AD5648 AD0(8);  //  14 bit  0..16383

  AD0.begin();

  //  valid channels
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertTrue(AD0.setPercentage(chan, chan * 8));
  }
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertEqualFloat(chan * 8, AD0.getPercentage(chan), 0.1);
  }

  //  channel out of range test.
  assertFalse(AD0.setPercentage(8, 0));
  //  value out of range
  assertFalse(AD0.setPercentage(0, -1));
  assertFalse(AD0.setPercentage(0, 101));
}


unittest(get_PowerUpValue)
{
  AD56X8 AD0(8);
  AD5668_3 AD16M(7);

  AD0.begin();
  AD16M.begin();

  //  valid channels  0 Volts
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertEqual(0, AD0.getValue(chan));
  }
  //  valid channels  0 Volts
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertEqual(32768, AD16M.getValue(chan));
  }

  //  invalid channel returns 0.
  assertEqual(0, AD16M.getValue(8));
}


unittest(prepareChannel)
{
  AD56X8 AD0(8);

  AD0.begin();

  //  valid channels
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertTrue(AD0.prepareChannel(chan, chan * 100));
  }
  for (uint8_t chan = 0; chan < 8; chan++)
  {
    assertEqual(chan * 100, AD0.getValue(chan));
  }

  //  channel out of range test.
  assertFalse(AD0.prepareChannel(8, 0));
}


unittest(set_power_mode)
{
  AD56X8 AD0(8);

  AD0.begin();

  assertTrue(AD0.setPowerMode(0, 0));
  assertTrue(AD0.setPowerMode(1, 0));
  assertTrue(AD0.setPowerMode(2, 0));
  assertTrue(AD0.setPowerMode(3, 0));

  //  powerMode out of range test.
  assertFalse(AD0.setPowerMode(4, 0));
}


unittest(set_clear_code)
{
  AD56X8 AD0(8);

  AD0.begin();

  assertTrue(AD0.setClearCode(0));
  assertTrue(AD0.setClearCode(1));
  assertTrue(AD0.setClearCode(2));

  //  CCMode out of range test.
  assertFalse(AD0.setClearCode(4));
}


unittest_main()


//  -- END OF FILE --
