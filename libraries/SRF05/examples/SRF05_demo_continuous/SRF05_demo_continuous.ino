//
//    FILE: SRF05_demo_continuous.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//     URL: https://github.com/RobTillaart/SRF05
//
//  e.g. use with plotter.

#include "SRF05.h"

const int trigger = 7;
const int echo    = 6;

SRF05 SRF(trigger, echo);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SRF05_LIB_VERSION: ");
  Serial.println(SRF05_LIB_VERSION);
  Serial.println();

  SRF.setCorrectionFactor(1.035);
}


void loop()
{
  float d = SRF.getCentimeter();
  if (d < 500)
  {
    Serial.println(d, 1);
    delay(100);
  }
  delay(10);
}


//  -- END OF FILE --
