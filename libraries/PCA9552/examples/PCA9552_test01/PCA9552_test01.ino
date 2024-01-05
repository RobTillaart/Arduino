//
//    FILE: PCA9552_test01.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-16
// PURPOSE: test PCA9552 library
//     URL: https://github.com/RobTillaart/PCA9552


#include "PCA9552.h"


PCA9552 leds(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9552_LIB_VERSION: ");
  Serial.println(PCA9552_LIB_VERSION);
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
  leds.setOutputMode(0, PCA9552_MODE_LOW);
  leds.setOutputMode(1, PCA9552_MODE_HIGH);
  leds.setOutputMode(2, PCA9552_MODE_PWM0);
  leds.setOutputMode(3, PCA9552_MODE_PWM1);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
