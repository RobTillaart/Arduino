//
//    FILE: MHZCO2_analog.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MHZ library / sensor
//    DATE: 2020-09-01


#include "Arduino.h"
#include "MHZCO2.h"


/*
   DATASHEET P.7
   Conversion between analog voltage output and concentration,
   take 0.4V ~ 2V as an example:

   Vo(V) = 0.4V + (2.0V - 0.4V) * C(concentration ppm) / range(ppm)

   C = (Vo - 0.4 V ) * range / 1.6;
*/


void setup()
{
  Serial.begin(115200);
  //  Serial.println(__FILE__);
  //  Serial.print("MHZCO2_LIB_VERSION: ");
  //  Serial.println(MHZCO2_LIB_VERSION);
}


void loop()
{
  uint16_t C = concentration(A0, 2000);
  Serial.println(C);
}


uint16_t concentration(int port, uint16_t maxConcentration)
{
  float volt = analogRead(port) * (5.0 / 1023.0);
  uint16_t C = (volt - 0.4) * maxConcentration / 1.6;
  return C;
}


//  -- END OF FILE --

