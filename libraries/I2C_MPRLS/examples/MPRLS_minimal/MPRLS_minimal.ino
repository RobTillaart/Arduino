//
//    FILE: MPRLS_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2C_MPRLS


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
  sensor.begin(16);  //  implicit minPressure of 0
  //  optimistic no error check
}


void loop()
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
  delay(1000);
}


//  -- END OF FILE --
