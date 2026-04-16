//
//    FILE: TCA6408A_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6408A_RT


#include "TCA6408A.h"


TCA6408A tca(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TCA6408A_LIB_VERSION: ");
  Serial.println(TCA6408A_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  if (tca.begin() == false)
  {
    Serial.println("No TCA found.");
    while (1);
  }

  Serial.println("1. test pinMode8()");
  tca.setPinMode8(0x0F);
  Serial.println(tca.getPinMode8());
  tca.setPinMode8(0xF0);
  Serial.println(tca.getPinMode8());
  tca.setPinMode8(0xAA);
  Serial.println(tca.getPinMode8());
  tca.setPinMode8(0x55);
  Serial.println(tca.getPinMode8());
  Serial.println();

  Serial.println("1. test polarity8()");
  tca.setPolarity8(0x0F);
  Serial.println(tca.getPolarity8());
  tca.setPolarity8(0xF0);
  Serial.println(tca.getPolarity8());
  tca.setPolarity8(0xAA);
  Serial.println(tca.getPolarity8());
  tca.setPolarity8(0x55);
  Serial.println(tca.getPolarity8());
  Serial.println();

  //  set all input
  tca.setPinMode8(0xFF);
}


void loop(void)
{
  Serial.println(tca.digitalRead8(), HEX);
  delay(1000);
}


//  -- END OF FILE --
