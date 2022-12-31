//    FILE: atomic_weight_find.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"
#include "AtomicWeight.h"

PTOE ptoe;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  uint8_t n = ptoe.find("Fe");
  Serial.println(ptoe.protons(n));

  n = ptoe.find("Au");
  Serial.println(ptoe.protons(n));

  n = ptoe.find("H");
  Serial.println(ptoe.protons(n));

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

