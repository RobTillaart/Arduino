//
//    FILE: AS7331_manual.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AS7331


#include "AS7331.h"


AS7331 mySensor(0x70);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS7331_LIB_VERSION: ");
  Serial.println(AS7331_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (mySensor.begin() == false)
  {
    Serial.println("Could not connect to AS7331.");
    //  while(1);
  }

  //  just explicit.
  mySensor.setMode(AS7331_MODE_MANUAL);
  mySensor.setGain(AS7331_GAIN_2x);
  mySensor.setConversionTime(AS7331_CONV_001);

  mySensor.setMeasurementMode();
}


void loop()
{
  if (mySensor.conversionReady())
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
    mySensor.setMeasurementMode();
  }

}


//  -- END OF FILE --
