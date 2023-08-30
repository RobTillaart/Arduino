//
//    FILE: WaterMix_demo2.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-29
// PURPOSE: demo


#include "WaterMix.h"

WaterMix WM1;
WaterMix WM2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("WATERMIX_LIB_VERSION: ");
  Serial.println(WATERMIX_LIB_VERSION);

  WM1.begin();
  WM2.begin();

  WM1.add(10, 30.7);
  WM2.add(3, 25.5);

  Serial.print("before:\t");
  Serial.print(WM1.volume());
  Serial.print("\t");
  Serial.println(WM1.temperature());

  Serial.print("add:\t");
  Serial.print(WM2.volume());
  Serial.print("\t");
  Serial.println(WM2.temperature());

  WM1.add(WM2);
  Serial.print("after:\t");
  Serial.print(WM1.volume());
  Serial.print("\t");
  Serial.println(WM1.temperature());
  

}


void loop()
{
}


//  -- END OF FILE --
