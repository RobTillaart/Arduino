//
//    FILE: DHT12_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for DHT12 I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/DHT12


#include "DHT12.h"

DHT12 DHT(&Wire);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  // Serial.println(__FILE__);
  // Serial.print("DHT12 LIBRARY VERSION: ");
  // Serial.println(DHT12_LIB_VERSION);
  // Serial.println();

  Wire.begin();
  DHT.begin();

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
