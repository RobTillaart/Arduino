//
//    FILE: AS7331_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AS7331


#include "AS7331.h"


AS7331 mySensor(0x33);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS7331_LIB_VERSION: ");
  Serial.println(AS7331_LIB_VERSION);
  Serial.println();

  Wire.begin();
  mySensor.begin();

  mySensor.setMeasurementMode();
}


void loop()
{
  Serial.print("UVA:\t");
  Serial.println(mySensor.getUVA());
  Serial.print("UVB:\t");
  Serial.println(mySensor.getUVB());
  Serial.print("UVC:\t");
  Serial.println(mySensor.getUVC());
  Serial.print("TEMP:\t");
  Serial.println(mySensor.getCelsius());
  Serial.println();

  delay(2000);
}


//  -- END OF FILE --
