//
//    FILE: PPD71_PulseRatio.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/PPD71


#include "PPD71.h"

PPD71 ppd(&Serial);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PPD71_LIB_VERSION: ");
  Serial.println(PPD71_LIB_VERSION);
  Serial.println();

  //  wait for first data.
  delay(2000);
}


void loop()
{
  if (ppd.getData())
  {
    Serial.print(ppd.getPulseRatio05());
    Serial.print("\t");
    Serial.print(ppd.getPulseRatio07());
    Serial.print("\t");
    Serial.print(ppd.getPulseRatio10());
    Serial.print("\t");
    Serial.print(ppd.getPulseRatio25());
    Serial.print("\n");
  }
  delay(2000);
}


//  -- END OF FILE --
