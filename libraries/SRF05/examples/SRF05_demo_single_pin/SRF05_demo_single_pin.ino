//
//    FILE: SRF05_demo_single_pin.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//     URL: https://github.com/RobTillaart/SRF05


#include "SRF05.h"

const int trigger = 7;
const int echo    = trigger;

//  SRF05 SRF(trigger, echo);     //  alternative
//  SRF05 SRF(trigger, trigger);  //  alternative
SRF05 SRF(trigger);


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


//  -- END OF FILE --
