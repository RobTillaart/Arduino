//    FILE: atomic_weight_find.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"
#include "AtomicWeight.h"


PTOE ptoe;
uint32_t start, stop;


volatile char *p = 0;
volatile int n;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ATOMIC_WEIGHT_LIB_VERSION: ");
  Serial.println(ATOMIC_WEIGHT_LIB_VERSION);
  Serial.println();

  delay(10);
  start = micros();
  for (int i = 0; i < 119; i++)
  {
    p = ptoe.name(i);
  }
  stop = micros();
  Serial.print("NAME:\t");
  Serial.println((stop - start) * 1.0 / 119);

  delay(10);
  start = micros();
  for (int i = 0; i < 119; i++)
  {
    n =  ptoe.find(ptoe.name(i));
  }
  stop = micros();
  Serial.print("FIND:\t");
  Serial.println((stop - start) * 1.0 / 119);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
