//
//    FILE: I2C_eeprom_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.09
// PURPOSE: show/test I2C_EEPROM library
//

#include <Wire.h> //I2C library
#include <I2C_eeprom.h>

// UNO
#define SERIAL_OUT Serial
// Due
// #define SERIAL_OUT SerialUSB

I2C_eeprom ee(0x50);

uint32_t start, diff, totals = 0;

void setup() 
{
  ee.begin();

  SERIAL_OUT.begin(57600); 
  while (!SERIAL_OUT); // wait for SERIAL_OUT port to connect. Needed for Leonardo only
  
  SERIAL_OUT.print("Demo I2C eeprom library ");
  SERIAL_OUT.print(I2C_EEPROM_VERSION);
  SERIAL_OUT.println("\n");

  SERIAL_OUT.println("\nTEST: determine size");
  start = micros();
  int size = ee.determineSize();
  diff = micros() - start;
  SERIAL_OUT.print("TIME: ");
  SERIAL_OUT.println(diff);
  if (size > 0)
  {
    SERIAL_OUT.print("SIZE: ");
    SERIAL_OUT.print(size);
    SERIAL_OUT.println(" KB");
  } else if (size == 0)
  {
    SERIAL_OUT.println("WARNING: Can't determine eeprom size");
  }
  else
  {
    SERIAL_OUT.println("ERROR: Can't find eeprom\nstopped...");
    while(1);
  }

  SERIAL_OUT.println("\nTEST: 64 byte page boundary writeBlock");
  ee.setBlock(0, 0, 128);
  dumpEEPROM(0, 128);
  char data[] = "11111111111111111111";
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
  ee.writeBlock(10, (uint8_t *) &data2, 100);
  dumpEEPROM(0, 128);
  for (int i = 0; i < 100; i++)
  {
    if (i % 10 == 0 ) SERIAL_OUT.println();
    SERIAL_OUT.print(' ');
    SERIAL_OUT.print(ee.readByte(10+i));
  }
  SERIAL_OUT.println();


  SERIAL_OUT.println("\nTEST: check almost endofPage writeBlock");
  ee.setBlock(0, 0, 128);
  char data3[] = "6666"; 
  ee.writeBlock(60, (uint8_t *) &data3, 2);
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
  // block to 10
  memoryAddress = memoryAddress / 10 * 10;
  length = (length + 9) / 10 * 10;

  byte b = ee.readByte(memoryAddress); 
  for (int i = 0; i < length; i++) 
  {
    if (memoryAddress % 10 == 0)
    {
      SERIAL_OUT.println();
      SERIAL_OUT.print(memoryAddress);
      SERIAL_OUT.print(":\t");
    }
    SERIAL_OUT.print(b);
    b = ee.readByte(++memoryAddress); 
    SERIAL_OUT.print("  ");
  }
  SERIAL_OUT.println();
}
// END OF FILE
