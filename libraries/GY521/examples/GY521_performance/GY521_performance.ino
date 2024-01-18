//
//    FILE: GY521_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/GY521

#include "GY521.h"


GY521 sensor(0x68);

uint32_t counter = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }
}

void loop()
{
  uint32_t start = micros();
  int16_t x = sensor.read();
  uint32_t duration = micros() - start;
  
  Serial.print(x);
  Serial.print('\t');
  Serial.print(duration);
  Serial.println();
  
  delay(1000);
}


//  -- END OF FILE --

