//
//    FILE: TSL260R_demo.ino
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

TSL260R  TSL0;
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

  Serial.println("\t TSL260\tTSL261\tTSL262");
  Serial.println("Volt \t uW/cm2");
  Serial.println("==============================");
  for (float voltage = 0.1; voltage <= 3; voltage += 0.1)
  {
    Serial.print(voltage, 3);
    Serial.print("\t");
    Serial.print(TSL0.irradiance(voltage), 3);
    Serial.print("\t");
    Serial.print(TSL1.irradiance(voltage), 3);
    Serial.print("\t");
    Serial.print(TSL2.irradiance(voltage), 3);
    Serial.println();
  }
  Serial.println("\ndone...");
}


void loop()
{
}


// -- END OF FILE --
