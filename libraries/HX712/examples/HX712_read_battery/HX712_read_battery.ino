//
//    FILE: HX712_read_battery.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX712 demo
//     URL: https://github.com/RobTillaart/HX712


#include "HX712.h"

HX712 scale;

//  adjust pins if needed
uint8_t dataPin = 6;
uint8_t clockPin = 7;

float f;


void setup()
{
  Serial.begin(115200);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("HX712_LIB_VERSION: ");
  //  Serial.println(HX712_LIB_VERSION);
  //  Serial.println();

  scale.begin(dataPin, clockPin);

  //  no calibration needed for read_battery().
}


void loop()
{
  //  continuous ~ 4x per second
  f = scale.read_battery();
  Serial.println(f);
  delay(250);
}


//  -- END OF FILE --
