//
//    FILE: PCF8591_incremental_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-22
//     URL: https://github.com/RobTillaart/PCF8591


#include "PCF8591.h"

PCF8591 dev(0x48);

uint32_t start, stop, dura1, dura2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8591_LIB_VERSION: ");
  Serial.println(PCF8591_LIB_VERSION);

  Wire.begin();

  dev.begin();


  if (! dev.isConnected())
  {
    Serial.println("\nFailed to connect\n");
    // while(1);
  }
  delay(100);

  Serial.print("POR 1st read:\t");
  Serial.println(dev.read(3));
  Serial.println();

  //////////////////////////////////////////////////////

  Serial.println("Read 4 one by one");
  for (uint8_t i = 0; i < 4; i++)
  {
    Serial.print(dev.read(i));
    Serial.print('\t');
  }
  delay(10);

  start = micros();
  for (uint8_t i = 0; i < 4; i++)
  {
    dev.read(i);
  }
  stop = micros();
  dura2 = stop - start;
  Serial.println(dura2);

  //////////////////////////////////////////////////////

  Serial.println("Read 4 with auto increment");
  start = micros();
  dev.read4();
  stop = micros();
  for (uint8_t i = 0; i < 4; i++)
  {
    Serial.print(dev.lastRead(i));
    Serial.print('\t');
  }
  dura1 = stop - start;
  Serial.println(dura1);
  delay(10);

  Serial.print("\t\t\tRatio:\t");
  Serial.println((1.0 * dura2) / dura1);

  Serial.println("\nDone...\n");
}


void loop()
{
}


// -- END OF FILE --

