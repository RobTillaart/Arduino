//
//    FILE: print_sci_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program SCI
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();


  float x = 1E15;

  for (int i = 0; i < 500; i++)
  {
    x += 1E14;
    Serial.println(sci(x, 4));
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
