//
//    FILE: AM2315C_async.ino
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

AM2315C DHT;

uint32_t counter = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AM2315C LIBRARY VERSION: ");
  Serial.println(AM2315C_LIB_VERSION);
  Serial.println();

  Wire.begin();
  DHT.begin();

  delay(2000);

  //  start with initial request
  Serial.println(DHT.requestData());
}


void loop()
{
  uint32_t now = millis();

  if (now - DHT.lastRead() > 1000)
  {
    DHT.readData();
    DHT.convert();

    Serial.print(DHT.getHumidity(), 1);
    Serial.print(" %RH \t");
    Serial.print(DHT.getTemperature(), 1);
    Serial.print(" °C\t");
    Serial.print(counter);
    Serial.print("\n");
    //  new request
    counter = 0;
    DHT.requestData();
  }

  //  other code here
  counter++;  //  dummy counter to show async behaviour
}


//  -- END OF FILE --
