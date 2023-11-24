//
//    FILE: 24LC1025_format.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: clear 24LC1025 EEPROM
//    DATE: 2021-01-27


#include "I2C_24LC1025.h"

I2C_24LC1025 ee(0x50);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("I2C_24LC1025_LIB_VERSION: ");
  Serial.println(I2C_24LC1025_LIB_VERSION);

  Wire.begin();

  if (! ee.begin())
  {
    Serial.println("EEPROM not found...");
    while (1);
  }

  Serial.println("Formatting takes 32 dots ( < 45 seconds).");

  start = millis();
  for (uint32_t i = 0; i < I2C_DEVICESIZE_24LC1025; i+=128)
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

