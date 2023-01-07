//
//    FILE: MHZCO2_serial1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo for MEGA / 2560 with Serial1
//    DATE: 2020-09-01


#include "MHZCO2.h"

MHZ19B MHZ19B;


void setup()
{
  Serial.begin(115200);
  //   Serial.println(__FILE__);

  MHZ19B.begin(&Serial1);
  Serial1.begin(9600);
  
}


void loop()
{
  MHZ19B.measure();

  Serial.print("CO2:  ");
  Serial.println(MHZ19B.getCO2());
  Serial.print("MCO2: ");
  Serial.println(MHZ19B.getMinCO2());
  Serial.print("Temp: ");
  Serial.println(MHZ19B.getTemperature());
  Serial.print("Accu: ");
  Serial.println(MHZ19B.getAccuracy());

  delay(1000);
}


//  -- END OF FILE --
