//
//    FILE: functionGenerator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//    DATE: 2015-01-03
//     URL: https://github.com/RobTillaart/FunctionGenerator


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
  //  wave selection by potMeter
  // int choice = analogRead(A0) / 200;

  float value;
  //  wait for next millisecond;
  if (millis() - lastTime > 0)
  {
    lastTime = millis();
    float t = lastTime * 0.001;
    switch (choice)
    {
      case '0':  value = gen.square(t);   break;
      case '1':  value = gen.sawtooth(t); break;
      case '2':  value = gen.triangle(t); break;
      case '3':  value = gen.stair(t);    break;
      case '4':  value = gen.sinus(t);    break;
      case '5':  value = gen.line();      break;
      case '6':  value = gen.random();    break;
      default:   value = gen.zero();      break;
    }
    Serial.println(value);
  }
}


//  -- END OF FILE --

