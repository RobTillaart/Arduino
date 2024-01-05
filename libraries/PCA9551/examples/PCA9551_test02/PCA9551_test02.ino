//
//    FILE: PCA9551_test02.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// PURPOSE: test PCA9551 library
//     URL: https://github.com/RobTillaart/PCA9551


#include "PCA9551.h"


PCA9551 leds(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9551_LIB_VERSION: ");
  Serial.println(PCA9551_LIB_VERSION);
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
