//
//    FILE: MHZCO2_analog.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MHZ library / sensor
//     URL: https://github.com/RobTillaart/MHZCO2


#include "Arduino.h"
#include "MHZCO2.h"


/*
   DATASHEET P.7
   Conversion between analog voltage output and concentration,
   take 0.4V ~ 2V as an example:

   Vo(V) = 0.4V + (2.0V - 0.4V) * C(concentration ppm) / maxConcentration(ppm)

   reverting the formula:

   PPM = maxConcentration * (Vo - 0.4 V ) / 1.6;
   PPM = maxConcentration * (Vo - 0.4 V ) * 0.625;  //  slightly faster.

   calibrate by measuring lowest and highest voltages.
*/


void setup()
{
  // while (!Serial);  //  uncomment if needed
  Serial.begin(115200);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("MHZCO2_LIB_VERSION: ");
  //  Serial.println(MHZCO2_LIB_VERSION);
  //  Serial.println();
}


void loop()
{
  uint16_t C = concentration(A0, 2000);
  Serial.println(C);
}


uint16_t concentration(int port, uint16_t maxConcentration)
{
  //  adjust 5.0 volt and 1023 steps if needed.
  float volt = analogRead(port) * (5.0 / 1023.0);
  uint16_t PPM = maxConcentration * (volt - 0.4) / 1.6;
  return PPM;
}


//  -- END OF FILE --

