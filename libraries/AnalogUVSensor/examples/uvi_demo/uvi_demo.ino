//
//    FILE: uvi_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo UV sensor
//    DATE: 2021-09-25


#include "AnalogUVSensor.h"

AnalogUVSensor AUV;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print("ANALOG_UVSENSOR_LIB_VERSION: ");
  Serial.println(ANALOG_UVSENSOR_LIB_VERSION);

  AUV.begin(A0, 5.0, 1023);
}


void loop()
{
  float uvi = AUV.read();
  Serial.print("UVI: ");
  Serial.println(uvi, 1);
  delay(1000);
}


// -- END OF FILE --
