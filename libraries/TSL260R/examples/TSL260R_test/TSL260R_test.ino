//
//    FILE: TSL260R_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test wavelength
//    DATE: 2022-11-27
//
//  always check datasheet
//
//  PIN 1 - GND
//  PIN 2 - VDD - 5V
//  PIN 3 - SIGNAL


#include "TSL260R.h"

TSL260R  TSL0(A0, 1023, 5.0);
TSL261R  TSL1;
TSL262R  TSL2;

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
  Serial.println(TSL0.getAA());
  Serial.println(TSL0.getBB());

  Serial.println(TSL1.getWaveLength());
  Serial.println(TSL1.getWaveLengthFactor());
  Serial.println(TSL1.getAA());
  Serial.println(TSL1.getBB());

  Serial.println(TSL2.getWaveLength());
  Serial.println(TSL2.getWaveLengthFactor());
  Serial.println(TSL2.getAA());
  Serial.println(TSL2.getBB());
}


void loop()
{
}


// -- END OF FILE --
