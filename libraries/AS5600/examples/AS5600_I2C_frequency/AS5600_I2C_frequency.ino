//
//    FILE: AS5600_I2C_frequency.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-05-28


#include "AS5600.h"
#include "Wire.h"

AS5600 as5600;   //  use default Wire

uint32_t clk = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.
  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
}


void loop()
{
  clk += 100000;
  if (clk >= 800000) clk = 100000;
  Wire.setClock(clk);

  Serial.print(clk);
  Serial.print("\t");
  Serial.print(as5600.readAngle());
  Serial.print("\t");
  Serial.println(as5600.rawAngle() * AS5600_RAW_TO_DEGREES);

  delay(1000);
}


// -- END OF FILE --
