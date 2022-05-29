//
//    FILE: AS5600_demo_status.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-05-28


#include "AS5600.h"
#include "Wire.h"

AS5600 as5600;   //  use default Wire


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.
}


void loop()
{
  Serial.print("STATUS:\t ");
  Serial.println(as5600.readStatus(), HEX);
  Serial.print("CONFIG:\t ");
  Serial.println(as5600.getConfigure(), HEX);
  Serial.print("   AGC:\t ");
  Serial.println(as5600.readAGC(), HEX);
  Serial.print("MAGNET:\t ");
  Serial.println(as5600.readMagnitude(), HEX);
  Serial.println();

  delay(1000);
}


// -- END OF FILE --
