//
//    FILE: PulseDivider_same_input.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Test multi pulse dividers with same input pin.
//    DATE: 2023-09-13
//     URL: https://github.com/RobTillaart/PulseDivider


#include "PulseDivider.h"

//  PINS for Arduino UNO
PulseDivider PD10(6, 9, 10, 1, 5000);
PulseDivider PD100(6, 8, 100, 1, 5000);
PulseDivider PD1000(6, 13, 1000, 1, 50000);  //  build in LED!

void setup()
{
  Serial.begin(115200);

  Serial.print("PULSEDIVIDER_LIB_VERSION: ");
  Serial.println(PULSEDIVIDER_LIB_VERSION);

  PD10.start();
  PD100.start();
  PD1000.start();
}

//  check every input equally often
void loop()
{
  //  more software dividers imply a lower maximum frequency.
  //  or more time to do a million checks.

  PD10.check();  //  as often as possible
  PD100.check();  //  as often as possible
  PD1000.check();  //  as often as possible
}


//  -- END OF FILE --
