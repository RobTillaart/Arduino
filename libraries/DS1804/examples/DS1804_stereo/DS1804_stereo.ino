//    FILE: DS1804_stereo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DS1804


#include "DS1804.h"


//  adjust pins if needed
const uint8_t CS_LEFT  = 4;
const uint8_t CS_RIGHT = 5;
const uint8_t INCPIN   = 6;  //  shared
const uint8_t UDPIN    = 7;  //  shared

DS1804 left(CS_LEFT, INCPIN, UDPIN);
DS1804 right(CS_RIGHT, INCPIN, UDPIN);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS1804_LIB_VERSION: ");
  Serial.println(DS1804_LIB_VERSION);
  Serial.println();

  left.begin();
  right.begin();
  left.select(true);
  right.select(true);
}


void loop()
{
  if (Serial.available())
  {
    int c = Serial.read();
    //  L = on, l = off
    if (c == 'L') left.select(true);
    if (c == 'l') left.select(false);
    //  R = on, r = off
    if (c == 'R') right.select(true);
    if (c == 'r') right.select(false);
    //  MUTE
    if (c == 'M') {
      left.select(false);
      right.select(false);
    }
    //  UP / DOWN
    if (c == 'U') left.moveUp();    //  right will follow as U/D pins are shared!
    if (c == 'D') left.moveDown();  //  right will follow as U/D pins are shared!
  }
}


//  -- END OF FILE --
