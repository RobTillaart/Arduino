//
//    FILE: SGP30_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SGP30
//    DATE: 2021-06-24
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709

//  minimal sketch, can be used with IDE->tools->plotter

#include "SGP30.h"


SGP30 SGP;


void setup()
{
  Serial.begin(115200);
  while (!Serial) delay(1);

  Serial.print(__FILE__);
  SGP.begin();
}


void loop()
{
  SGP.measure(false);      // returns false if no measurement is made 

  Serial.print(SGP.getTVOC());
  Serial.print("\t");
  Serial.print(SGP.getCO2());
  Serial.println();
  delay(1000);
}


// -- END OF FILE --
