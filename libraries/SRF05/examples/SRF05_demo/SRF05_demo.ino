//
//    FILE: SRF05_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//     URL: https://github.com/RobTillaart/SRF05


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
  Serial.print("\t");
  Serial.print(SRF.getTime());
  delay(100);
  Serial.print("\t");
  Serial.print(SRF.getMillimeter());
  delay(100);
  Serial.print("\t");
  Serial.print(SRF.getCentimeter(), 2);
  delay(100);
  Serial.print("\t");
  Serial.print(SRF.getMeter(), 2);
  delay(100);
  Serial.print("\t");
  Serial.print(SRF.getInch(), 1);
  delay(100);
  Serial.print("\t");
  Serial.print(SRF.getFeet(), 2);
  delay(100);
  Serial.println();
}


//  -- END OF FILE --

