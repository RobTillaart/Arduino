//
//    FILE: 24LC1025_test_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


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

  Serial.println("\nwriting and reading in the low block");
  ee.writeByte(0, 21);
  ee.writeByte(1, 22);
  Serial.println(ee.readByte(0));
  Serial.println(ee.readByte(1));


  Serial.println("\nwriting and reading in the high block");
  ee.writeByte(65536, 'A');
  Serial.println(ee.readByte(65536));


  Serial.println("\nwriting and reading in the low block");
  char buf1[24] = "aabbccddeeffgghhiijj";
  char buf2[24];
  ee.writeBlock(120, (uint8_t*) buf1, strlen(buf1) + 1);
  dump(96, 160);
  ee.readBlock(120, (uint8_t*) buf2, strlen(buf1) + 1);
  Serial.println(buf2);
  ee.setBlock(120, 42, strlen(buf1) + 1);
  dump(96, 160);


  Serial.println("\nwriting and reading in the high block");
  char buf3[24] = "aabbccddeeffgghhiijj";
  char buf4[24];
  ee.writeBlock(0x10000 + 120, (uint8_t*) buf3, (uint32_t)strlen(buf3) + 1);
  dump(0x10000 + 96, 0x10000 + 160);
  ee.readBlock(0x10000 + 120, (uint8_t*) buf4, (uint32_t)strlen(buf3) + 1);
  buf4[20] = 0;
  Serial.println(buf4);

  ee.setBlock(0x10000 + 120, 42, strlen(buf3) + 1);
  dump(0x10000 + 96, 0x10000 + 160);
  ee.readBlock(0x10000 + 120, (uint8_t*) buf4, strlen(buf3) + 1);
  buf4[20] = 0;
  Serial.println(buf4);


  Serial.println("\nwriting over block boundary block");
  ee.writeBlock(0xFFF0, (uint8_t *) "012345678901234567890123456789012345", (uint32_t) 32);
  dump(0xFFE0, 0x10020);

  char buf5[64];
  ee.readBlock(0xFFF0, (uint8_t *)buf5, (uint32_t)32);
  buf5[32] = 0;
  Serial.println(buf5);

  Serial.println("\nreadBlock timing 32 bytes");
  start = micros();
  ee.readBlock(0x0000, (uint8_t *)buf5, (uint32_t)32);
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  ee.readBlock(0xFFF0, (uint8_t *)buf5, (uint32_t)32);
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  ee.readBlock(0x1F0000, (uint8_t *)buf5, (uint32_t)32);
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  delay(10);


  /*
    start = micros();
    dump(0x00, 0x0FFFF);  // First block of 64K
    stop = micros();
    Serial.print("\nTIME: \t");
    Serial.println(stop - start);
  */

  // dump(0xFFF0, 0x1000F);
  // test(65530);
  Serial.println("\nDone...");
}


void loop()
{
}


void dump(uint32_t from, uint32_t to)
{
  for (uint32_t i = from; i < to; i++)  //  I2C_DEVICESIZE_24LC1025
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
#endif
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


//  -- END OF FILE --

