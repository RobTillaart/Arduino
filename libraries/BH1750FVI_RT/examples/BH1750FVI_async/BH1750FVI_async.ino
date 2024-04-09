//
//    FILE: BH1750FVI_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT


#include "BH1750FVI.h"

BH1750FVI myLux(0x23);

float correctionFactor = 0.45;     //  min value see datasheet
uint32_t count = 0;


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
  if (myLux.isReady())
  {
    float val = myLux.getLux();

    if (count % 20 == 0)
    {
      Serial.println("\nCNT \tLUX \tMODE \tFACTOR \tRAWLUX");
    }
    
    Serial.print(count);
    Serial.print("\t");
    Serial.print(val, 1);
    Serial.print("\t");
    Serial.print(myLux.getMode());
    Serial.print("\t");
    Serial.print(myLux.getCorrectionFactor(), 2);
    Serial.print("\t");
    Serial.println(val / myLux.getCorrectionFactor(), 1);

    //  note correction factor are steps of 1/69 internally, see datasheet
    correctionFactor += 0.05;
    if (correctionFactor > 3.68)  //  0.45 - 3.68 = 45 steps of 0.05
    {
      correctionFactor = 0.45;
      Serial.println();
    }
    myLux.setCorrectionFactor(correctionFactor);  //  0.45 .. 3.68

    count++;
  }
  delay(1000);
  //  do other things here
}


//  -- END OF FILE --
