//
//    FILE: PCA9685_OE_control.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9635 library
//     URL: https://github.com/RobTillaart/PCA9685_RT


#include "PCA9685.h"


PCA9685 ledArray(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9685_LIB_VERSION: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  Wire.begin();
  ledArray.begin();

  //  start just one channel
  ledArray.setPWM(1, 100);

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
