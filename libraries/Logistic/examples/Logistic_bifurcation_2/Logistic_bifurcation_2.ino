//    FILE: Logistic_bifurcation_2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Logistic
//
//  using multiple colors shows sort of proper bifurcation.


#include "Logistic.h"

Logistic L;
float arr[32];  //  more is possible but hard to see.


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  //  Serial.println(__FILE__);
  //  Serial.print("LOGISTIC_LIB_VERSION: ");
  //  Serial.println(LOGISTIC_LIB_VERSION);
  //  Serial.println();

  float rate = 0.0;
  while (rate < 4.00)
  {
    //  initialize
    rate += 0.01;
    L.setRate(rate);
    L.iterate(0.5);

    //  make many iterations
    //  for (int i = 0; i < 100 + random(2); i++)  //  the random(2) gives something of a range
    for (int i = 0; i < 100; i++)
    {
      L.iterate();
    }
    for (int i = 0; i < 32; i++)
    {
      arr[i] = L.iterate();
      Serial.print(arr[i] * 100, 6);
      Serial.print(",");
    }
    Serial.println();
  }
}


void loop()
{
}


//  -- END OF FILE --
