//
//    FILE: SRF05_demo.ino
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
}


void loop()
{
  Serial.println(SRF.getTime());
  delay(100);
  Serial.println(SRF.getMillimeter());
  delay(100);
  Serial.println(SRF.getCentimeter(), 1);
  delay(100);
  Serial.println(SRF.getMeter(), 2);
  delay(100);
  Serial.println(SRF.getInch(), 1);
  delay(100);
  Serial.println(SRF.getFeet(), 2);
  delay(1000);
  Serial.println();
}


// -- END OF FILE --

