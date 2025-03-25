//
//    FILE: PCA9671_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo device detection
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

  if (!PCA.begin())
  {
    Serial.println("could not initialize...");
  }
  if (!PCA.isConnected())
  {
    Serial.println("=> not connected");
  }
  else
  {
    Serial.println("=> connected!!");
  }
}


void loop()
{
}


//  -- END OF FILE --

