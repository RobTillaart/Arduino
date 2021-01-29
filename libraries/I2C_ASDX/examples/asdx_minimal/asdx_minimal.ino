//
//    FILE: asdx_minimal.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo
//    DATE: 2020-06-18
//     URL: https://github.com/RobTillaart/I2C_ASDX

#include "I2C_ASDX.h"

// adjust to type of sensor
I2C_ASDX sensor(0x58, 100);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  sensor.begin();
}

void loop()
{
  int state = sensor.read();
  if (state == I2C_ASDX_OK)
  {
    Serial.print("mBar:\t");
    Serial.println(sensor.getMilliBar());
    Serial.print(" Bar:\t");
    Serial.println(sensor.getBar());
    Serial.print(" PSI:\t");
    Serial.println(sensor.getPSI());
    Serial.println();
  }
  else Serial.println("error");

  delay(1000);
}

// =- END OF FILE --
