//
//    FILE: boilingPoint_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for boiling point formula
//     URL: https://github.com/RobTillaart/Temperature
//


#include "temperature.h"

uint32_t stop, start;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TEMPERATURE_LIB_VERSION: ");
  Serial.println(TEMPERATURE_LIB_VERSION);
  Serial.println();

  for (int meters = 0; meters < 5000; meters += 100)
  {
    Serial.print(meters);
    Serial.print("\t");
    Serial.print(boilingCelsius(meters));
    Serial.print("\t");
    Serial.print(boilingFahrenheit(meters * 3.2808));
    Serial.print("\n");
  }
  Serial.println();

  for (int feet = 0; feet <= 15000; feet += 100)
  {
    Serial.print(feet);
    Serial.print("\t");
    Serial.print(boilingCelsius(feet * 0.3048));
    Serial.print("\t");
    Serial.print(boilingFahrenheit(feet));
    Serial.print("\n");
  }
  Serial.println();

  for (float temp = 100; temp >= 80; temp -= 1)
  {
    Serial.print(temp);
    Serial.print("\t");
    Serial.print(boilingMeter(temp));
    Serial.print("\n");
  }
  Serial.println();
  
  for (float temp = 100; temp >= 98; temp -= 0.1)
  {
    Serial.print(temp);
    Serial.print("\t");
    Serial.print(boilingMeter(temp));
    Serial.print("\n");
  }
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
