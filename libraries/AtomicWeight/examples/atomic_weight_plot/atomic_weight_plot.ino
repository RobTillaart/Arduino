//    FILE: atomic_weight_plot.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo for plotter
//     URL: https://github.com/RobTillaart/AtomicWeight
//

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

  Serial.println("Protons\tNeutrons\tWeight");
  for (int n = 0; n < 119; n++)
  {
    //  for (int i = 0; i < 4; i++)  //  plot 4x to max graph
    {
      Serial.print(ptoe.protons(n));
      Serial.print("\t");
      Serial.print(ptoe.neutrons(n));
      Serial.print("\t");
      Serial.print(ptoe.weight(n));
      Serial.print("\n");
    }
  }
}


void loop()
{
}


//  -- END OF FILE --
