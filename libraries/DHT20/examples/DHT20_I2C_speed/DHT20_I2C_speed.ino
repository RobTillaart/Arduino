//
//    FILE: DHT20_I2C_speed.ino
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

//  NOTE datasheet states 400 KHz as maximum


#include "DHT20.h"

DHT20 DHT;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DHT20 LIBRARY VERSION: ");
  Serial.println(DHT20_LIB_VERSION);
  Serial.println();

  Serial.println("\nNOTE: datasheet states 400 KHz as maximum.\n");

  Wire.begin();
  DHT.begin();  //  ESP32 default pins 21, 22
  delay(2000);

  for (uint32_t speed = 50000; speed < 850000; speed += 50000)
  {
    Wire.setClock(speed);
    Serial.print(speed);
    Serial.print("\t");
    Serial.print(DHT.read());  // status
    Serial.print("\t");
    Serial.print(DHT.getHumidity(), 1);
    Serial.print("\t");
    Serial.print(DHT.getTemperature(), 1);
    Serial.println();
    delay(1000);
  }

  Serial.println();
  for (uint32_t speed = 50000; speed < 850000; speed += 50000)
  {
    Wire.setClock(speed);
    start = micros();
    DHT.read();
    stop = micros();

    Serial.print(speed);
    Serial.print("\t");
    Serial.print(stop - start);  //  time
    Serial.print("\t");
    Serial.print(DHT.getHumidity(), 1);
    Serial.print("\t");
    Serial.print(DHT.getTemperature(), 1);
    Serial.println();
    delay(1000);
  }


  Serial.println();
  for (uint32_t speed = 50000; speed < 850000; speed += 50000)
  {
    DHT.requestData();
    while (DHT.isMeasuring());
    Wire.setClock(speed);
    start = micros();
    DHT.readData();
    stop = micros();
    DHT.convert();
    Serial.print(speed);
    Serial.print("\t");
    Serial.print(stop - start);  // time
    Serial.print("\t");
    Serial.print(DHT.getHumidity(), 1);
    Serial.print("\t");
    Serial.print(DHT.getTemperature(), 1);
    Serial.println();
    delay(1000);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
