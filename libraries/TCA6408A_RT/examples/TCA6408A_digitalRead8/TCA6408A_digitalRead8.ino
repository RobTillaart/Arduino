//
//    FILE: TCA6408A_digitalRead8.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6408A_RT


#include "TCA6408A.h"


TCA6408A tca(0x20);

uint8_t value, previous;


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

  //  Set all pins as inputs
  tca.setPinMode8(0xFF);
  tca.setPolarity8(0xFF);

  Serial.print(millis());
  Serial.println(": config done..");

  previous = tca.digitalRead8();
}


void loop(void)
{
  //  polling
  value = tca.digitalRead8();
  if (value != previous)
  {
    previous = value;
    Serial.print(millis());
    Serial.print(": \t");
    Serial.println(value, HEX);
  }
}


//  -- END OF FILE --
