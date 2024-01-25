//    FILE: RMS_by_sampling.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-08-15
// PURPOSE: demo RMS by sampling for AC current
//     URL: https://github.com/RobTillaart/ACS712
//
//  stand alone sketch to be used with a ACS712


#include "Arduino.h"
//  #include "printHelpers.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
}


void loop()
{
  //  50 Hz, Arduino UNO, 20A ACS
  float current = mA_AC_sampling(50, 5000.0 / 1023, 100, A0);
  Serial.println(current);
  delay(1000);
}


float mA_AC_sampling(float frequency, float mVperStep, float mVperAmpere, uint8_t analogPin)
{
  uint16_t midpoint   = 511;
  uint32_t period     = round(1000000UL / frequency);
  uint16_t samples    = 0;
  float    sumSquared = 0;

  uint32_t start = micros();
  while (micros() - start < period)
  {
    samples++;
    float current = analogRead(analogPin) - midpoint;
    sumSquared += (current * current);
  }
  //  Serial.print(scieng(sumSquared, 1, 3));
  //  Serial.print("\t");
  //  Serial.print(samples);
  //  Serial.print("\t");
  float AmperePerStep = mVperStep / mVperAmpere;
  float RMS = sqrt(sumSquared / samples) * AmperePerStep;
  return RMS * 1000.0;  //  mA
}


//  -- END OF FILE --
