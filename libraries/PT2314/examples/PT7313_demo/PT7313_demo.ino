//
//    FILE: PT7313_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: move sound around
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

  pt.setAttnLeft(0);
  pt.setAttnRight(31);
  pt.setAttnLeftBack(31);
  pt.setAttnRightBack(31);
  
  pt.setLoudness(true);
}


void loop()
{
  for (int i = 0; i < 32; i++)
  {
    pt.setAttnLeft(31 - i);
    pt.setAttnRight(i);
    delay(100);
  }
  for (int i = 0; i < 32; i++)
  {
    pt.setAttnRight(31 - i);
    pt.setAttnRightBack(i);
    delay(100);
  }
  for (int i = 0; i < 32; i++)
  {
    pt.setAttnRightBack(31 - i);
    pt.setAttnLeftBack(i);
    delay(100);
  }
  for (int i = 0; i < 32; i++)
  {
    pt.setAttnLeftBack(31 - i);
    pt.setAttnLeft(i);
    delay(100);
  }
}


//  -- END OF FILE --
