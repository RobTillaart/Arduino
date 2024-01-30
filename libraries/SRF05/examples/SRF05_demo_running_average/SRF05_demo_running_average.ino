//
//    FILE: SRF05_demo_running_average.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//     URL: https://github.com/RobTillaart/SRF05


#include "SRF05.h"

const int trigger = 7;
const int echo    = 6;

SRF05 SRF(trigger, echo);


///////////////////////////////////////////////////////
//
//
//
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SRF05_LIB_VERSION: ");
  Serial.println(SRF05_LIB_VERSION);
  Serial.println();

  SRF.setCorrectionFactor(1.035);
  SRF.setModeRunningAverage(0.1);
}


void loop()
{
  Serial.println(SRF.getMillimeter());
  delay(100);
}


//  -- END OF FILE --

