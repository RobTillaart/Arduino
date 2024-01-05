//
//    FILE: PCA9553_PWM.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-18
// PURPOSE: test PCA9553 library
//     URL: https://github.com/RobTillaart/PCA9553
//
//  Connect LEDs from pin 0 and pin 1 with a resistor to 5V
//  See datasheet


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

  leds.setOutputMode(0, PCA9553_MODE_PWM0);
  leds.setOutputMode(1, PCA9553_MODE_PWM1);

  leds.setPrescaler(0, 43);  //  1 Hz
  leds.setPWM(0, 128);       //  50% duty cycle
  leds.setPrescaler(1, 21);  //  2 Hz
  leds.setPWM(1, 32);        //  12% duty cycle
}


void loop()
{
}


//  -- END OF FILE --
