//
//    FILE: I2C_eeprom_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show/test I2C_EEPROM library
//     URL: https://github.com/RobTillaart/I2C_EEPROM
//
//  uses a 24LC256 (32KB) EEPROM
//  might need adaptions for other EEPROMS (page size etc)


#include "Wire.h"
#include "I2C_eeprom.h"


//  UNO
#define SERIAL_OUT Serial
//  Due
// #define SERIAL_OUT SerialUSB


I2C_eeprom ee(0x50);
//  I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, diff, totals = 0;


void setup()
{
  SERIAL_OUT.begin(115200);
  while (!SERIAL_OUT);  //  wait for SERIAL_OUT port to connect. Needed for Leonardo only
  SERIAL_OUT.println(__FILE__);
  SERIAL_OUT.print("I2C_EEPROM_VERSION: ");
  SERIAL_OUT.println(I2C_EEPROM_VERSION);

  Wire.begin();

  ee.begin();
  if (! ee.isConnected())
  {
    SERIAL_OUT.println("ERROR: Can't find eeprom\nstopped...");
    while (1);
  }
  SERIAL_OUT.print("isConnected:\t");
  SERIAL_OUT.println(ee.isConnected());

  SERIAL_OUT.println("\nTEST: determine size");
  start = micros();
  uint32_t size = ee.determineSize(true);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  if (size > 0)
  {
    SERIAL_OUT.print("SIZE: ");
    SERIAL_OUT.print(size);
    SERIAL_OUT.println(" Bytes");
  } else if (size == 0)
  {
    SERIAL_OUT.println("WARNING: Can't determine eeprom size");
  }
  else
  {
    SERIAL_OUT.println("ERROR: Can't find eeprom\nstopped...");
    while (1);
  }

  SERIAL_OUT.println("\nTEST: 64 byte page boundary writeBlock");
  ee.setBlock(0, 0, 128);
  dumpEEPROM(0, 128);
  Serial.println("---");
  // char data[] = "11111111111111111111";
  char data[] = "33333333333333333333";
  ee.writeBlock(60, (uint8_t*) data, 10);
  dumpEEPROM(0, 128);


  SERIAL_OUT.println("\nTEST: 64 byte page boundary setBlock");
  ee.setBlock(0, 0, 128);
  dumpEEPROM(0, 128);
  ee.setBlock(60, '1', 10);
  dumpEEPROM(0, 128);


  SERIAL_OUT.println("\nTEST: 64 byte page boundary readBlock");
  ee.setBlock(0, 0, 128);
  ee.setBlock(60, '1', 6);
  dumpEEPROM(0, 128);
  char ar[100];
  memset(ar, 0, 100);
  ee.readBlock(60, (uint8_t*)ar, 10);
  SERIAL_OUT.println(ar);


  SERIAL_OUT.println("\nTEST: write large string readback in small steps");
  ee.setBlock(0, 0, 128);
  char data2[] = "0000000000111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999A";
  ee.writeBlock(10, (uint8_t *) &data2, sizeof(data2));
  dumpEEPROM(0, 128);
  for (int i = 0; i < 100; i++)
  {
    if (i % 10 == 0 ) SERIAL_OUT.println();
    SERIAL_OUT.print(' ');
    SERIAL_OUT.print(ee.readByte(10 + i));
  }
  SERIAL_OUT.println();


  SERIAL_OUT.println("\nTEST: check almost endofPage writeBlock");
  ee.setBlock(0, 0, 128);
  char data3[] = "6666";
  ee.writeBlock(60, (uint8_t *) &data3, sizeof(data3));
  dumpEEPROM(0, 128);

  // SERIAL_OUT.println();
  // SERIAL_OUT.print("\nI2C speed:\t");
  // SERIAL_OUT.println(16000/(16+2*TWBR));
  // SERIAL_OUT.print("TWBR:\t");
  // SERIAL_OUT.println(TWBR);
  // SERIAL_OUT.println();

  totals = 0;
  SERIAL_OUT.print("\nTEST: timing writeByte()\t");
  uint32_t start = micros();
  ee.writeByte(10, 1);
  uint32_t diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  SERIAL_OUT.print("TEST: timing writeBlock(50)\t");
  start = micros();
  ee.writeBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  SERIAL_OUT.print("TEST: timing readByte()\t\t");
  start = micros();
  ee.readByte(10);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  SERIAL_OUT.print("TEST: timing readBlock(50)\t");
  start = micros();
  ee.readBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  SERIAL_OUT.print("TOTALS: ");
  SERIAL_OUT.println(totals);
  totals = 0;

  // same tests but now with a 5 millisec delay in between.
  delay(5);

  SERIAL_OUT.print("\nTEST: timing writeByte()\t");
  start = micros();
  ee.writeByte(10, 1);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  delay(5);

  SERIAL_OUT.print("TEST: timing writeBlock(50)\t");
  start = micros();
  ee.writeBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  delay(5);

  SERIAL_OUT.print("TEST: timing readByte()\t\t");
  start = micros();
  ee.readByte(10);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  delay(5);

  SERIAL_OUT.print("TEST: timing readBlock(50)\t");
  start = micros();
  int xx = ee.readBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  totals += diff;

  SERIAL_OUT.print("TOTALS: ");
  SERIAL_OUT.println(totals);
  totals = 0;

  // does it go well?
  SERIAL_OUT.println(xx);

  SERIAL_OUT.println("\tDone...");
}


void loop()
{
}


void dumpEEPROM(uint16_t memoryAddress, uint16_t length)
{
  const int BLOCK_TO_LENGTH = 10;

  SERIAL_OUT.print("\t  ");
  for (int x = 0; x < 10; x++)
  {
    if (x != 0) SERIAL_OUT.print("    ");
    SERIAL_OUT.print(x);
  }
  SERIAL_OUT.println();

  // block to defined length
  memoryAddress = memoryAddress / BLOCK_TO_LENGTH * BLOCK_TO_LENGTH;
  length = (length + BLOCK_TO_LENGTH - 1) / BLOCK_TO_LENGTH * BLOCK_TO_LENGTH;

  byte b = ee.readByte(memoryAddress);
  for (unsigned int i = 0; i < length; i++)
  {
    char buf[6];
    if (memoryAddress % BLOCK_TO_LENGTH == 0)
    {
      if (i != 0) SERIAL_OUT.println();
      sprintf(buf, "%05d", memoryAddress);
      SERIAL_OUT.print(buf);
      SERIAL_OUT.print(":\t");
    }
    sprintf(buf, "%03d", b);
    SERIAL_OUT.print(buf);
    b = ee.readByte(++memoryAddress);
    SERIAL_OUT.print("  ");
  }
  SERIAL_OUT.println();
}


//  -- END OF FILE --

