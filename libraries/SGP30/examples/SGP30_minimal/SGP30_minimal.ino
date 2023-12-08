//
//    FILE: SGP30_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SGP30
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709

//  minimal sketch, can be used with IDE->tools->plotter

#include "SGP30.h"

#define PLOT_HEADER     "TVOC\tCO2"

SGP30 SGP;


void setup()
{
  Serial.begin(115200);
  while (!Serial) delay(1);
  
  //  Serial.println(__FILE__);
  //  Serial.print("SGP30_LIB_VERSION: ");
  //  Serial.println(SGP30_LIB_VERSION);
  //  Serial.println();

  Wire.begin();
  SGP.begin();
  
  Serial.println(PLOT_HEADER);
}


void loop()
{
  SGP.measure(false);      //  returns false if no measurement is made 

  Serial.print(SGP.getTVOC());
  Serial.print("\t");
  Serial.print(SGP.getCO2());
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
