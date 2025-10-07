//
//    FILE: AS7331_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal sketch
//     URL: https://github.com/RobTillaart/AS7331


#include "AS7331.h"


AS7331 mySensor(0x74);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("AS7331_LIB_VERSION: "));
  Serial.println(AS7331_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (mySensor.begin() == false)
  {
    Serial.print("invalid address: ");
    Serial.println(mySensor.getAddress(), HEX);
    while (1);
  }

  /*  defaults from begin()
    _mode     = AS7331_MODE_MANUAL;
    _gain     = AS7331_GAIN_16x;
    _convTime = AS7331_CONV_064;
  */
  mySensor.powerUp();
  mySensor.setConversionTime(AS7331_CONV_4096);  // just make it a bit slow
  
  mySensor.startMeasurement();
}


void loop()
{
  if (mySensor.conversionReady())
  {
    Serial.print("UVA:\t");
    Serial.println(mySensor.getUVA_uW());
    Serial.print("UVB:\t");
    Serial.println(mySensor.getUVB_uW());
    Serial.print("UVC:\t");
    Serial.println(mySensor.getUVC_uW());
    Serial.print("TEMP:\t");
    Serial.println(mySensor.getCelsius());
    Serial.print("ERR:\t");
    Serial.println(mySensor.getLastError());
    Serial.println();
    //  start new measurement.
    mySensor.startMeasurement();
  }

  //  other things.
}


//  -- END OF FILE --
