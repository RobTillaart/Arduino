//
//    FILE: MAX14661_SHADOW.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PAIR interface
//    DATE: 2021-08-30
//     URL: https://github.com/RobTillaart/MAX14661


#include "Wire.h"
#include "MAX14661.h"

MAX14661 mux(0x4C);  //  0x4C..0x4F


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX14661_LIB_VERSION: ");
  Serial.println(MAX14661_LIB_VERSION);

  Wire.begin();
  if (mux.begin() == false)
  {
    Serial.println("Could not find MAX14661");
    while (1);
  }

  test1();
  test2();
  test3();
  test4();
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  mux.setShadowChannelMaskA(0x55);
  mux.setShadowChannelMaskB(0xAA);
  Serial.println(mux.getShadowChannelMaskA());
  Serial.println(mux.getShadowChannelMaskB());
  mux.activateShadow();
  Serial.println(mux.getShadowChannelMaskA());
  Serial.println(mux.getShadowChannelMaskB());
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  mux.setShadowChannelMaskA(0x0F);
  mux.setShadowChannelMaskB(0xF0);
  Serial.println(mux.getShadowChannelMaskA());
  Serial.println(mux.getShadowChannelMaskB());
  mux.activateShadow();
  Serial.println(mux.getShadowChannelMaskA());
  Serial.println(mux.getShadowChannelMaskB());
}


void test3()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  mux.shadowClear();
  Serial.println(mux.getShadowChannelMaskA());
  Serial.println(mux.getShadowChannelMaskB());
  mux.activateShadow();
  Serial.println(mux.getShadowChannelMaskA());
  Serial.println(mux.getShadowChannelMaskB());
}


void test4()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int ch = 0; ch < 16; ch++)
  {
    mux.openShadowChannelA(ch);
    Serial.println(mux.getShadowChannelMaskA());
    mux.closeShadowChannelA(ch);
  }
  for (int ch = 0; ch < 16; ch++)
  {
    mux.openShadowChannelB(ch);
    Serial.println(mux.getShadowChannelMaskB());
    mux.closeShadowChannelB(ch);
  }
  mux.shadowClear();
  mux.activateShadow();
  Serial.println(mux.getShadowChannelMaskA());
  Serial.println(mux.getShadowChannelMaskB());
}


void loop()
{
}


//  -- END OF FILE --

