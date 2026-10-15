//
//    FILE: MB1242_statusPin.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test checking pin 2 of device with status
//     URL: https://github.com/RobTillaart/MB1242
//
//  Connect status pin 2 of the device to a pin from the uProcessor

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

  //  adjust to your setup
  //  connect uproc pin to device pin 2.
  MB.setStatusPin(4);

  MB.requestDistance();
}


void loop()
{
  //  intervals should be less than 100 ms as statuspin is used
  if (MB.ready())
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.println(MB.readCM());
    MB.requestDistance();
  }
}


//  -- END OF FILE --
