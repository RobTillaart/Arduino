//
//    FILE: I2C_eeprom_verify.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_EEPROM library - updateByte
//     URL: https://github.com/RobTillaart/I2C_EEPROM
//
// uses a 24LC256 (32KB) EEPROM


#include "Wire.h"
#include "I2C_eeprom.h"

#define NN   100

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

  Serial.print("\nTestruns NN: ");
  Serial.print(NN);
  Serial.println("\n");
  Serial.println("\nTEST: NN x writeByte()");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    ee.writeByte(i, 0);
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  delay(10);

  Serial.println("\nTEST: NN x writeByteVerify()");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.writeByteVerify(i, 0) == false)
    {
      Serial.print("X");
    }
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  delay(10);

  //////////////////////////////////////////////////////////////////////

  Serial.println("\nTEST: NN x updateByte() same data");
  delay(10);
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    ee.updateByte(i, 0);
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  Serial.println("\nTEST: NN x updateByteVerify() same data");
  delay(10);
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.updateByteVerify(i, 0) == false)
    {
      Serial.print("X");
    }
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  Serial.println("\nTEST: NN x updateByteVerify() not same data");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.updateByteVerify(i, i) == false)
    {
      Serial.print("X");
    }
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  //////////////////////////////////////////////////////////////////////

  char buffer[] = "12345678901234567890123456789012345678901234567890";  //  50 bytes
  Serial.println("\nTEST: NN x writeBlock()");
  delay(10);
  ee.setBlock(0, 0, 100);  // clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    ee.writeBlock(0, (uint8_t *) buffer, 50);
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  delay(10);


  Serial.println("\nTEST: NN x writeBlockVerify()");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.writeBlockVerify(0, (uint8_t *) buffer, 50) == false)
    {
      Serial.print("X");
    }
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  delay(10);

  //////////////////////////////////////////////////////////////////////

  Serial.println("\nTEST: NN x updateBlock() same data");
  delay(10);
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    ee.updateBlock(0, (uint8_t *) buffer, 50);
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);


  Serial.println("\nTEST: NN x updateBlockVerify() same data");
  delay(10);
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.updateBlockVerify(0, (uint8_t *) buffer, 50) == false)
    {
      Serial.print("X");
    }
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  strcpy(buffer, "98765432109876543210987654321098765432109876543210");  //  50 bytes
  Serial.println("\nTEST: NN x updateBlockVerify() not same data");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.updateBlockVerify(0, (uint8_t *) buffer, 50) == false)
    {
      Serial.print("X");
    }
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  //////////////////////////////////////////////////////////////////////

  Serial.println("\nTEST: NN x setBlock() same data");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    ee.setBlock(0, 0, 50);
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  Serial.println("\nTEST: NN x setBlockVerify() same data");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.setBlockVerify(0, 0, 50) == false)
    {
      Serial.print("X");
    }
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  delay(10);

  Serial.println("\nTEST: NN x setBlockVerify() not same data");
  delay(10);
  start = micros();
  for (int i = 0; i < NN; i++)
  {
    if (ee.setBlockVerify(0, 1, 50) == false)
    {
      Serial.print("X");
    }
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
