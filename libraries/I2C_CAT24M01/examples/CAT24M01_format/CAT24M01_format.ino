//
//    FILE: CAT24M01_format.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: clear CAT24M01 EEPROM
//     URL: https://github.com/RobTillaart/I2C_CAT24M01


#include "I2C_CAT24M01.h"

I2C_CAT24M01 ee(0x50);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_CAT24M01_LIB_VERSION: ");
  Serial.println(I2C_CAT24M01_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (! ee.begin())
  {
    Serial.println("EEPROM not found...");
    while (1);
  }

  Serial.println("Formatting takes 32 dots ( < 45 seconds).");

  start = millis();
  for (uint32_t i = 0; i < I2C_DEVICESIZE_CAT24M01; i+=128)
  {
    if (i % 0x1000 == 0) Serial.print('.');
    ee.setBlock(i, 0x00, 128);
  }
  stop = millis();

  Serial.print("\nTIME: \t");
  Serial.println(stop - start);
  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

