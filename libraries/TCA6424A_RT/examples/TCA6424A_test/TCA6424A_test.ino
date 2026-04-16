//
//    FILE: TCA6424A_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6424A_RT


#include "TCA6424A.h"


TCA6424A tca(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TCA6424A_LIB_VERSION: ");
  Serial.println(TCA6424A_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  if (tca.begin() == false)
  {
    Serial.println("No TCA found.");
    while (1);
  }

  Serial.println("1. test pinMode24()");
  tca.setPinMode24(0x0F0F0F);
  Serial.println(tca.getPinMode24());
  tca.setPinMode24(0xF0F0F0);
  Serial.println(tca.getPinMode24());
  tca.setPinMode24(0xAAAAAA);
  Serial.println(tca.getPinMode24());
  tca.setPinMode24(0x555555);
  Serial.println(tca.getPinMode24());
  Serial.println();

  Serial.println("1. test polarity24()");
  tca.setPolarity24(0x0F0F0F);
  Serial.println(tca.getPolarity24());
  tca.setPolarity24(0xF0F0F0);
  Serial.println(tca.getPolarity24());
  tca.setPolarity24(0xAAAAAA);
  Serial.println(tca.getPolarity24());
  tca.setPolarity24(0x555555);
  Serial.println(tca.getPolarity24());
  Serial.println();

  //  set all input
  tca.setPinMode24(0xFFFFFF);
}


void loop(void)
{
  Serial.println(tca.digitalRead24(), HEX);
  delay(1000);
}


//  -- END OF FILE --
