//    FILE: atomic_weight_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight

#include "Arduino.h"
#include "AtomicWeight.h"

uint32_t start, stop;

PTOE ptoe;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  for (int i = 0; i <= ptoe.size(); i++)
  {
    printElem(i);
  }
}

void loop()
{
  
}


void printElem(uint8_t i)
{
  Serial.print(ptoe.name(i));
  Serial.print("\t");
  Serial.print(ptoe.electrons(i));
  Serial.print("\t");
  Serial.print(ptoe.protons(i));
  Serial.print("\t");
  Serial.print(ptoe.neutrons(i));
  Serial.print("\t");
  Serial.print(ptoe.weight(i), 3);

  Serial.print("\n");
}


// -- END OF FILE --
