//
//    FILE: functionGenerator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo function generators
//    DATE: 2015-01-03
//     URL: https://github.com/RobTillaart/FunctionGenerator
//

#include "functionGenerator.h"

funcgen gen;

uint32_t lastTime = 0;
char choice = '0';

void setup()
{
  Serial.begin(500000);
  Serial.println(__FILE__);
  Serial.println("Start ");

  gen.setFrequency(4);
  gen.setAmplitude(50);
}

void loop()
{
  if (Serial.available())
  {
    choice = Serial.read();
  }
  // wave selection by potMeter
  // int choice = analogRead(A0) / 200;

  float val;
  // wait for next millisecond;
  if (millis() - lastTime > 0)
  {
    lastTime = millis();
    float t = lastTime * 0.001;
    switch (choice)
    {
      case '0':  val = gen.square(t);   break;
      case '1':  val = gen.sawtooth(t); break;
      case '2':  val = gen.triangle(t); break;
      case '3':  val = gen.stair(t);    break;
      case '4':  val = gen.sinus(t);    break;
      case '5':  val = gen.line();      break;
      case '6':  val = gen.random();    break;
      default:   val = gen.zero();      break;
    }
    Serial.println(val);
  }
}

// END OF FILE
