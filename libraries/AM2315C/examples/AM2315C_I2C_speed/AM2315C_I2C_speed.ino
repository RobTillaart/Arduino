//
//    FILE: AM2315C_I2C_speed.ino
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
//
//  NOTE datasheet states 400 KHz as maximum


#include "AM2315C.h"

AM2315C DHT;  //  default Wire

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AM2315C LIBRARY VERSION: ");
  Serial.println(AM2315C_LIB_VERSION);
  Serial.println();

  Wire.begin();
  DHT.begin();    //  ESP32 default pins 21 22

  Serial.println("\nNOTE: datasheet states 400 KHz as maximum.\n");

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
    Serial.print(stop - start);  // time
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
