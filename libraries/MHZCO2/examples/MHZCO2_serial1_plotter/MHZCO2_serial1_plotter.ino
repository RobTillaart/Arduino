//
//    FILE: MHZCO2_serial1_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo for MEGA / 2560 with Serial1


#include "Arduino.h"
#include "MHZCO2.h"


MHZ19B MHZ19B;


void setup()
{
  Serial.begin(115200);
//  Serial.println(__FILE__);
//  Serial.print("MHZCO2_LIB_VERSION: ");
//  Serial.println(MHZCO2_LIB_VERSION);

  MHZ19B.begin(&Serial1);
  Serial1.begin(9600);

  //  HEADER
  Serial.println("CO2, MCO2, Temp, Accu");
}


void loop()
{
  MHZ19B.measure();

  Serial.print(MHZ19B.getCO2());
  Serial.print(",");
  Serial.print(MHZ19B.getMinCO2());
  Serial.print(",");
  Serial.print(MHZ19B.getTemperature());
  Serial.print(",");
  Serial.print(MHZ19B.getAccuracy());
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
