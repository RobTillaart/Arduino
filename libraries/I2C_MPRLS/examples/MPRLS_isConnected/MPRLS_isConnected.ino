//
//    FILE: MPRLS_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MPRLS


#include "I2C_MPRLS.h"


//  adjust address of sensor if needed
I2C_MPRLS sensor(0x58);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_MPRLS_LIB_VERSION: ");
  Serial.println(I2C_MPRLS_LIB_VERSION);
  Serial.println();

  Wire.begin();
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
  if (sensor.isConnected() == false)
  {
    Serial.println("cannot connect to sensor!");
  }
  else
  {
    int state = sensor.read();
    if (state == I2C_MPRLS_OK)
    {
      Serial.print("pressure:\t");
      Serial.println(sensor.getPressure());
    }
    else 
    {
      Serial.print("error: ");
      Serial.println(state);
    }
  }

  delay(1000);
}


//  -- END OF FILE --
