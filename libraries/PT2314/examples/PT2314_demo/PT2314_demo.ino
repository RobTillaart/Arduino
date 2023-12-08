//
//    FILE: PT2314_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/PT2314


#include "PT2314.h"

//  PT2413 pt;
//  PT7314 pt;
PT7313 pt;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  delay(100);

  Wire.begin();
  pt.begin();

  //  do your settings
  pt.setVolume(20);
  //  shift the balance
  pt.setAttnLeft(15);
  pt.setAttnRight(24);
  
  pt.setLoudness(true);
}


void loop()
{
}


//  -- END OF FILE --
