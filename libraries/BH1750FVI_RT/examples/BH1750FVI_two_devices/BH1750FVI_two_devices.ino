//
//    FILE: BH1750FVI_two_devices.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT


#include "BH1750FVI.h"

BH1750FVI myLux1(0x23);  //  BH1750FVI_DEFAULT_ADDRESS
BH1750FVI myLux2(0x5C);  //  BH1750FVI_ALT_ADDRESS

float correctionFactor = 0.45f;  //  min value see datasheet


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BH1750FVI_LIB_VERSION: ");
  Serial.println(BH1750FVI_LIB_VERSION);
  Serial.println();

  Wire.begin();

  myLux1.powerOn();
  myLux1.setContHighRes();

  myLux2.powerOn();
  myLux2.setContHighRes();
}


void loop()
{
  if (myLux1.isReady())
  {
    float val = myLux1.getLux();
    Serial.print("1:\t");
    Serial.print(val, 1);
    Serial.print("\t");
    Serial.print(myLux1.getMode());
    Serial.print("\t");
    Serial.print(myLux1.getCorrectionFactor(), 2);
    Serial.print("\t");
    Serial.println(val / myLux1.getCorrectionFactor(), 1);

    //  note correction factor are steps of 1/69 internally, see datasheet
    correctionFactor += 0.05f;
    if (correctionFactor > 3.68f)  //  0.45 - 3.68 = 45 steps of 0.05
    {
      correctionFactor = 0.45f;
      Serial.println();
    }
    myLux1.setCorrectionFactor(correctionFactor);  //  0.45 .. 3.68
  }
  if (myLux2.isReady())
  {
    float val = myLux2.getLux();
    Serial.print("2:\t");
    Serial.print(val, 1);
    Serial.print("\t");
    Serial.print(myLux2.getMode());
    Serial.print("\t");
    Serial.print(myLux2.getCorrectionFactor(), 2);
    Serial.print("\t");
    Serial.println(val / myLux2.getCorrectionFactor(), 1);

    //  note correction factor are steps of 1/69 internally, see datasheet
    correctionFactor += 0.05f;
    if (correctionFactor > 3.68f)  //  0.45 - 3.68 = 45 steps of 0.05
    {
      correctionFactor = 0.45f;
      Serial.println();
    }
    myLux2.setCorrectionFactor(correctionFactor);  //  0.45 .. 3.68
  }
  delay(1000);
  //  do other things here
}


//  -- END OF FILE --
