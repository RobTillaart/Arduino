//
//    FILE: functionGenerator_MCP4725.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//    DATE: 2021-01-06
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//  see readme.md for mac frequency table.


#include "functionGenerator.h"
#include "MCP4725.h"
#include "Wire.h"


funcgen gen;
float value   = 0;
float frequency = 40;
float amplitude  = 1.0;

float d = 0;

//  q = square
//  s = sinus
//  w = sawtooth
//  t = stair
//  r = random
char mode = 's';

MCP4725 MCP(0x63);
uint32_t count;
uint32_t lastTime = 0;


void setup()
{
  Serial.begin(230400);
  gen.setAmplitude(1);
  gen.setYShift(1);
  gen.setFrequency(frequency);
  value = 0;

  Wire.begin();
  MCP.begin();
  Wire.setClock(100000);

  MCP.setValue(0);
  if (!MCP.isConnected())
  {
    Serial.println("err");
    while (1);
  }

  while (1)
  {
    count++;
    float t = micros() * 0.000001;
    if (millis() - lastTime > 1000)
    {
      Serial.println(count);
      count = 0;
      lastTime = millis();
    }

    if (Serial.available())
    {
      int c = Serial.read();
      switch (c)
      {
        case '+':
          frequency += 0.01;
          break;
        case '-':
          frequency -= 0.01;
          break;
        case '*':
          frequency *= 10;
          break;
        case '/':
          frequency /= 10;
          break;
        case '0' ... '9':
          frequency *= 10;
          frequency += (c - '0');
          break;
        case 'c':
          frequency = 0;
          break;
        case 'A':
          break;
        case 'a':
          break;
        case 'D':
          d = gen.getDutyCycle();
          d++;
          gen.setDutyCycle(d);
          break;
        case 'd':
          d = gen.getDutyCycle();
          d--;
          gen.setDutyCycle(d);
          break;
          break;
        case 'q':
        case 's':
        case 'w':
        case 't':
        case 'r':
          mode = c;
          break;
        default:
          break;
      }
      gen.setFrequency(frequency);
      Serial.println(frequency);
    }

    switch (mode)
    {
      case 'q':
        value = 2047 * gen.square(t);
        break;
      case 'w':
        value = 2047 * gen.sawtooth(t);
        break;
      case 't':
        value = 2047 * gen.triangle(t);
        break;
      case 'r':
        value = 2047 * gen.random();
        break;
      default:
      case 's':
        value = 2047 *  gen.sinus(t);
        break;
    }
    MCP.setValue(value);
  }
}


void loop()
{
}


//  -- END OF FILE --
