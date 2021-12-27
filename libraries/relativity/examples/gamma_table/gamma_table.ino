//
//    FILE: gamma_table.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test formulas
//    DATE: 2021-05-29
//     URL: https://github.com/RobTillaart/relativity


#include "relativity.h"


uint32_t start, stop;

relativity R;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print("\nSpeed of light (m/s):\t");
  Serial.println(R.getC());

  Serial.println("\n Percentage\t Speed\t\t factor\t\t gamma\n");

  for (double perc = 1; perc < 99.9999; perc += (100 - perc) / 10)
  {
    double v = R.getC() * perc * 0.01;

    Serial.print(" ");
    Serial.print(perc, 5);
    Serial.print("\t ");
    Serial.print(v * 0.001);
    Serial.print("\t ");
    Serial.print(R.factor(v), 6);
    Serial.print("\t ");
    Serial.print(R.gamma(v ), 6);
    Serial.println();
  }
  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --

