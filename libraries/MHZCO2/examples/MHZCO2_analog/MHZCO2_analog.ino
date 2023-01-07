//
//    FILE: MHZCO2_analog.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo MHZ library / sensor
//    DATE: 2020-09-01


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
  // Serial.println(__FILE__);
}


void loop()
{
  uint16_t  C = concentration(A0, 2000);
  Serial.println(C);
}


uint16_t concentration(int port, uint16_t maxC)
{
  float volt = analogRead(port) * (5.0 / 1023.0);
  uint16_t C = (volt - 0.4) * maxC / 1.6;
  return C;
}


//  -- END OF FILE --

