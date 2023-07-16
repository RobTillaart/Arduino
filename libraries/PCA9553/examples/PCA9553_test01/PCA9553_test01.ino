//
//    FILE: PCA9553_test01.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-16
// PURPOSE: test PCA9553 library
//     URL: https://github.com/RobTillaart/PCA9553


#include "Arduino.h"
#include "Wire.h"
#include "PCA9553.h"


PCA9553 leds(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.print("PCA9553_LIB_VERSION: ");
  Serial.println(PCA9553_LIB_VERSION);
  Serial.println();

  if (leds.begin() == false)
  {
    Serial.println("COuld not connect.");
    while(1);
  }

  //  default
  leds.setPrescaler0(255);
  leds.setPWM0(128);

  //  different
  leds.setPrescaler1(113);
  leds.setPWM1(32);

  //  all channels a different source
  leds.setLEDSource(0, 0);
  leds.setLEDSource(1, 1);
  leds.setLEDSource(2, 2);
  leds.setLEDSource(3, 3);

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
