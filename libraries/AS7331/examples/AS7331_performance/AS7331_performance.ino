//
//    FILE: AS7331_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour (verbose)
//     URL: https://github.com/RobTillaart/AS7331


#include "AS7331.h"

AS7331 mySensor(0x74);
uint32_t start, stop;


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
  mySensor.setConfigurationMode();
  mySensor.powerUp();
  mySensor.setMode(AS7331_MODE_CONTINUOUS);
  mySensor.setConversionTime(AS7331_CONV_1024);
  mySensor.setStandByOff();
  mySensor.startMeasurement();

  Serial.println("\nconversionReady()");
  for (uint32_t speed = 100000; speed <= 800000; speed += 100000)
  {
    Wire.setClock(speed);
    delay(100);  //  flush IO
    start = micros();
    bool b = mySensor.conversionReady();
    stop = micros();
    Serial.print(speed);
    Serial.print('\t');
    Serial.print(stop - start);
    Serial.println();
  }

  Serial.println("\ngetUVA_uW()");
  for (uint32_t speed = 100000; speed <= 800000; speed += 100000)
  {
    Wire.setClock(speed);
    delay(100);  //  flush IO
    while (mySensor.conversionReady() == false);

    start = micros();
    float uva = mySensor.getUVA_uW();
    stop = micros();
    Serial.print(speed);
    Serial.print('\t');
    Serial.print(stop - start);
    Serial.println();
  }


}


void loop()
{
}


//  -- END OF FILE --
