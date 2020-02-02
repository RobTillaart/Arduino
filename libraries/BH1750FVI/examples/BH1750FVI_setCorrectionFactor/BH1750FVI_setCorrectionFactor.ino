//
//    FILE: setCorrectionFactor.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of BH1750FVI lux scanner library
//    DATE: 2020-02-02
//
// Released to the public domain
//

#include "BH1750FVI.h"

BH1750FVI myLux(0x23);

uint32_t lastUpdate = 0;

float correctionFactor = 0.01;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print(__FILE__);
  Serial.println();

  Wire.begin();

  myLux.powerOn();
  myLux.setContHighRes();
}

void loop()
{
  int interval = 100;
  if (millis() - lastUpdate >= interval)
  {
    lastUpdate += interval;
    float val = myLux.getLux();
    Serial.print(val, 1);
    Serial.print("\t");
    Serial.print(myLux.getCorrectionFactor(), 3);
    Serial.print("\t");
    Serial.println(val / myLux.getCorrectionFactor(), 1);

    // note correctionfactor are steps of 1/69 internally, see datasheet
    myLux.setCorrectionFactor(correctionFactor);  // 0.01 .. 3.68
    correctionFactor += 0.01;
    if (correctionFactor > 3.68) correctionFactor = 0.01;
  }

}

// END OF FILE