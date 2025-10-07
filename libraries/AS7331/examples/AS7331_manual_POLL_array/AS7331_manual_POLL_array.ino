//
//    FILE: AS7331_manual_POLL_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour (verbose)
//     URL: https://github.com/RobTillaart/AS7331
//
//  Not tested with an array of 4 (only one sensor)
//  - switching address runtime does work (incorrect values).

#include "AS7331.h"


AS7331 sensors[4] = { AS7331(0x74), AS7331(0x75), AS7331(0x76), AS7331(0x77) };


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("AS7331_LIB_VERSION: "));
  Serial.println(AS7331_LIB_VERSION);
  Serial.println();

  Wire.begin();

  for (int i = 0; i < 4; i++)
  {
    if (sensors[i].begin() == false)
    {
      Serial.print("invalid address: ");
      Serial.println(sensors[i].getAddress(), HEX);
    }
    else
    {
      //  initialize
      sensors[i].softwareReset();
      sensors[i].setConfigurationMode();
      sensors[i].powerUp();
      sensors[i].setMode(AS7331_MODE_MANUAL);
      sensors[i].setStandByOff();
      sensors[i].setGain(AS7331_GAIN_256x);
      sensors[i].setConversionTime(AS7331_CONV_2048);
      sensors[i].startMeasurement();
      delay(500);  //  delay so the sensors start a bit at different times.
    }
  }
}


void loop()
{
  for (int i = 0; i < 4; i++)
  {
    if (sensors[i].conversionReady())
    {
      Serial.print(i);
      Serial.print('\t');
      Serial.print(sensors[i].getUVA_uW());
      Serial.print('\t');
      Serial.print(sensors[i].getUVB_uW());
      Serial.print('\t');
      Serial.print(sensors[i].getUVC_uW());
      Serial.print('\t');
      Serial.print(sensors[i].getCelsius());
      Serial.print('\t');
      Serial.print(sensors[i].getLastError());
      Serial.println();

      //  start new measurement.
      sensors[i].startMeasurement();
    }
  }

  //  other things.
}


//  -- END OF FILE --
