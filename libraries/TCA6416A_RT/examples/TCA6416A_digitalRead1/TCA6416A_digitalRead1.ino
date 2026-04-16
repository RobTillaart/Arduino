//
//    FILE: TCA6416A_digitalRead1.ino
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

  //  Set all pins as inputs
  //  Set all pins to inverted
  //  setPinMode8() is faster, this shows how it can be done per pin.
  for (int pin = 0; pin < 16; pin++)
  {
    tca.setPinMode1(pin, 1);
    tca.setPolarity1(pin, 1);
  }

  Serial.print(millis());
  Serial.println(": config done..");
}


void loop(void)
{
  Serial.print(millis());
  Serial.print(": \t");
  for (int pin = 16; pin > -1; pin--)
  {
    Serial.print(tca.digitalRead1(pin) ? 1 : 0);
    delay(100);
  }
  Serial.println();
}


//  -- END OF FILE --
