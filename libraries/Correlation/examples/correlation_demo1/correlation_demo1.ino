//
//    FILE: correlation_demo1.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-17
// PURPOSE: demo of the Correlation Library
//     URL: https://github.com/RobTillaart/Correlation


#include "Correlation.h"

Correlation C;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  C.clear();
  for (int i = 0; i < 20; i++)
  {
    C.add(i * 10, i * 40 + 0.1 * random(10));
  }

  C.calculate();
  Serial.print("A:\t");
  Serial.println(C.getA(), 3);
  Serial.print("B:\t");
  Serial.println(C.getB(), 3);
  Serial.print("Rsq:\t");
  Serial.println(C.getRsquare(), 6);
  Serial.print("Esq:\t");
  Serial.println(C.getEsquare(), 3);
  Serial.println();

  for (int i = 0; i <= 20; i++)
  {
    Serial.print(i * 5);
    Serial.print("\t");
    Serial.println(C.getEstimateY(i * 5), 4);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

