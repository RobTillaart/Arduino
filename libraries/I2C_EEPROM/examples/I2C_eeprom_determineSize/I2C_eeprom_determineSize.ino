//
//    FILE: I2C_eeprom_determineSize.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test determinSize() function
//


#include "Wire.h"
#include "I2C_eeprom.h"


I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, diff;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("I2C_EEPROM_VERSION: ");
  Serial.println(I2C_EEPROM_VERSION);

  ee.begin();
  if (! ee.isConnected())
  {
    Serial.println("ERROR: Can't find eeprom\nstopped...");
    while (1);
  }

  Serial.println("\nDetermine size");
  delay(10);

  start = micros();
  uint32_t size = ee.determineSize(false);  // debug param
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.print(diff);
  Serial.println(" us.");
  if (size == 0)
  {
    Serial.println("SIZE: could not determine size");
  }
  else if (size > 1024)
  {
    Serial.print("SIZE: ");
    Serial.print(size / 1024);
    Serial.println(" KB.");
  }
  else
  {
    Serial.print("SIZE: ");
    Serial.print(size);
    Serial.println(" bytes.");
  }

  Serial.print("PAGE: ");
  uint8_t pageSize = ee.getPageSize(size);
  Serial.print(pageSize);
  Serial.println(" bytes.");

  Serial.println("Done...");
}


void loop()
{
}

// -- END OF FILE --
