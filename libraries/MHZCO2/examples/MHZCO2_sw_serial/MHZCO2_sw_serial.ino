//
//    FILE: MHZCO2_sw_serial.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-09-01


#include "SoftwareSerial.h"
#include "MHZCO2.h"


const int TX = 4;
const int RX = 5;
SoftwareSerial ss(TX, RX);


MHZ19B MHZ19B;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  MHZ19B.begin(&ss);
  ss.begin(9600);
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
