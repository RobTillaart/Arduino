//
//    FILE: asdx_timed_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2C_ASDX


#include "I2C_ASDX.h"


//  adjust to type of sensor  (address, psi)
I2C_ASDX sensor(0x58, 100);

const uint32_t interval = 1000;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("I2C_ASDX_VERSION: ");
  Serial.println(I2C_ASDX_VERSION);

  Wire.begin();
  sensor.begin();

  if (sensor.begin() == false)
  {
    Serial.print("Cannot find sensor:\t");
    Serial.print(sensor.getAddress());
    Serial.println("Check wires or try another address.");
    while(1);
  }
}


void loop()
{
  uint32_t now = millis();

  if (now - sensor.lastRead() >= interval)
  {
    Serial.print(now);
    Serial.print("\t");
    int state = sensor.read();
    switch (state)
    {
      case I2C_ASDX_OK:
        Serial.print("mBar:\t");
        Serial.println(sensor.getPressure());
        break;
      case I2C_ASDX_INIT:
        Serial.println("S:\tINIT");
        break;
      case I2C_ASDX_READ_ERROR:
        Serial.print("E:\tread error\t");
        Serial.println(sensor.errorCount());
        break;
      case I2C_ASDX_C000_ERROR:
        Serial.print("E:\tC000 error\t");
        Serial.println(sensor.errorCount());
        break;
      default:        //  catch all other...
        Serial.print("E:\t");
        Serial.println(state);
        break;
    }
  }
}


//  -- END OF FILE --

