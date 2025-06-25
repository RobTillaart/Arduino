//    FILE: atomic_weight_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight
//
//  to see balance neutrons / protons (stable isotope)
//  use in plotter, see comments below


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

  Serial.println("Elem\te\tp\tn\tweight");
  for (int i = 0; i <= ptoe.size(); i++)
  {
    printElem(i);
    //  When plotting output, print elements 4x to have nicer graph.
    //  printElem(i);
    //  printElem(i);
    //  printElem(i);
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


//  -- END OF FILE --
