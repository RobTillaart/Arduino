//
//    FILE: TCA6424A_digitalRead24.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6424A_RT


#include "TCA6424A.h"


TCA6424A tca(0x20);

uint32_t value, previous;


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

  //  Set all pins as inputs
  tca.setPinMode24(0xFFFFFF);
  tca.setPolarity24(0xFFFFFF);

  Serial.print(millis());
  Serial.println(": config done..");

  previous = tca.digitalRead24();
}


void loop(void)
{
  //  polling
  value = tca.digitalRead24();
  if (value != previous)
  {
    previous = value;
    Serial.print(millis());
    Serial.print(": \t");
    Serial.println(value, HEX);
  }
}


//  -- END OF FILE --
