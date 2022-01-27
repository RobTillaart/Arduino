//
//    FILE: Adler32_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Adler.h"



Adler32 ad;
volatile uint8_t z;
uint32_t start, stop, randomtime;


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Adler32_performance");
  Serial.print("ADLER_LIB_VERSION: ");
  Serial.println(ADLER_LIB_VERSION);

  start = micros();
  for (uint16_t x = 0; x < 10000; x++)
  {
    z = random(255);
  }
  stop = micros();
  randomtime = stop - start;
  Serial.print("randomtime: ");
  Serial.println(randomtime);
  delay(100);

  ad.begin();
  start = micros();
  for (uint16_t x = 0; x < 10000; x++)
  {
    z = random(255);
    ad.add(z);
  }
  stop = micros();
  Serial.print("     total: ");
  Serial.println(stop - start);
  Serial.print(" 1e4 x add: ");
  Serial.println(stop - start - randomtime);
  delay(100);

  Serial.print("  checksum: ");
  Serial.println(ad.getAdler());
}


void loop()
{
}


// -- END OF FILE --
