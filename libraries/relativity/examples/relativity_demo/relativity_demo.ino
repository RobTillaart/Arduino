//
//    FILE: relativity_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test formulas
//    DATE: 2021-05-29
//     URL: https://github.com/RobTillaart/relativity


#include "relativity.h"

relativity R;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print("\nSpeed of light (m/s):\t");
  Serial.println(R.getC());

  Serial.println("\n Percentage\t Speed\t\t Time\t\t Length\t\t Mass\n");

  for (double perc = 1; perc < 99.9999; perc += (100 - perc) / 10)
  {
    double v = R.getC() * perc * 0.01;

    Serial.print(" ");
    Serial.print(perc, 5);
    Serial.print("\t ");
    Serial.print(v * 0.001);
    Serial.print("\t ");
    Serial.print(R.relativeTime(1, v), 5);
    Serial.print("\t ");
    Serial.print(R.relativeLength(1, v ), 5);
    Serial.print("\t ");
    Serial.print(R.relativeMass(1, v), 3);
    Serial.print("\t ");
    Serial.print(R.EnergyMass(1, v), 2);
    Serial.println();
  }
  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --

