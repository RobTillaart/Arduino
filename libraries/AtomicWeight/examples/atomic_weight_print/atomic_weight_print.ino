//    FILE: atomic_weight_print.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//          Note: the table of elements_name takes ~1670 bytes.
//          So it will NOT work on devices with small memory e.g. UNO.
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"
#include "AtomicWeight.h"
#include "elements_name.h"


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
  Serial.print("\t");
  Serial.print(elements_name[i]);

  Serial.print("\n");
}


//  -- END OF FILE --
