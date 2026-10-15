//
//    FILE: MB1242_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/MB1242


#include "MB1242.h"


MB1242 MB(0x70);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MB1242_LIB_VERSION: ");
  Serial.println(MB1242_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  MB.begin();

  MB.requestDistance();
}


void loop()
{
  if (MB.ready())
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(MB.readInch());
    Serial.print("\t");
    Serial.println(MB.readFeet());
    MB.requestDistance();
  }
}


//  -- END OF FILE --
