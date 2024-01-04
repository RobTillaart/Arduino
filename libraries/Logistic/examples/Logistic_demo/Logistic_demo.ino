//    FILE: Logistic_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Logistic
//
//  best viewed with plotter


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

  //  set initial rate
  L.setRate(1.0);
  //  set initial value
  Serial.println(0.1 * 100, 6);  //  * 100 improves plotter range
  x = L.iterate(0.1);
  Serial.println(x * 100, 6);
}


void loop()
{
  x = L.iterate();
  Serial.println(x * 100, 6);
  delay(10);
}


//  -- END OF FILE --
