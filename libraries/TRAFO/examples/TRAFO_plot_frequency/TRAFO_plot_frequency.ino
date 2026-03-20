//
//    FILE: TRAFO_plot_frequency.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple frequency plotter
//     URL: https://github.com/RobTillaart/TRAFO


#include "TRAFO.h"


TRAFO myTrafo;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("TRAFO_LIB_VERSION: ");
  //  Serial.println(TRAFO_LIB_VERSION);
  //  Serial.println();

  myTrafo.begin(readADC, 1023, 5.0, 708);

  Serial.println("Frequency");
}


void loop()
{
  Serial.println(myTrafo.detectFrequency(1));
}


int32_t readADC()
{
  return (int32_t)analogRead(A0);
}


//  -- END OF FILE --
