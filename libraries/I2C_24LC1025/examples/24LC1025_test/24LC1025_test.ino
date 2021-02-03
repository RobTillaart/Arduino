//
//    FILE: 24LC1025_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020
//    (c) : MIT
//


#include "I2C_24LC1025.h"

I2C_24LC1025 ee(0x50);


uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  if (! ee.begin())
  {
    Serial.println("EEPROM not found...");
    while (1);
  }

  ee.writeByte(0, 21);
  ee.writeByte(1, 22);
  ee.writeByte(65536, 'A');

  Serial.println(ee.readByte(0));
  Serial.println(ee.readByte(65536));

  start = micros();
  dump(0x00, 0x0FFFF);  // First block of 64K
  stop = micros();
  Serial.print("\nTIME: \t");
  Serial.println(stop - start);

  // dump(0xFFF0, 0x1000F);
  // test(65530);
  Serial.println("\nDone...");
}

void loop()
{
}


void dump(uint32_t from, uint32_t to)
{
  for (uint32_t i = from; i < to; i++)  // I2C_DEVICESIZE_24LC512
  {
    volatile int x = ee.readByte(i);
    char buffer[24];
    if (i % 16 == 0)
    {
      char buffer[24];
      Serial.print('\n');
      sprintf(buffer, "%08lX\t", i);
      Serial.print(buffer);
    }
    sprintf(buffer, "%02X\t", ee.readByte(i));
    Serial.print(buffer);
  }
  Serial.println();
}



void test(uint32_t offset)
{
  Serial.println();

  for (int i = 0; i < 10; i++)
  {
    ee.writeByte(offset + i, i);
    Serial.println(offset + i);
    delay(10);
  }

  for (int i = 0; i < 10; i++)
  {
    if (i % 10 == 0) Serial.print('\n');
    Serial.print(ee.readByte(offset + i));
    Serial.print('\t');
    delay(10);
  }
  Serial.print('\n');
}



// -- END OF FILE --
