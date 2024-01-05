//
//    FILE: PCA9552_test02.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
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

}


void loop()
{
  //  random blink
  leds.write1(0, random(2));

  //  steady blink
  leds.write1(1, !leds.read1(1));

  //  output 2 follows 3
  leds.write1(2, leds.read1(3));
  leds.write1(3, random(2));
  delay(1000);
}


//  -- END OF FILE --
