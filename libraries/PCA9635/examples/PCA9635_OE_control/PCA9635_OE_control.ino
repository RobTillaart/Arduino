//
//    FILE: PCA9635_OE_control.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9635 library
//     URL: https://github.com/RobTillaart/PCA9635


#include "PCA9635.h"


PCA9635 ledArray(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9635_LIB_VERSION: ");
  Serial.println(PCA9635_LIB_VERSION);
  Serial.println();

  Wire.begin();

  ledArray.begin();

  //  just one channel
  ledArray.write1(1, 100);

  ledArray.setOutputEnablePin(12);
  ledArray.setOutputEnable(true);
  delay(1000);
  ledArray.setOutputEnable(false);
  delay(1000);
  ledArray.setOutputEnable(true);

  //  TODO  elaborate

  Serial.println("done...");
}

void loop()
{
}


//  -- END OF FILE --

