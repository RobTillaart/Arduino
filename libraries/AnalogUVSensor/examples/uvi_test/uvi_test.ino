//
//    FILE: uvi_test.ino
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

  for (uint16_t milliVolt = 0; milliVolt < 1210; milliVolt += 10)
  {
    Serial.print(milliVolt);
    Serial.print("\t");
    Serial.println(AUV.mV2index(milliVolt), 1);
  }

  Serial.println("\n Done...");
}


void loop()
{
}


// -- END OF FILE --
