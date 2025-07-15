//
//    FILE: AS5600_demo_offset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AS5600
//
//  Examples may use AS5600 or AS5600L devices.
//  Check if your sensor matches the one used in the example.
//  Optionally adjust the code.


#include "AS5600.h"


//  Uncomment the line according to your sensor type
AS5600L as5600;   //  use default Wire
// AS5600 as5600;   //  use default Wire


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.

  //  test border cases first
  as5600.setOffset(-0.0000001);
  Serial.println(as5600.getOffset(), 2);
  as5600.setOffset(360.0);
  Serial.println(as5600.getOffset(), 2);
  Serial.println();
}


void loop()
{
  float offset = 0;
  while (offset < 360)
  {
    as5600.setOffset(offset);
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(as5600.getOffset(), 2);
    Serial.print("\t");
    Serial.print(as5600.readAngle());
    Serial.print("\t");
    Serial.println(as5600.rawAngle() * AS5600_RAW_TO_DEGREES);
    delay(100);
    offset += 12.34;
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
