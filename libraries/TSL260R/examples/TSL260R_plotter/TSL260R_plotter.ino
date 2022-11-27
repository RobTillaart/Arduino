//
//    FILE: TSL260R_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-11-27
//
//  always check datasheet
//
//  PIN 1 - GND
//  PIN 2 - VDD - 5V
//  PIN 3 - SIGNAL


#include "TSL260R.h"

TSL260R  TSL;

uint32_t lastMeasurement = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
//  Serial.println(__FILE__);
//  Serial.print(" TSL260R_LIB_VERSION: ");
//  Serial.println(TSL260R_LIB_VERSION);
}


void loop()
{
  uint32_t now = millis();
  if (now - lastMeasurement >= 100)
  {
    lastMeasurement = now;

    float voltage = analogRead(A0) * 5.0 / 1023;
    Serial.print(voltage, 3);
    Serial.print(" \t");
    Serial.print(TSL.irradiance(voltage), 3);
    Serial.println(" uW/cm2");
  }
}


// -- END OF FILE --
