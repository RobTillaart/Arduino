//
//    FILE: WaterMix_demo.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-29
// PURPOSE: demo


#include "WaterMix.h"

WaterMix WM;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("WATERMIX_LIB_VERSION: ");
  Serial.println(WATERMIX_LIB_VERSION);

  WM.begin();
  WM.add(100, 50);
}


void loop()
{
  WM.add(100, 10);
  Serial.print(WM.volume());
  Serial.print("\t");
  Serial.println(WM.temperature());
  delay(100);
}


//  -- END OF FILE --
