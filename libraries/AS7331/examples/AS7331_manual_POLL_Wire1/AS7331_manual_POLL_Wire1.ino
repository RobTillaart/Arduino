//
//    FILE: AS7331_manual_POLL_Wire1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test Wire1 API, e.g. ESP32
//     URL: https://github.com/RobTillaart/AS7331


#include "AS7331.h"


AS7331 mySensor(0x74, &Wire1);


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

  //  explicit reset and configuration
  mySensor.softwareReset();
  mySensor.setConfigurationMode();
  mySensor.powerUp();
  mySensor.setMode(AS7331_MODE_MANUAL);
  mySensor.setStandByOff();
  mySensor.setGain(AS7331_GAIN_256x);
  mySensor.setConversionTime(AS7331_CONV_4096);

  mySensor.startMeasurement();
}


void loop()
{
  //  alternative, if you need status too
  //  uint16_t status = mySensor.readStatus();
  //  if (status & 0x0800)
  //  {
  //  }

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
