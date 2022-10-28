//
//    FILE: demUV.ino
//  AUTHOR: Rob Tillaart
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
  float uvi = AUV.read(3);      //  average 3 readings
  Serial.print("UVI: ");
  Serial.print(uvi, 1);
  Serial.print("\t");
  Serial.println(AUV.index2color(uvi));
  delay(1000);
}


// -- END OF FILE --
