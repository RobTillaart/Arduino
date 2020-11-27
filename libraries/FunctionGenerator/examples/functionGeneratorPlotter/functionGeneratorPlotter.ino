//
//    FILE: functionGeneratorPlotter.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo function generators
//    DATE: 2020-06-10
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
// use a Serial plotter to show the data


#include "functionGenerator.h"

funcgen gen;

void setup()
{
  Serial.begin(115200);
  // Serial.print("Start functionGeneratorPerformance - LIB VERSION: ");
  // Serial.println(FUNCTIONGENERATOR_LIB_VERSION);
  
  gen.setAmplitude(50);
}

void loop()
{
  float t = millis() * 0.001;
  Serial.print(gen.square(t));
  Serial.print("\t");
  Serial.print(gen.sawtooth(t));
  Serial.print("\t");
  Serial.print(gen.triangle(t));
  Serial.print("\t");
  Serial.print(gen.sinus(t));
  Serial.print("\t");
  Serial.print(gen.stair(t));
  Serial.print("\t");
  Serial.print(gen.random());
  Serial.print("\t");
  Serial.print(gen.line());
  Serial.print("\t");
  Serial.print(gen.zero());
  Serial.println();
}

// END OF FILE
