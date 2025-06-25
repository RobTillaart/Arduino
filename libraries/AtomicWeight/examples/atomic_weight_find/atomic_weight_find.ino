//    FILE: atomic_weight_find.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"
#include "AtomicWeight.h"

PTOE ptoe;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ATOMIC_WEIGHT_LIB_VERSION: ");
  Serial.println(ATOMIC_WEIGHT_LIB_VERSION);
  Serial.println();

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

