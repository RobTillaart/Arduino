//
//    FILE: asdx_raw_data.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo raw counters
//     URL: https://github.com/RobTillaart/I2C_ASDX


#include "I2C_ASDX.h"


//  adjust to type of sensor  (address, psi)
I2C_ASDX sensor(0x58, 100);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_ASDX_VERSION: ");
  Serial.println(I2C_ASDX_VERSION);
  Serial.println();

  Wire.begin();
  sensor.begin();

  Serial.println("Pres");
}


void loop()
{
  int state = sensor.read();
  if (state == I2C_ASDX_OK)
  {
    Serial.println(sensor.rawPressureCount());
  }
  else
  {
    Serial.print("error: ");
    Serial.println(state);
  }

  delay(1000);
}


//  -- END OF FILE --
