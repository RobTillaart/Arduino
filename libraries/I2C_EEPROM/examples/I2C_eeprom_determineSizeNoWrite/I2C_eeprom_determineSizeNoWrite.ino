//
//    FILE: I2C_eeprom_determineSizeNoWrite.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test determineSizeNoWrite() function
//     URL: https://github.com/RobTillaart/I2C_EEPROM


#include "Wire.h"
#include "I2C_eeprom.h"


I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, diff;


void setup()
{
  Serial.begin(115200);
  while (!Serial);  //  wait for Serial port to connect. Needed for Leonardo only
  Serial.println(__FILE__);
  Serial.print("I2C_EEPROM_VERSION: ");
  Serial.println(I2C_EEPROM_VERSION);

  Wire.begin();

  ee.begin();
  if (! ee.isConnected())
  {
    Serial.println("ERROR: Can't find eeprom\nstopped...");
    while (1);
  }

  Serial.println("\nDetermine size no write");
  delay(100);

  start = micros();
  uint32_t size = ee.determineSizeNoWrite();
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.print(diff);
  Serial.println(" us.");
  if (size == 0)
  {
    Serial.println("SIZE: could not determine size");
  }
  else if (size == 1)
  {
      Serial.println("SIZE: device has default data in first bytes, write some data and retry or use the determineSize method");
  }
  else if (size == 2)
  {
      Serial.println("SIZE: device has all the same data in first bytes, write some data and retry");
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


//  -- END OF FILE --
