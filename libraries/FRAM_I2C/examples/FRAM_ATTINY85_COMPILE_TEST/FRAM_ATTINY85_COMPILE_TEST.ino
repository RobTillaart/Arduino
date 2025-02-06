//
//    FILE: FRAM_ATTINY85_COMPILE_TEST.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: compile test for FRAM library with ATTINY85
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
//
// WARNING: not tested with hardware, only compilation.
//          this example is for checking if there are compile errors.
//  TESTED: IDE: 1.8.19 ATTINY85
//


#include "TinyWireM.h"
#include "FRAM.h"


FRAM fram;

uint32_t start;
uint32_t stop;


void setup()
{
  TinyWireM.begin();

  fram.begin(0x50);

  testID();
  testFRAMmemory();
  testReadWriteSmall();
  testReadWriteLarge();
//  testWriteText();
//  testReadText1();
//  testReadText2();
}


void loop()
{
}


void testID()
{
  int x = fram.getManufacturerID();
  int y = fram.getProductID();
  int s = fram.getSize();
}

void testFRAMmemory()
{

  start = millis();
  uint8_t val = 0x55;
  for (uint16_t addr = 0; addr < 32768; addr++)
  {
    fram.write8(addr, val);
    if (fram.read8(addr) != 0x55)
    {
    }
    if (addr % 1000 == 0)
    {
    }
  }
  stop = millis();
}


void testReadWriteSmall()
{
  uint8_t t8 = 0xFE;
  fram.write8(1000, t8);
  if (fram.read8(1000) != 0xFE)
  {
  }
  else
  {
  }


  uint16_t t16 = 0xFADE;
  fram.write16(1000, t16);
  if (fram.read16(1000) != 0xFADE)
  {

  }
  else
  {

  }


  uint32_t t32 = 0xFADEFACE;
  fram.write32(1000, t32);
  if (fram.read32(1000) != 0xFADEFACE)
  {

  }
  else
  {
  }

}


void testReadWriteLarge()
{
  uint8_t ar[20];
  for (int i = 0; i < 20; i++) ar[i] = i;

  start = millis();
  fram.write(1000, ar, 20);
  stop = millis();

  for (int i = 0; i < 20; i++) ar[i] = 0;

  start = millis();
  fram.read(1000, ar, 20);
  stop = millis();

  for (int i = 0; i < 20; i++)
  {
    if (ar[i] != i)
    {
    }
  }

}


void testWriteText()
{
  char str[5][16] =
  {
    "Hello world 0",
    "Hello world 1",
    "Hello world 2",
    "Hello world 3",
    "Hello world 4",
  };

  start = millis();
  fram.write(2000, (uint8_t *)str, 80);
  stop = millis();
}


void testReadText1()
{
  char str[5][16];

  start = millis();
  fram.read(2000, (uint8_t *)str, 80);
  stop = millis();

  for (int i = 0; i < 5; i++)
  {
  }
}


void testReadText2()
{
  char str[16];

  for (int i = 0; i < 5; i++)
  {
    fram.read(2000 + 16 * i, (uint8_t *)str, 16);
  }
}



//  -- END OF FILE --
