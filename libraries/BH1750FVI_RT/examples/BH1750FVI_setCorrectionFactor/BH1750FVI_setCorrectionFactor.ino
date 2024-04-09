//
//    FILE: setCorrectionFactor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT


#include "BH1750FVI.h"

BH1750FVI myLux(0x23);

uint32_t lastUpdate = 0;

float correctionFactor = 0.45;     //  min value see datasheet


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
  uint16_t interval = 180;              //  max time see datasheet P2
  if (millis() - lastUpdate >= interval)
  {
    lastUpdate += interval;
    float val = myLux.getLux();

    Serial.print(val, 1);
    Serial.print("\t");
    Serial.print(myLux.getCorrectionFactor(), 3);
    Serial.print("\t");
    Serial.println(val / myLux.getCorrectionFactor(), 1);

    //  note correctionfactor are steps of 1/69 internally, see datasheet
    myLux.setCorrectionFactor(correctionFactor);  //  0.45 .. 3.68
    correctionFactor += 0.05;
    if (correctionFactor > 3.68)
    {
      correctionFactor = 0.45;
      Serial.println();
    }
  }
}


//  -- END OF FILE --
