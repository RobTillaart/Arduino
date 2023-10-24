//
//    FILE: DHT12_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for DHT12 I2C humidity & temperature sensor

#include "DHT12.h"

DHT12 DHT(&Wire);


void setup()
{
  Wire.begin();
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


//  -- END OF FILE --
