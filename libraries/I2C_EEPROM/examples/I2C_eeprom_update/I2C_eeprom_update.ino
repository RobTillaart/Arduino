//
//    FILE: I2C_eeprom_update.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_EEPROM library - updateByte
//     URL: https://github.com/RobTillaart/I2C_EEPROM
//
//  uses a 24LC256 (32KB) EEPROM


#include "Wire.h"
#include "I2C_eeprom.h"


I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, dur1, dur2;


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

  Serial.println("\nTEST: determine size");
  uint32_t size = ee.determineSize();
  if (size > 0)
  {
    Serial.print("SIZE: ");
    Serial.print(size);
    Serial.println(" KB");
  }
  else if (size == 0)
  {
    Serial.println("WARNING: Can't determine eeprom size");
  }
  else
  {
    Serial.println("ERROR: Can't find eeprom\nstopped...");
    while(1);
  }

  Serial.println("\nTEST: 100x writebyte()");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    ee.writeByte(i, 0);
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  delay(10);

  Serial.println("\nTEST: 100x updateByte()");
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    ee.updateByte(i, 0);
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

