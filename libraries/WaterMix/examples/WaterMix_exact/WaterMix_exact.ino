//
//    FILE: WaterMix_exact.ino
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

  fast();

  exact();
}

void fast()
{
  Serial.println(__FUNCTION__);

  WM1.begin(10, 10);
  WM2.begin(20, 50);

  Serial.print("before:\t");
  Serial.print(WM1.volume(), 4);
  Serial.print("\t");
  Serial.println(WM1.temperature(), 4);

  Serial.print("add:\t");
  Serial.print(WM2.volume(), 4);
  Serial.print("\t");
  Serial.println(WM2.temperature(), 4);

  delay(100);

  uint32_t start = micros();
  WM1.add(WM2);
  uint32_t stop = micros();

  Serial.print("after:\t");
  Serial.print(WM1.volume(), 4);
  Serial.print("\t");
  Serial.println(WM1.temperature(), 4);

  Serial.print("Time:\t");
  Serial.println(stop - start);

  Serial.println("\n");
}


void exact()
{
  Serial.println(__FUNCTION__);

  WM1.begin(10, 10);
  WM2.begin(20, 50);

  Serial.print("before:\t");
  Serial.print(WM1.volume(), 4);
  Serial.print("\t");
  Serial.println(WM1.temperature(), 4);

  Serial.print("add:\t");
  Serial.print(WM2.volume(), 4);
  Serial.print("\t");
  Serial.println(WM2.temperature(), 4);

  delay(100);

  uint32_t start = micros();
  WM1.addExact(WM2);
  uint32_t stop = micros();

  Serial.print("after:\t");
  Serial.print(WM1.volume(), 4);
  Serial.print("\t");
  Serial.println(WM1.temperature(), 4);

  Serial.print("Time:\t");
  Serial.println(stop - start);

  Serial.println("\n");
}


void loop()
{
}


//  -- END OF FILE --
