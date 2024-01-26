//
//    FILE: DHT20_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for DHT20 I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/DHT20
//
//  Always check datasheet - front view
//
//          +--------------+
//  VDD ----| 1            |
//  SDA ----| 2    DHT20   |
//  GND ----| 3            |
//  SCL ----| 4            |
//          +--------------+


#include "DHT20.h"

DHT20 DHT(&Wire);


void setup()
{
  Wire.begin();
  DHT.begin();  //  ESP32 default pins 21 22

  Serial.begin(115200);
  Serial.println("Humidity, Temperature");
}


void loop()
{
  if (millis() - DHT.lastRead() >= 1000)
  {
    //  note no error checking
    DHT.read();
    Serial.print(DHT.getHumidity(), 1);
    Serial.print(", ");
    Serial.println(DHT.getTemperature(), 1);
  }
}


//  -- END OF FILE --
