//
//    FILE: MHZCO2_serial1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo for MEGA / 2560 etc with Serial1
//     URL: https://github.com/RobTillaart/MHZCO2


#include "Arduino.h"
#include "MHZCO2.h"


MHZ19B MHZ19B;


void setup()
{
  // while (!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MHZCO2_LIB_VERSION: ");
  Serial.println(MHZCO2_LIB_VERSION);
  Serial.println();

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
