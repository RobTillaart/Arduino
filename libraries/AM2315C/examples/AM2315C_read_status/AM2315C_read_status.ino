//
//    FILE: AM2315C_read_status.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for AM2315C I2C humidity & temperature sensor
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

uint8_t count = 0;

void setup()
{
  DHT.begin();    //  ESP32 default pins 21 22

  Wire.setClock(400000);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AM2315C LIBRARY VERSION: ");
  Serial.println(AM2315C_LIB_VERSION);
  Serial.println();

  delay(2000);
}


void loop()
{
  int status = DHT.readStatus();
  Serial.println(status);
  delay(1000);
}


//  -- END OF FILE --
