//
//    FILE: I2C_eeprom_format.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo format EEPROM
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


  Serial.println();
  uint32_t size = ee.determineSize(false);  //  debug parameter
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


  // flush input
  while (Serial.available()) Serial.read();

  Serial.println("Sure to format EEPROM? [Y | N]");
  while (!Serial.available());
  int ans =  Serial.read();

  if ( ans == 'Y')
  {
    start = millis();
    for (uint32_t address = 0; address < size; address += 128)
    {
      if (address % 1024 == 0) Serial.print('.');
      ee.setBlock(address, 0xFF, 128);
    }
    diff = millis() - start;
    Serial.print("\nTIME: ");
    Serial.print(diff);
    Serial.println(" ms.");
  }
  else
  {
    Serial.println("not formatted");
  }

  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --
