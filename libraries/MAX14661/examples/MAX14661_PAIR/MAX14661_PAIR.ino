//
//    FILE: MAX14661_PAIR.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PAIR interface
//    DATE: 2021-01-29
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
    while(1);
  }
  
  test1();
  test2();
  test3();
  test4();
  test5();
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.openChannel(ch);
    Serial.println(mux.getChannels(), HEX);
  }
  mux.closeAllChannels();
  Serial.println(mux.getChannels(), HEX);
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.openChannel(ch);
    Serial.println(mux.getChannels(), HEX);
    mux.closeChannel(ch);
  }
  mux.closeAllChannels();
  Serial.println(mux.getChannels(), HEX);
}


void test3()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println(mux.getChannels(), HEX);
  mux.openAllChannels();
  mux.closeAllChannels();
  Serial.println(mux.getChannels(), HEX);
}


void test4()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println(mux.getChannels(), HEX);
  mux.openAllChannels();
  Serial.println(mux.getChannels(), HEX);
  mux.closeAllChannels();
  Serial.println(mux.getChannels(), HEX);
}


void test5()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int i = 0; i < 10; i++)
  {
    uint16_t mask = random(65535);
    mux.setChannels(mask);
    Serial.println(mux.getChannels(), HEX);
  }
  mux.closeAllChannels();
  Serial.println(mux.getChannels(), HEX);
}


void loop()
{
}


//  -- END OF FILE --

