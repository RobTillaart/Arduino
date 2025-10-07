//
//    FILE: AS7331_manual_POLL.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour (verbose)
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

  //  explicit reset
  mySensor.softwareReset();
  Serial.println("softwareReset: ");

  //  select configuration mode
  mySensor.setConfigurationMode();
  Serial.print("setConfigurationMode: ");
  Serial.println(mySensor.readOSR(), HEX);

  mySensor.powerUp();
  Serial.print("powerUP: ");
  Serial.println(mySensor.readOSR(), HEX);

  Serial.print("getDeviceID: ");
  Serial.println(mySensor.getDeviceID(), HEX);
  Serial.println();

  //  select manual mode,
  mySensor.setMode(AS7331_MODE_MANUAL);
  Serial.print("setMode: ");
  Serial.println(mySensor.getMode());

  mySensor.setStandByOff();
  Serial.print("GetStandByMode: ");
  Serial.println(mySensor.getStandByMode(), HEX);

  mySensor.setGain(AS7331_GAIN_256x);
  Serial.print("setGain: ");
  Serial.println(mySensor.getGain());

  mySensor.setConversionTime(AS7331_CONV_4096);
  Serial.print("setConversionTime: ");
  Serial.println(mySensor.getConversionTime());

  mySensor.startMeasurement();
  Serial.print("startMeasurement: ");
  Serial.println(mySensor.readStatus(), HEX);
}


void loop()
{
  //  alternative, if you need status too
  //  uint16_t status = mySensor.readStatus();
  //  if (status & AS7331_STATUS_NDATA)
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
