//
//    FILE: AM2315C_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for AM2315C I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/AM2315C
//
//  Always check datasheet
//
//                    +-----------------+
//    RED    -------- | VDD             |
//    YELLOW -------- | SDA    AM2315C  |
//    BLACK  -------- | GND             |
//    WHITE  -------- | SCL             |
//                    +-----------------+


#include "AM2315C.h"

AM2315C DHT(&Wire);


void setup()
{
  Serial.begin(115200);
  // Serial.println();
  // Serial.println(__FILE__);
  // Serial.print("AM2315C LIBRARY VERSION: ");
  // Serial.println(AM2315C_LIB_VERSION);
  // Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  DHT.begin();

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
