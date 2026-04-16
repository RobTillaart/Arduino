//
//    FILE: TCA6416A_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6416A_RT


#include "TCA6416A.h"


TCA6416A tca(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TCA6416A_LIB_VERSION: ");
  Serial.println(TCA6416A_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  if (tca.begin() == false)
  {
    Serial.println("No TCA found.");
    while (1);
  }

  Serial.println("1. test pinMode16()");
  tca.setPinMode16(0x0F0F);
  Serial.println(tca.getPinMode16());
  tca.setPinMode16(0xF0F0);
  Serial.println(tca.getPinMode16());
  tca.setPinMode16(0xAAAA);
  Serial.println(tca.getPinMode16());
  tca.setPinMode16(0x5555);
  Serial.println(tca.getPinMode16());
  Serial.println();

  Serial.println("1. test polarity16()");
  tca.setPolarity16(0x0F0F);
  Serial.println(tca.getPolarity16());
  tca.setPolarity16(0xF0F0);
  Serial.println(tca.getPolarity16());
  tca.setPolarity16(0xAAAA);
  Serial.println(tca.getPolarity16());
  tca.setPolarity16(0x5555);
  Serial.println(tca.getPolarity16());
  Serial.println();

  //  set all input
  tca.setPinMode16(0xFFFF);
}


void loop(void)
{
  Serial.println(tca.digitalRead16(), HEX);
  delay(1000);
}


//  -- END OF FILE --
