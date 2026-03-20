//
//    FILE: TRAFO_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
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
}


void loop()
{
  /// Serial.print("Freq: \t");
  Serial.print(myTrafo.getZeroPoint());
  Serial.print("\t");
  Serial.print(myTrafo.getADC());
  Serial.print("\t");
  Serial.print(myTrafo.detectFrequency(5));
  Serial.print("\t");
  Serial.println(myTrafo.getRMS());
}


int32_t readADC()
{
  return (int32_t)analogRead(A0);
}


//  -- END OF FILE --
