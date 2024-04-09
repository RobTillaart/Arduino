//
//    FILE: BH1750FVI_single_shot_3_res.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT


#include "BH1750FVI.h"

BH1750FVI myLux(0x23);

uint32_t lastUpdate = 0;
float val;
uint32_t count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print(__FILE__);
  Serial.println();

  Wire.begin();

  myLux.powerOn();
  myLux.setContLowRes();
}


void loop()
{
  if (count % 20 == 0)
  {
    Serial.println("\nLOW \tHIGH \tHIGH2 \tRAW");
  }
  count++;
  myLux.setOnceLowRes();
  delay(200);
  val = myLux.getLux();
  Serial.print(val, 1);
  Serial.print('\t');

  myLux.setOnceHighRes();
  delay(200);
  val = myLux.getLux();
  Serial.print(val, 1);
  Serial.print('\t');

  myLux.setOnceHigh2Res();
  delay(200);
  val = myLux.getLux();
  Serial.print(val, 1);
  Serial.print('\t');

  myLux.setOnceHighRes();
  delay(200);
  val = myLux.getRaw();
  Serial.print(val, 1);
  Serial.print('\t');

  Serial.println();
}


//  -- END OF FILE --
