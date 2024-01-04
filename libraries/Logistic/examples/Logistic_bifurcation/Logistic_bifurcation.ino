//    FILE: Logistic_bifurcation.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Logistic
//
//  although build in plotter is not an XY plotter
//  it gives some idea.


#include "Logistic.h"

Logistic L;
float x = 0;


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
    x = L.iterate(0.5);

    //  make many iterations
    //  for (int i = 0; i < 100 + random(2); i++)  //  the random(2) gives something of a range
    for (int i = 0; i < 100; i++)
    {
      x = L.iterate();
    }

    //  display some values.
    Serial.println(x * 100, 6);  //  * 100 improves plotter range
    //    x = L.iterate();
    //    Serial.println(x * 100, 6);  //  * 100 improves plotter range
    //    x = L.iterate();
    //    Serial.println(x * 100, 6);  //  * 100 improves plotter range
    //    x = L.iterate();
    //    Serial.println(x * 100, 6);  //  * 100 improves plotter range
  }
}


void loop()
{
}


//  -- END OF FILE --
