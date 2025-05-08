//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-11-25
// PURPOSE: unit tests for the PCA9632 I2C LED driver
//          https://github.com/RobTillaart/PCA9632
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
#include "PCA9632.h"


unittest_setup()
{
  fprintf(stderr, "PCA9632_LIB_VERSION: %s\n", (char *) PCA9632_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "\nerror codes");
  assertEqual(PCA9632_OK         , 0x00);
  assertEqual(PCA9632_ERROR      , 0xFF);
  assertEqual(PCA9632_ERR_WRITE  , 0xFE);
  assertEqual(PCA9632_ERR_CHAN   , 0xFD);
  assertEqual(PCA9632_ERR_MODE   , 0xFC);
  assertEqual(PCA9632_ERR_REG    , 0xFB);
  assertEqual(PCA9632_ERR_I2C    , 0xFA);

  fprintf(stderr, "\nmode 1");
  assertEqual(PCA9632_MODE1_AUTOINCR2, 0x80);
  assertEqual(PCA9632_MODE1_AUTOINCR1, 0x40);
  assertEqual(PCA9632_MODE1_AUTOINCR0, 0x20);
  assertEqual(PCA9632_MODE1_SLEEP    , 0x10);
  assertEqual(PCA9632_MODE1_SUB1     , 0x08);
  assertEqual(PCA9632_MODE1_SUB2     , 0x04);
  assertEqual(PCA9632_MODE1_SUB3     , 0x02);
  assertEqual(PCA9632_MODE1_ALLCALL  , 0x01);
  assertEqual(PCA9632_MODE1_NONE     , 0x00);
  assertEqual(PCA9632_MODE1_DEFAULT  , 0x81);

  fprintf(stderr, "\nmode 2");
  assertEqual(PCA9632_MODE2_BLINK    , 0x20);
  assertEqual(PCA9632_MODE2_INVERT   , 0x10);
  assertEqual(PCA9632_MODE2_ACK      , 0x08);
  assertEqual(PCA9632_MODE2_TOTEMPOLE, 0x04);
  assertEqual(PCA9632_MODE2_NONE     , 0x00);
  assertEqual(PCA9632_MODE2_DEFAULT  , 0x02);

  fprintf(stderr, "\nledout");
  assertEqual(PCA9632_LEDOFF         , 0x00);
  assertEqual(PCA9632_LEDON          , 0x01);
  assertEqual(PCA9632_LEDPWM         , 0x02);
  assertEqual(PCA9632_LEDGRPPWM      , 0x03);
}


unittest(test_constructor_pca9632)
{
  PCA9632 RGBW(0x60);

  Wire.begin();

  assertTrue(RGBW.begin());
  assertTrue(RGBW.isConnected());
}


unittest(test_constructor_pca9633)
{
  PCA9633 RGBW(0x60);

  Wire.begin();

  assertTrue(RGBW.begin());
  assertTrue(RGBW.isConnected());
}


unittest_main()


//  -- END OF FILE --
