//
//    FILE: TCA6416A_digitalRead16.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6416A_RT


#include "TCA6416A.h"


TCA6416A tca(0x20);

uint16_t value, previous;


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

  //  Set all pins as inputs
  tca.setPinMode16(0xFFFF);
  tca.setPolarity16(0xFFFF);

  Serial.print(millis());
  Serial.println(": config done..");

  previous = tca.digitalRead16();
}


void loop(void)
{
  //  polling
  value = tca.digitalRead16();
  if (value != previous)
  {
    previous = value;
    Serial.print(millis());
    Serial.print(": \t");
    Serial.println(value, HEX);
  }
}


//  -- END OF FILE --
