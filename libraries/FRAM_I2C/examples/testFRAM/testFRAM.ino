//
//    FILE: testFRAM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for FRAM library for Arduino
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"


FRAM fram;

uint32_t start;
uint32_t stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Wire.begin();

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.println(rv);
  }
  else
  {
    testID();
    testFRAMmemory();
    testReadWriteSmall();
    testReadWriteLarge();
    testWriteText();
    testReadText1();
    testReadText2();
  }
  Serial.println("done...");
}


void loop()
{
}


void testID()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print("ManufacturerID: ");
  Serial.println(fram.getManufacturerID());
  Serial.print("     ProductID: ");
  Serial.println(fram.getProductID());
  Serial.print("     memory KB: ");
  Serial.println(fram.getSize());

  Serial.println();
}


void testFRAMmemory()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println("takes ~32 seconds");

  start = millis();
  uint8_t val = 0x55;
  for (uint16_t addr = 0; addr < 32768; addr++)
  {
    fram.write8(addr, val);
    if (fram.read8(addr) != 0x55)
    {
      Serial.print("FAIL: \t");
      Serial.println(addr);
    }
    if (addr % 1000 == 0)
    {
      Serial.print(".");
    }
  }
  stop = millis();
  Serial.println();
  Serial.print("TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");
  Serial.println();
}


void testReadWriteSmall()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.print("test8:\t");
  uint8_t t8 = 0xFE;
  fram.write8(1000, t8);
  if (fram.read8(1000) != 0xFE)
  {
    Serial.println("failed.");
  }
  else
  {
    Serial.println("ok.");
  }

  Serial.print("test16:\t");
  uint16_t t16 = 0xFADE;
  fram.write16(1000, t16);
  if (fram.read16(1000) != 0xFADE)
  {
    Serial.println("failed.");
  }
  else
  {
    Serial.println("ok.");
  }

  Serial.print("test32:\t");
  uint32_t t32 = 0xFADEFACE;
  fram.write32(1000, t32);
  if (fram.read32(1000) != 0xFADEFACE)
  {
    Serial.println("failed.");
  }
  else
  {
    Serial.println("ok.");
  }
  Serial.println();
}


void testReadWriteLarge()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint8_t ar[100];
  for (int i = 0; i < 100; i++) ar[i] = i;

  start = millis();
  fram.write(1000, ar, 100);
  stop = millis();
  Serial.print("WRITE 100 bytes TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");

  for (int i = 0; i < 100; i++) ar[i] = 0;

  start = millis();
  fram.read(1000, ar, 100);
  stop = millis();
  Serial.print("READ 100 bytes TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");

  for (int i = 0; i < 100; i++)
  {
    if (ar[i] != i)
    {
      Serial.print("FAIL: \t");
      Serial.println(i);
    }
  }
  Serial.println();
}


void testWriteText()
{
  char str[10][20] =
  {
    "Hello world 0",
    "Hello world 1",
    "Hello world 2",
    "Hello world 3",
    "Hello world 4",
    "Hello world 5",
    "Hello world 6",
    "Hello world 7",
    "Hello world 8",
    "Hello world 9",
  };
  Serial.println();
  Serial.println(__FUNCTION__);

  start = millis();
  fram.write(2000, (uint8_t *)str, 200);
  stop = millis();
  Serial.print("WRITE 200 bytes TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");
  Serial.println();
}


void testReadText1()
{
  char str[10][20];

  Serial.println();
  Serial.println(__FUNCTION__);

  start = millis();
  fram.read(2000, (uint8_t *)str, 200);
  stop = millis();
  Serial.print("READ 200 bytes TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");
  Serial.println();

  for (int i = 0; i < 10; i++)
  {
    Serial.println(str[i]);
  }
  Serial.println();
}


void testReadText2()
{
  char str[20];

  Serial.println();
  Serial.println(__FUNCTION__);

  for (int i = 0; i < 10; i++)
  {
    fram.read(2000 + 20 * i, (uint8_t *)str, 20);
    Serial.println(str);
  }
  Serial.println();
}


//  -- END OF FILE --
