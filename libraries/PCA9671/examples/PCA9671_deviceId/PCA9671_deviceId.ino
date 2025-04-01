//
//    FILE: PCA9671_deviceId.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo get DeviceID
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

//  adjust addresses if needed
PCA9671 PCA(0x20);


void setup()
{
  //  while(!Serial);  //  uncomment when needed
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (PCA.begin() == false)
  {
    Serial.println("Could not connect..");
    while(1);
  }

  uint32_t deviceID = PCA.deviceID();
  uint8_t manufacturer = (deviceID >> 16) & 0xFF;
  uint8_t feature  = (deviceID >> 9) & 0x7F;
  uint8_t category = (deviceID >> 3) & 0x3F;
  uint8_t revision = (deviceID >> 0) & 0x07;
  
  Serial.print("MANUFACT: \t");
  Serial.println(manufacturer, HEX);
  Serial.print(" FEATURE: \t");
  Serial.println(feature, HEX);
  Serial.print("CATEGORY: \t");
  Serial.println(category, HEX);
  Serial.print("REVISION: \t");
  Serial.println(revision, HEX);
}


void loop()
{
}


//  -- END OF FILE --
