//
//    FILE: demo0.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-17
// PURPOSE: demo of the Correlation Library
//     URL: https://github.com/RobTillaart/Correlation


/*
  X    Y    x    y    xy    x2    b    a    EY    ei    ei2
  ------------------------------------------------------------
  4    11   21   10               2,1  2,6              1,9
  2    7    2    4    8     4                6,8   0,2  0,04
  3    9    1    2    2     1                8,9   0,1  0,01
  4    10   0    1    0     0               11     1    1
  5    14   1    3    3     1               13,1   0,9  0,81
  6    15   2    4    8     4               15,2   0,2  0,04
*/


#include "Correlation.h"

Correlation C;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  C.clear();
  C.add(4, 11);  
  C.add(2, 7);
  C.add(3, 9);
  C.add(4, 10);
  C.add(5, 14);
  C.add(6, 15);

  C.calculate();
  Serial.print("A:\t");
  Serial.println(C.getA(), 3);
  Serial.print("B:\t");
  Serial.println(C.getB(), 3);
  Serial.print("R:\t");
  Serial.println(C.getR(), 6);
  Serial.print("Rsq:\t");
  Serial.println(C.getRsquare(), 6);
  Serial.print("Esq:\t");
  Serial.println(C.getEsquare(), 3);
  Serial.println();

  for (int i = 2; i <= 6; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.println(C.getEstimateY(i), 4);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

