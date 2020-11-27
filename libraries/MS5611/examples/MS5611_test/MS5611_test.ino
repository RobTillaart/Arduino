//
//    FILE: MS5611_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: demo application
//    DATE: 2014-okt-16
//     URL: https://github.com/RobTillaart/MS5611

#include "MS5611.h"

MS5611 MS5611(0x77);

void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("MS5611 lib version: ");
  Serial.println(MS5611_LIB_VERSION);
  
  Wire.begin();
  MS5611.begin();
}

void loop()
{
  int result = MS5611.read();
  if (result != MS5611_READ_OK)
  {
    Serial.print("Error in read: ");
    Serial.println(result);
  }
  else
  {
    Serial.print("T:\t");
    Serial.print(MS5611.getTemperature() * 0.01, 2);
    Serial.print("\tP:\t");
    Serial.print(MS5611.getPressure() * 0.01, 2);
  }

  delay(5000);
}
