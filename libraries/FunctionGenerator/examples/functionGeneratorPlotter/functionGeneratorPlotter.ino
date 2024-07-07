//
//    FILE: functionGeneratorPlotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//    DATE: 2020-06-10
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  use a Serial plotter to show the data


#include "functionGenerator.h"

funcgen gen;
funcgen gen2;


void setup()
{
  Serial.begin(115200);
  //  Serial.println(__FILE__);
  //  Serial.print("FUNCTIONGENERATOR_LIB_VERSION: ");
  //  Serial.println(FUNCTIONGENERATOR_LIB_VERSION);
  //  Serial.println();

  gen.setAmplitude(80);
  gen.setFrequency(65.0 / 60.0); //  HB = BPM/60.0
  gen.setDutyCycle(40);
  gen2.setYShift(+20);

  gen2.setAmplitude(80);
  gen2.setFrequency(120.0 / 60.0); //  HB = BPM/60.0
  gen2.setDutyCycle(80);
  gen2.setYShift(-80);
}


void loop()
{
  float t = millis() * 0.001;

  //  UNCOMMENT WAVES YOU WANT TO SEE
  //  DO NOT FORGET TO PRINT THE '\t' SEPARATOR

  //  Serial.print(t, 3);
  //  Serial.print("\t");
  Serial.print(100);
  Serial.print("\t");
  Serial.print(-100);
  Serial.print("\t");
  //  Serial.print(gen.square(t));
  //  Serial.print("\t");
  //  Serial.print(gen.sawtooth(t, 0));  //  up    /|   signal
  //  Serial.print("\t");
  //  Serial.print(gen.sawtooth(t, 1));  //  down  |\   signal
  //  Serial.print("\t");
  //  Serial.print(gen.triangle(t));
  //  Serial.print("\t");
  //  Serial.print(gen.sinus(t));
  //  Serial.print("\t");
  //  Serial.print(gen.sinusDiode(t));
  //  Serial.print("\t");
  //  Serial.print(gen.sinusRectified(t));
  //  Serial.print("\t");
  //  Serial.print(gen.trapezium1(t));
  //  Serial.print("\t");
  //  Serial.print(gen.trapezium2(t));
  //  Serial.print("\t");
  Serial.print(gen.heartBeat(t));
  Serial.print("\t");
  Serial.print(gen2.heartBeat(t));
  //  Serial.print("\t");
  //  Serial.print(gen.freeWave(t, array));
  //  Serial.print("\t");
  //    Serial.print(gen.stair(t, 16, 0));  //  step up
  //    Serial.print("\t");
  //    Serial.print(gen.stair(t, 16, 1));  //  step down
  //    Serial.print("\t");
  //  Serial.print(gen.random());
  //  Serial.print("\t");
  //  Serial.print(gen.random_DC());
  //  Serial.print("\t");
  //  Serial.print(gen.line());
  //  Serial.print("\t");
  //  Serial.print(gen.zero());
  Serial.println();
  delay(10);
}


//  -- END OF FILE --
