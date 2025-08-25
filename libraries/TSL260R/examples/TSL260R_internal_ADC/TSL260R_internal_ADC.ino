//
//    FILE: TSL260R_internal_ADC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo internal ADC
//     URL: https://github.com/RobTillaart/TSL260R
//
//  always check datasheet
//
//  PIN 1 - GND
//  PIN 2 - VDD - 5V
//  PIN 3 - SIGNAL


#include "TSL260R.h"

TSL260R  TSL0(A0, 1023, 5.0);  //  Arduino UNO

uint32_t lastMeasurement = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TSL260R_LIB_VERSION: ");
  Serial.println(TSL260R_LIB_VERSION);
  Serial.println();

  Serial.println("\t TSL260\tTSL261\tTSL262");
  Serial.println("uW/cm2");
  Serial.println("========");
}


void loop()
{
  uint32_t now = millis();
  if (now - lastMeasurement >= 100)
  {
    Serial.println(TSL0.irradiance(), 3);
  }
}


//  -- END OF FILE --
