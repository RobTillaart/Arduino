//
//    FILE: PCA9553_blink.ino
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

  //  GPIO
  //  not mandatory, just to make it explicit
  leds.pinMode1(0, OUTPUT);
  leds.pinMode1(1, OUTPUT);
}


void loop()
{
  leds.write1(0, LOW);
  delay(500);
  leds.write1(1, LOW);
  delay(500);
  leds.write1(0,HIGH);
  delay(500);
  leds.write1(1,HIGH);
  delay(500);
}


//  -- END OF FILE --
