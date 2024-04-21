//
//    FILE: I2C_eeprom_verifyBlock.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_EEPROM library
//     URL: https://github.com/RobTillaart/I2C_EEPROM
//
// uses a 24LC256 (32KB) EEPROM


#include "Wire.h"
#include "I2C_eeprom.h"

I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, dur1;

char buffer[] = "12345678901234567890123456789012345678901234567890";  //  50 bytes

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

  delay(10);

  //////////////////////////////////////////////////////////////////////

  Serial.println("\nTEST: writeBlock()");
  delay(10);
  start = micros();
  ee.writeBlock(0, (uint8_t *) buffer, 50);
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  delay(10);

  Serial.println("\nTEST: verifyBlock() no change");
  delay(10);
  start = micros();
  if (ee.verifyBlock(0, (uint8_t *) buffer, 50) == false)
  {
    Serial.print("X");
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  delay(10);


  for (uint8_t loc = 0; loc < 50; loc += 5)
  {
    disrupt(loc);
  }

  Serial.println("done...");
}


void loop()
{
}


void disrupt(uint8_t location)
{
  bool flag = true;
  //  disrupt memory
  Serial.print("\nTEST: verifyBlock() after change @ ");
  Serial.println(location);
  delay(10);
  ee.writeBlock(0, (uint8_t *) buffer, 50);
  ee.writeByte(location, 255);

  start = micros();
  if (ee.verifyBlock(0, (uint8_t *) buffer, 50) == false)
  {
    flag = false;
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  Serial.println(flag);
  delay(10);
}



//  -- END OF FILE --
