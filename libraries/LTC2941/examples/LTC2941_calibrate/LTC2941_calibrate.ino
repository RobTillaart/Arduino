//
//    FILE: LTC2941_calibrate.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test calibration routine in begin()
//     URL: https://github.com/RobTillaart/LTC2941
//
//  this sketch checks if a {Rsense, mAh} combination makes sense.
//  read datasheet page 10,11

#include "LTC2941.h"

LTC2941 LTC;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTC2941_LIB_VERSION: ");
  Serial.println(LTC2941_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  Qbattery test, default Resistor
  for (int mah = 250; mah <= 6000; mah += 250)
  {
    verify(mah, 0.050);
  }
  Serial.println();

  //  resistor test, fixed Qbattery
  for (int r = 10; r <= 200; r += 10)
  {
    verify(2000, r * 0.001);
  }


  Serial.print("\ndone...");
}


void loop()
{
}


void verify(float mAh, float Rsense)
{
  bool b = LTC.begin(mAh, Rsense);
  Serial.print(b);
  Serial.print("\t");
  Serial.print(mAh, 0);
  Serial.print("\t");
  Serial.print(Rsense, 4);
  Serial.print("\t");
  Serial.print(LTC.getPrescaler());
  Serial.print("\t");
  Serial.print(LTC.getQLSB() * 1000, 3);
  Serial.print("\t");

  uint32_t cnt = uint32_t(mAh / LTC.getQLSB());
  Serial.print(cnt);
  Serial.print("\t");
  Serial.println((cnt > 65535) || (b == false) ? "Error" : "OK");
}

//  -- END OF FILE -
