//
//    FILE: Fletcher16_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Fletcher


#include "Arduino.h"
#include "Fletcher16.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers


Fletcher16 fl;
volatile uint8_t z;
uint32_t start, stop, randomtime;


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();
  delay(100);

  start = micros();
  for (uint16_t x = 0; x < 10000; x++)
  {
    z = random(256);
  }
  stop = micros();
  randomtime = stop - start;
  Serial.print("randomtime: ");
  Serial.println(randomtime);
  delay(100);

  fl.begin();
  start = micros();
  for (uint16_t x = 0; x < 10000; x++)
  {
    z = random(256);
    fl.add(z);
  }
  stop = micros();
  Serial.print("     total: ");
  Serial.println(stop - start);
  Serial.print(" 1e4 x add: ");
  Serial.println(stop - start - randomtime);
  delay(100);
  
  Serial.print("  checksum: ");
  Serial.println(fl.getFletcher());
}


void loop()
{
}


//  -- END OF FILE --
