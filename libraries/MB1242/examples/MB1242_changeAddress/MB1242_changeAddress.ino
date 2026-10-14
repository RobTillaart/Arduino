//
//    FILE: MB1242_changeAddress.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test address change
//     URL: https://github.com/RobTillaart/MB1242
//
//  adjust sketch to reset address back to 0x70.


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

  //  change the address
  MB.changeAddress(0x80);

  //  get distance with new address
  MB.requestDistance();
}


void loop()
{
  if (MB.ready())
  {
    Serial.println(MB.readCM());
    MB.requestDistance();
  }
}


//  -- END OF FILE --
