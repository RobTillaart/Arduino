//
//    FILE: TRAFO_determineFormFactor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple RMS plotting
//     URL: https://github.com/RobTillaart/TRAFO


#include "TRAFO.h"


TRAFO myTrafo;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TRAFO_LIB_VERSION: ");
  Serial.println(TRAFO_LIB_VERSION);
  Serial.println();

  myTrafo.begin(readADC, 1023, 5.0, 708);

  Serial.println("FormFactor");
}


void loop()
{
  Serial.println(myTrafo.determineFormFactor(),3);
}


int32_t readADC()
{
  return (int32_t)analogRead(A0);
}


//  -- END OF FILE --
