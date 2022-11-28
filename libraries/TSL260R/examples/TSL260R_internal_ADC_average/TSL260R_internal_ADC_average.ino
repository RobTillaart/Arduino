//
//    FILE: TSL260R_internal_ADC_average.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo average internal ADC
//    DATE: 2022-11-28
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
  Serial.print("\nTSL260R_LIB_VERSION: ");
  Serial.println(TSL260R_LIB_VERSION);

  Serial.println("\t TSL260\tTSL261\tTSL262");
  Serial.println("uW/cm2");
  Serial.println("========");
}


void loop()
{
  uint32_t now = millis();
  if (now - lastMeasurement >= 100)
  {
    lastMeasurement = now;
    Serial.print(TSL0.irradiance(), 3);
    Serial.print("\t");

    float voltage = 0;
    for (int i = 0; i < 10; i++)
    {
      voltage += analogRead(A0) * (5.0 / 1023);
    }
    Serial.println(TSL0.irradiance(voltage * 0.1), 3);
  }
}


// -- END OF FILE --
