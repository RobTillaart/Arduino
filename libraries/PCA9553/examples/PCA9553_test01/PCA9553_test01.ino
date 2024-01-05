//
//    FILE: PCA9553_test01.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-16
// PURPOSE: test PCA9553 library
//     URL: https://github.com/RobTillaart/PCA9553


#include "PCA9553.h"


PCA9553 leds(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9553_LIB_VERSION: ");
  Serial.println(PCA9553_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (leds.begin() == false)
  {
    Serial.println("Could not connect.");
    while(1);
  }

  //  default
  leds.setPrescaler(0, 255);
  leds.setPWM(0, 128);

  //  different
  leds.setPrescaler(1, 113);
  leds.setPWM(1, 32);

  //  all output pins in a different mode
  leds.setOutputMode(0, PCA9553_MODE_LOW);
  leds.setOutputMode(1, PCA9553_MODE_HIGH);
  leds.setOutputMode(2, PCA9553_MODE_PWM0);
  leds.setOutputMode(3, PCA9553_MODE_PWM1);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
