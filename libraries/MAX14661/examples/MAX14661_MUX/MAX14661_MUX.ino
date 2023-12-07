//
//    FILE: MAX14661_MUX.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PAIR interface
//    DATE: 2021-01-29
//     URL: https://github.com/RobTillaart/MAX14661


#include "Wire.h"
#include "MAX14661.h"

MAX14661 mux(0x62);


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
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.MUXA(ch);
    Serial.println(mux.getMUXA(), HEX);
  }
  mux.MUXA(255);
  Serial.println(mux.getMUXB(), HEX);
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.MUXB(ch);
    Serial.println(mux.getMUXB(), HEX);
  }
  mux.MUXB(255);
  Serial.println(mux.getMUXB(), HEX);
}


void test3()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  for (int ch = 0; ch < 16; ch++)
  {
    mux.MUXB(ch);
    Serial.println(mux.getMUXB(), HEX);
  }
  mux.MUXB(255);
  Serial.println(mux.getMUXB(), HEX);
}


void loop()
{
}


//  -- END OF FILE --

