//
//    FILE: DHT12 _plotter.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Demo for DHT12 I2C humidity & temperature sensor
//
// HISTORY:
// 0.1.0 - 2020-04-11 initial version
//

#include <DHT12.h>

DHT12 DHT;

void setup()
{
  DHT.begin();
  Serial.begin(115200);
  Serial.println("Humidity, Temperature");
}

void loop()
{
  // note no error checking
  DHT.read();
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(", ");
  Serial.println(DHT.getTemperature(), 1);
  delay(1000);
}

// -- END OF FILE --
