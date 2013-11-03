//
//    FILE: I2C_eeprom_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: show/test I2C_EEPROM library
//

#include <Wire.h> //I2C library
#include <I2C_eeprom.h>

I2C_eeprom ee(0x50);

void setup() 
{
  Serial.begin(115200);
  Serial.print("Demo I2C eeprom library ");
  Serial.print(I2C_EEPROM_VERSION);
  Serial.println("\n");

  Serial.println("\nTEST: 64 byte page boundary writeBlock");
  ee.setBlock(0,0,128);
  dumpEEPROM(0, 128);
  char data[] = "11111111111111111111";
  ee.writeBlock(60, (uint8_t*) data, 10);
  dumpEEPROM(0, 128);


  Serial.println("\nTEST: 64 byte page boundary setBlock");
  ee.setBlock(0,0,128);
  dumpEEPROM(0, 128);
  ee.setBlock(60, '1', 10);
  dumpEEPROM(0, 128);


  Serial.println("\nTEST: 64 byte page boundary readBlock");
  ee.setBlock(0,0,128);
  ee.setBlock(60, '1', 6);
  dumpEEPROM(0, 128);
  char ar[100];
  memset(ar,0,100);
  ee.readBlock(60, (uint8_t*)ar, 10);
  Serial.println(ar);


  Serial.println("\nTEST: write large string readback in small steps");
  ee.setBlock(0,0,128);
  char data2[] = "0000000000111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999A"; 
  ee.writeBlock(10, (uint8_t *) &data2, 100);
  dumpEEPROM(0, 128);
  for (int i = 0; i<100; i++)
  {
    if (i%10 == 0 ) Serial.println();
    Serial.print(' ');
    Serial.print(ee.readByte(10+i));
  }
  Serial.println();


  Serial.println("\nTEST: check almost endofPage writeBlock");
  ee.setBlock(0,0,128);
  char data3[] = "6666"; 
  ee.writeBlock(60, (uint8_t *) &data3, 2);
  dumpEEPROM(0, 128);

  Serial.println();
  Serial.print("\n\tI2C speed:\t");
  Serial.println(16000/(16+2*TWBR));
  Serial.print("TWBR:\t");
  Serial.println(TWBR);
  Serial.println();

  Serial.print("\nTEST: timing writeByte()\t");
  uint32_t start = micros();
  ee.writeByte(10, 1);
  uint32_t diff = micros() - start;  
  Serial.println(diff);

  Serial.print("TEST: timing writeBlock(50)\t");
  start = micros();
  ee.writeBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;  
  Serial.println(diff);

  Serial.print("TEST: timing readByte()\t\t");
  start = micros();
  ee.readByte(10);
  diff = micros() - start;  
  Serial.println(diff);

  Serial.print("TEST: timing readBlock(50)\t");
  start = micros();
  ee.readBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;  
  Serial.println(diff);

  // same tests but now with a 5 millisec delay in between.
  delay(5);

  Serial.print("\nTEST: timing writeByte()\t");
  start = micros();
  ee.writeByte(10, 1);
  diff = micros() - start;  
  Serial.println(diff);

  delay(5);

  Serial.print("TEST: timing writeBlock(50)\t");
  start = micros();
  ee.writeBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;  
  Serial.println(diff);

  delay(5);

  Serial.print("TEST: timing readByte()\t\t");
  start = micros();
  ee.readByte(10);
  diff = micros() - start;  
  Serial.println(diff);

  delay(5);

  Serial.print("TEST: timing readBlock(50)\t");
  start = micros();
  int xx = ee.readBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;  
  Serial.println(diff);

  // does it go well?
  Serial.println(xx);
  Serial.println("\tDone...");

}


void loop() 
{
}


void dumpEEPROM(uint16_t addr, uint16_t length)
{
  // block to 10
  addr = addr / 10 * 10;
  length = (length + 9)/10 * 10;

  byte b = ee.readByte(addr); 
  for (int i = 0; i < length; i++) 
  {
    if (addr % 10 == 0)
    {
      Serial.println();
      Serial.print(addr);
      Serial.print(":\t");
    }
    Serial.print(b);
    b = ee.readByte(++addr); 
    Serial.print("  ");
  }
  Serial.println();
}
// END OF FILE



