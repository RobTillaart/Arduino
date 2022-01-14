//
//    FILE: MS5611_DETECTOR.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: detect an MS5611 on a NANO33 BLE
//    DATE: 2022-01-13
//     URL: https://github.com/RobTillaart/MS5611


#include "Arduino.h"
#include "Wire.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.beginTransmission(0x76);
  Wire.write(0);
  int x = Wire.endTransmission();
  Wire.beginTransmission(0x77);
  Wire.write(0);
  int y = Wire.endTransmission();

  Serial.println(x);
  Serial.println(y);
  delay(1000);

  if (x == 0) Serial.println("MS5611 found at 0x76");
  else if (y == 0) Serial.println("MS5611 found at 0x77");
  else Serial.println("no MS5611 found");

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
