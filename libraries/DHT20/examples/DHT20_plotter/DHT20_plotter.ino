//
//    FILE: DHT20 _plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for DHT20 I2C humidity & temperature sensor
//


#include "DHT20.h"

DHT20 DHT(&Wire);


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
