//
//    FILE: MPRLS_timed_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2C_MPRLS


#include "I2C_MPRLS.h"


//  adjust address of sensor if needed
I2C_MPRLS sensor(0x58);

const uint32_t interval = 1000;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_MPRLS_LIB_VERSION: ");
  Serial.println(I2C_MPRLS_LIB_VERSION);
  Serial.println();

  Wire.begin();
  sensor.begin(6.4);

  if (sensor.begin(0, 16) == false)
  {
    Serial.print("Cannot find sensor:\t");
    Serial.print(sensor.getAddress());
    Serial.print(" - state: ");
    Serial.println(sensor.getState());
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
      case I2C_MPRLS_OK:
        Serial.print("pressure:\t");
        Serial.println(sensor.getPressure());
        break;
      case I2C_MPRLS_INIT:
        Serial.println("S:\tINIT");
        break;
      case I2C_MPRLS_READ_ERROR:
        Serial.print("E:\tread error\t");
        Serial.println(sensor.errorCount());
        break;
      case I2C_MPRLS_WRITE_ERROR:
        Serial.print("E:\twrite error\t");
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
