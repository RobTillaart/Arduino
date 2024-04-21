//
//    FILE: I2C_eeprom_test_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test I2C_EEPROM library
//     URL: https://github.com/RobTillaart/I2C_EEPROM


#include "Wire.h"
#include "I2C_eeprom.h"


I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, diff, totals = 0;


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

  Serial.print("I2C_EEPROM_VERSION: ");
  Serial.println(I2C_EEPROM_VERSION);

  for (uint32_t speed = 100000; speed <= 1000000; speed += 100000)
  {
    Wire.setClock(speed);
    Serial.print("SPEED: ");
    Serial.println(speed);
    delay(10);
    test();
    dumpEEPROM(0, 100);
  }
  Serial.println("\ndone...");
}


void loop()
{
}


////////////////////////////////////////////////////////////////////

void test()
{
  char data2[] = "0000000000111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999A";

  totals = 0;
  Serial.print("\nTEST: timing writeByte()\t");
  uint32_t start = micros();
  ee.writeByte(10, 1);
  uint32_t diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  Serial.print("TEST: timing writeBlock(50)\t");
  start = micros();
  ee.writeBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  Serial.print("TEST: timing readByte()\t\t");
  start = micros();
  ee.readByte(10);
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  Serial.print("TEST: timing readBlock(50)\t");
  start = micros();
  ee.readBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  Serial.print("TOTALS: ");
  Serial.println(totals);
  totals = 0;

  //  same tests but now with a 5 milliseconds delay in between.
  delay(5);

  Serial.print("\nTEST: timing writeByte()\t");
  start = micros();
  ee.writeByte(10, 1);
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  delay(5);

  Serial.print("TEST: timing writeBlock(50)\t");
  start = micros();
  ee.writeBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  delay(5);

  Serial.print("TEST: timing readByte()\t\t");
  start = micros();
  ee.readByte(10);
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  delay(5);

  Serial.print("TEST: timing readBlock(50)\t");
  start = micros();
  int xx = ee.readBlock(10, (uint8_t *) &data2, 50);
  diff = micros() - start;
  Serial.print("TIME: ");
  Serial.println(diff);
  totals += diff;

  Serial.print("TOTALS: ");
  Serial.println(totals);
  totals = 0;

  // does it go well?
  Serial.println(xx);
}


void dumpEEPROM(uint16_t memoryAddress, uint16_t length)
{
  const int BLOCK_TO_LENGTH = 10;

  Serial.print("\t  ");
  for (int x = 0; x < 10; x++)
  {
    if (x != 0) Serial.print("    ");
    Serial.print(x);
  }
  Serial.println();

  // block to defined length
  memoryAddress = memoryAddress / BLOCK_TO_LENGTH * BLOCK_TO_LENGTH;
  length = (length + BLOCK_TO_LENGTH - 1) / BLOCK_TO_LENGTH * BLOCK_TO_LENGTH;

  byte b = ee.readByte(memoryAddress);
  for (unsigned int i = 0; i < length; i++)
  {
    char buf[6];
    if (memoryAddress % BLOCK_TO_LENGTH == 0)
    {
      if (i != 0) Serial.println();
      sprintf(buf, "%05d", memoryAddress);
      Serial.print(buf);
      Serial.print(":\t");
    }
    sprintf(buf, "%03d", b);
    Serial.print(buf);
    b = ee.readByte(++memoryAddress);
    Serial.print("  ");
  }
  Serial.println();
}


//  -- END OF FILE --

