//
//    FILE: asdx_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2C_ASDX


#include "I2C_ASDX.h"


//  adjust to type of sensor  (address, psi)
I2C_ASDX sensor(0x58, 100);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("I2C_ASDX_VERSION: ");
  Serial.println(I2C_ASDX_VERSION);

  Wire.begin();
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
  if (sensor.isConnected() == false)
  {
    Serial.println("cannot connect to sensor!");
  }
  else
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
  }

  delay(1000);
}


//  -- END OF FILE --
