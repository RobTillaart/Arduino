//
//    FILE: I2C_eeprom_updateBlock.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_EEPROM library - performance gain updateBlock
//     URL: https://github.com/RobTillaart/I2C_EEPROM
//
// uses a 24LC256 (32KB) EEPROM
// as this test writes a lot it might wear out EEPROMs eventually.


#include "Wire.h"
#include "I2C_eeprom.h"


I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, dur1, dur2;

uint8_t ar[100];


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

  for (int i = 0; i < 100; i++) ar[i] = 100 - i;

  for (int i = 1; i < 11; i++)
  {
    test_1(i);
  }

  test_2();

  Serial.println("\ndone...");
}


void loop()
{
}


void test_1(int n)
{
  Serial.println(n);
  Serial.print("TEST:\twriteBlock()");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < n; i++) ee.writeBlock(0, ar, 100);
  dur1 = micros() - start;
  Serial.print("\t");
  Serial.println(dur1);
  delay(10);

  Serial.print("TEST:\treadBlock()");
  delay(10);
  start = micros();
  for (int i = 0; i < n; i++) ee.readBlock(0, ar, 100);
  dur1 = micros() - start;
  Serial.print("\t");
  Serial.println(dur1);
  delay(10);

  Serial.print("TEST:\tupdateBlock()");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < n; i++) ee.updateBlock(0, ar, 100);
  dur1 = micros() - start;
  Serial.print("\t");
  Serial.println(dur1);
  delay(10);
  Serial.println();
}


void test_2()
{
  Serial.println("\nTEST: 100x writeBlock()");
  delay(10);
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    ee.writeBlock(0, ar, 100);
  }
  dur1 = micros() - start;
  Serial.print("DUR1: ");
  Serial.println(dur1);
  dump(0, 100);
  delay(100);


  Serial.println("\nTEST: 100x updateBlock()");
  ee.setBlock(0, 0, 100);  //  clear first 100 bytes
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    ee.updateBlock(0, ar, 100);
  }
  dur2 = micros() - start;
  Serial.print("DUR2: ");
  Serial.println(dur2);
  dump(0, 100);
  delay(100);
}


void dump(uint32_t from, uint32_t to)
{
  for (uint32_t i = from; i < to; i++)  //  I2C_DEVICESIZE_24LC512
  {
    char buffer[24];
    if (i % 16 == 0)
    {
      char buffer[24];
      Serial.print('\n');
#if defined (ESP8266) || defined(ESP32)
      sprintf(buffer, "%08X\t", i);   //  ESP cast (long unsigned int)
#else
      sprintf(buffer, "%08lX\t", i);  //  AVR needs lX
#endif;
      Serial.print(buffer);
    }
    sprintf(buffer, "%02X\t", ee.readByte(i));
    Serial.print(buffer);
  }
  Serial.println();
}


//  -- END OF FILE --

