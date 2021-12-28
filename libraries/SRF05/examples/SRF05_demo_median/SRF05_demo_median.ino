//
//    FILE: SRF05_demo_median.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//    DATE: 2021-05-17
//     URL: https://github.com/RobTillaart/SRF05


#include "SRF05.h"

const int trigger = 7;
const int echo    = 6;

SRF05 SRF(trigger, echo);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SRF.setCorrectionFactor(1.035);
  SRF.setModeMedian(7);
}


void loop()
{
  Serial.println(SRF.getMillimeter());
  delay(10);
}


// -- END OF FILE --

