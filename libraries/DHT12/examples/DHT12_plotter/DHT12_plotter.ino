//
//    FILE: DHT12 _plotter.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: Demo for DHT12 I2C humidity & temperature sensor
//
//  HISTORY:
//  0.1.0  2020-04-11  initial version
//  0.3.0  2020-12-19  compatible new version
//  0.3.1  2021-10-25  add lastRead


#include "DHT12.h"

DHT12 DHT(&Wire);


void setup()
{
  DHT.begin();
  Serial.begin(115200);
  Serial.println("Humidity, Temperature");
}


void loop()
{
  if (millis() - DHT.lastRead() >= 1000)
  {
    // note no error checking
    DHT.read();
    Serial.print(DHT.getHumidity(), 1);
    Serial.print(", ");
    Serial.println(DHT.getTemperature(), 1);
  }
}

// -- END OF FILE --
