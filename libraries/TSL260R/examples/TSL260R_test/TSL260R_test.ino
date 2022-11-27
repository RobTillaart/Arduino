//
//    FILE: TSL260R_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: verify figure 12 datasheet page 9 voltage vs irradiance.
//    DATE: 2022-11-27
//
//  always check datasheet
//
//  PIN 1 - GND
//  PIN 2 - VDD - 5V
//  PIN 3 - SIGNAL


#include "TSL260R.h"

TSL260R  TSL0(A0, 1023, 5.0);

uint32_t lastMeasurement = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(" TSL260R_LIB_VERSION: ");
  Serial.println(TSL260R_LIB_VERSION);

  Serial.println(TSL0.getWaveLength());
  Serial.println(TSL0.getWaveLengthFactor());
}


void loop()
{
}


// -- END OF FILE --
